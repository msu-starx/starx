#include "converter.h"

double Converter::convertToVoltage(int adcValue, double adcMultiplier){
  double voltageValue = (double)(adcValue * adcMultiplier);
  return voltageValue;
}

double Converter::convertToPressure(double voltageValue){
  double pressureValue = ((voltageValue / 5.0) - 0.1) * (100.0 / 0.8);
  return pressureValue;
}

double Converter::convertToForce(double voltageValue){
  // Implement Force vs. Voltage interpolation
  double forceValue = voltageValue;
  return forceValue;
}

std::vector<std::string> Converter::splitString(const std::string &str, char delimiter){
  std::vector<std::string> tokens = {};
  std::string token = "";
  std::stringstream stream(str);
  while(std::getline(stream, token, delimiter)){
    tokens.push_back(token);
  }
  return tokens;
}

int Converter::stringToInt(const std::string &str){
  return std::stoi(str);
}

float Converter::stringToFloat(const std::string &str){
  return std::stof(str);
}

double Converter::stringToDouble(const std::string &str){
  return std::stod(str);
}

std::string Converter::intToString(int n){
  return std::to_string(n);
}
