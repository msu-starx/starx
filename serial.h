/*
 *	serial.h
 *
 *	MSU STARX Exosuit
 *	Software Version 2.3
 *	Created on: September 30, 2018
 *	All rights reserved
 */

#ifndef SERIAL_H_
#define SERIAL_H_

// Standard includes
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

class SerialPort {
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

#endif // SERIAL_H_
