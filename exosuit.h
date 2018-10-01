// This is start of the header guard
#ifndef EXOSUIT_H
#define EXOSUIT_H

#include "arduinomicro.h"
#include "converter.h"
#include "pid.h"

// Arduino Micro ADC Connections
// => ADC String = [A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11]
// A0 = Pressure Sensor Channel 1
// A1 = Pressure Sensor Channel 2
// A2 = Pressure Sensor Channel 3
// A3 = Pressure Sensor Channel 4
// A4 = FSR Sensor 1
// A5 = FSR Sensor 2
// A6 = FSR Sensor 3
// A7 = FSR Sensor 4
// A8 = EMG Sensor 1
// A9 = Reserved for PWM Channel 2
// A10 = Reserved for PWM Channel 3
// A11 = EMG Sensor 2

class ExoSuit{
  public:
    // Filter
    std::vector<double> u;
    std::vector<double> y;
    std::vector<double> lasty;
    Converter cvt;
    // Microcontroller Parameters
    ArduinoMicro board;
    #define portName "/dev/ttyACM0" // Arduino port
    #define baudRate 115200 // Serial baud rate
    // Sensor Definitions
    const unsigned int SensorMax = 4;
    std::vector<int> adcValues;
    std::vector<int> pressurePins{0, 1, 2, 3};
    std::vector<int> forcePins{4, 5, 6, 7};
    std::vector<int> emgPins{8, 11};
    std::vector<double> pressureStates;
    std::vector<double> forceStates;
    std::vector<double> emgStates;
    // Pressure Controller Definitions
    unsigned long totalTime = 0;
    unsigned int mode = 0;
    unsigned long lastTime = 0;
    unsigned long sampleTime = 3000; //milliseconds
    double Kp = 3; // 4
    double Ki = 2; // 3
    double Kd = 0.05; // 0.01
    double outputMin = 0;
    double outputMax = 100;
    double setpointValue = 60; // PSI
    std::vector<double> outputStates;
    std::vector<double> setpointStates;
    std::vector<unsigned int> dutyCycleStates;
    std::vector<std::string> dutyCycles;
    std::vector<PID> pressurePID;
    // Exosuit Functions
    void updateADC(void);
    void updateGPIO(void);
    void updateSensors(void);
    void updatePressurePID(void);
    void updatePWM(void);
    void initialize(void);
};

// This is the end of the header guard
#endif
