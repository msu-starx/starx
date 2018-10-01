// This is start of the header guard
#ifndef ARDUINOMICRO_H
#define ARDUINOMICRO_H

#include "serial.h"
#include <string>
#include <vector>

class ArduinoMicro{
  public:
    // Arduino Serial
    SerialPort arduinoPort;
    const unsigned int waitTime = 25; // Send and receive wait time (milliseconds)
    const char* packet;
    std::string data;
    // Arduino Parameters
    const int ADCPinCount = 12;
    const int GPIOPinCount = 10;
    const double ADCVoltageMultiplier = 5.0 / 1023.0;
    const std::string PacketDelimiterString = ",";
    const std::string PacketTerminatorString = "\r";
    // Arduino Commands
    const std::string GetADCValuesString = "ADC";
    const std::string GetGPIOValuesString = "DIG";
    const std::string SetGPIODirectionString = "PIN";
    const std::string SetGPIODirectionOutString = "OUT";
    const std::string SetGPIODirectionInString = "IN";
    const std::string SetPWMDutyCycleString = "PWM";
    const std::string SetFullStopString = "STP";
    // Arduino Functions
    std::string getADC(void);
    std::string getGPIO(void);
    std::string setPWM(std::vector<std::string> dutyCycles);
    void setupSerial(std::string portName, int baudRate);
    std::string createPacket(std::string command, std::vector<std::string> parameters);
};

// This is the end of the header guard
#endif
