// This is start of the header guard
#ifndef CONVERTER_H
#define CONVERTER_H

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Converter{
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

// This is the end of the header guard
#endif
