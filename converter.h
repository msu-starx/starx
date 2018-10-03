/*
 *	converter.h
 *
 *	MSU STARX Exosuit
 *	Software Version 2.3
 *	Created on: September 30, 2018
 *	All rights reserved
 */

#ifndef CONVERTER_H_
#define CONVERTER_H_

// Standard includes
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Converter {
    public:
        double convertToVoltage(int adcValue, double adcMultiplier);
        double convertToPressure(double voltageValue);
        double convertToForce(double voltageValue);
        int stringToInt(const std::string &str);
        float stringToFloat(const std::string &str);
        double stringToDouble(const std::string &str);
        std::string intToString(int n);
        std::vector<std::string> splitString(const std::string &str, char delimiter);
};

#endif // CONVERTER_H_
