// This is start of the header guard
#ifndef SERIAL_H
#define SERIAL_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <string.h>

class SerialPort{
  public:
    speed_t constBaud;
    int fileDescriptor = 0;
    int bytesWrite = 0;
    int bytesRead = 0;
    int baudRate = 0;
    static const int byteSize = 1; // Default byte array size
    static const int bufferSize = 255; // Default buffer array size
    char byteArray[byteSize] = {0}; // Initialized with null characters
    char bufferRead[bufferSize] = {0}; // Initialized with null characters
    const char *portName;
    struct termios portSettings;
    void openPort(void);
    void setPort(void);
    void flushPortIn(void);
    void flushPortOut(void);
    void flushPortAll(void);
    void closePort(void);
    void writePort(const char* bufferWrite);
    char* readPort(void);
    char* readPortUntil(char bufferTerminator);
};

// This is the end of the header guard
#endif
