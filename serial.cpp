#include "serial.h"

void SerialPort::openPort(void){
  fileDescriptor = open(portName, O_RDWR | O_NOCTTY);
  // portName = Name of serial port
  // O_RDWR = Allows read/write access to serial port
  // O_NOCTTY = No terminal will control the process
  // O_NDELAY = Non blocking mode (do not care about the DCD line status)
  if (fileDescriptor == -1){
    perror("\nOpen_Port: Unable to open serial port =");
  }
  else{
    printf("\nPort %s opened successfully!\n", portName);
  }
}

void SerialPort::setPort(void){
  tcgetattr(fileDescriptor, &portSettings); // Gets the current attributes

  switch(baudRate){
    case 300:
      constBaud = B300;
      break;
    case 600:
      constBaud = B600;
      break;
    case 1200:
      constBaud = B1200;
      break;
    case 2400:
      constBaud = B2400;
      break;
    case 4800:
      constBaud = B4800;
      break;
    case 9600:
      constBaud = B9600;
      break;
    case 19200:
      constBaud = B19200;
      break;
    case 38400:
      constBaud = B38400;
      break;
    case 57600:
      constBaud = B57600;
      break;
    case 115200:
      constBaud = B115200;
      break;
  }

  cfsetispeed(&portSettings, constBaud); // Sets read speed
  cfsetospeed(&portSettings, constBaud); // Sets write speed

  portSettings.c_cflag &= ~PARENB; // Disables parity
  portSettings.c_cflag &= ~CSTOPB; // Sets the stop bits amount to 1
  portSettings.c_cflag &= ~CSIZE; // Clears the mask for setting the data size
  portSettings.c_cflag |=  CS8; // Set the data bits amount to 8
  portSettings.c_cflag &= ~CRTSCTS; // Disables hardware flow control
  portSettings.c_cflag |=  (CREAD | CLOCAL); // Enables receiver and sets local mode
  portSettings.c_iflag &= ~(IXON | IXOFF | IXANY); // Disables software flow control
  portSettings.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Selects raw input mode
  portSettings.c_oflag &= ~OPOST; // Selects raw output mode

  portSettings.c_cc[VMIN]  = 0; // Minimum number of characters to read
  portSettings.c_cc[VTIME] = 0; // Time to wait for every character read
  // If VMIN = 0 and VTIME = 0, read() will be satisfied immediately

  if((tcsetattr(fileDescriptor, TCSANOW, &portSettings)) != 0){ // Sets the new attributes
    perror("\nSet_Port: Error in setting attributes - ");
  }
  else{
    printf("\n| Baud rate = %d bps | Stop bits = 1 | Parity = None |\n", baudRate);
  }

  this->flushPortAll();
}

void SerialPort::writePort(const char* bufferWrite){
  bytesWrite = write(fileDescriptor, bufferWrite, strlen(bufferWrite));
  if(bytesWrite < 0){
    fputs("write() of bytes failed!\n", stderr);
  }
  //*// Debug SerialPort::writePort
  if(bytesWrite > 0){
    printf("Sent: %s", bufferWrite);
    printf("\n");
  }//*/
}

char* SerialPort::readPort(void){
  bytesRead = read(fileDescriptor, &bufferRead, bufferSize);
  bufferRead[bytesRead] = 0;
  //*// Debug SerialPort::readPort
  if(bytesRead > 0){
    printf("Received: %s", bufferRead);
    printf("\n");
  }//*/
  return bufferRead;
}

char* SerialPort::readPortUntil(char bufferTerminator){
  // Not implemented
}

void SerialPort::closePort(void){
  close(fileDescriptor);
}

void SerialPort::flushPortIn(void){
  tcflush(fileDescriptor, TCIFLUSH);
}

void SerialPort::flushPortOut(void){
  tcflush(fileDescriptor, TCOFLUSH);
}

void SerialPort::flushPortAll(void){
  tcflush(fileDescriptor, TCIOFLUSH);
}
