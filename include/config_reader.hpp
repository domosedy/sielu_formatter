#ifndef FORMAT_CONFIG_READER
#define FORMAT_CONFIG_READER

#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>

using namespace std::string_literals;
enum class ExpressionType { CLASS, ENUM, VARIABLE_IN_CLASS, VARIABLE_IN_FUNCTION, FUNCTION, CONSTANT};

class ConfigReader {

    inline static std::map<ExpressionType, std::string> m_configurationInRegex;
    inline static const std::map<std::string, ExpressionType> m_parsedParameterToExpression {
        {"Enum"s, ExpressionType::ENUM},
        {"Class"s, ExpressionType::CLASS},
        {"VarClass"s, ExpressionType::VARIABLE_IN_CLASS},
        {"VarFunc"s, ExpressionType::VARIABLE_IN_FUNCTION},
        {"Function"s, ExpressionType::FUNCTION},
        {"Constant"s, ExpressionType::CONSTANT}
    };

    inline static const std::map<std::string, std::string> m_typeOfParameterToRegex {
        {"snake_case"s, R"([a-z]+(_[a-z]+)*)"s},
        {"camelCase"s, R"([a-z]+([A-Z][a-z]+)*)"s},
        {"CamelCase"s, R"(([A-Z][a-z]+)+)"s},
        {"CAPS_CASE"s, R"([A-Z]+(_[A-Z]+)*)"s},
        {"m_snake_case"s, R"(m_[a-z]+(_[a-z]+)*)"s}
    };

public:
    ConfigReader() = delete;

    static void readConfig(const std::string &fileName) {
        std::filebuf fb;

        if (!fb.open(fileName, std::ios::in)) {
            throw std::runtime_error("Config file doesn't exists.");
        }

        std::istream inputFile(&fb);

        for (std::string line; std::getline(inputFile, line); ) {
            std::stringstream lineInput(line);

            std::string parameter;

            if (!std::getline(lineInput, parameter, '=')) {
                continue;
            }

            auto iteratorInExpression = m_parsedParameterToExpression.find(parameter);

            if (iteratorInExpression == m_parsedParameterToExpression.end()) {
                throw std::runtime_error("Expression in config file doesn't exist");
            }


            std::string typeOfParameter;
            std::getline(lineInput, typeOfParameter);

            auto iteratorOfCase = m_typeOfParameterToRegex.find(typeOfParameter);

            if (iteratorOfCase == m_typeOfParameterToRegex.end()) {
                throw std::runtime_error("Type of case doesn't exist");
            }

            m_configurationInRegex[iteratorInExpression->second] = iteratorOfCase->second;
        }

        if (m_configurationInRegex.size() != m_parsedParameterToExpression.size()) {
            throw std::runtime_error("There are too little type of expression in config file");
        }
    }

    static const std::map<ExpressionType, std::string>& getConfiguration() {
        if (m_configurationInRegex.size() == 0) {
            throw std::runtime_error("Using parser without entering file");
        }

        return m_configurationInRegex;
    }
};

#endif