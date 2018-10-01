#include "arduinomicro.h"

std::string ArduinoMicro::createPacket(std::string command, std::vector<std::string> parameters = {}){
  std::string message = "";
  message.reserve(message.capacity()*10); // Increase message capacity for appending parameters
  message.append(command);
  if(!parameters.empty()){
    for(int i = 0; i < parameters.size(); i++){
      message.append(PacketDelimiterString);
      message.append(parameters[i]);
    }
  }
  message.append(PacketTerminatorString);
  return message;
}

std::string ArduinoMicro::getADC(void){
  packet = this->createPacket(GetADCValuesString).c_str();
  arduinoPort.writePort(packet);
  usleep(waitTime*1000); // Delay before reading buffer
  data = arduinoPort.readPort();
  return std::string(data);
}

std::string ArduinoMicro::getGPIO(void){
  packet = this->createPacket(GetGPIOValuesString).c_str();
  arduinoPort.writePort(packet);
  usleep(waitTime*1000); // Delay before reading buffer
  data = arduinoPort.readPort();
  return std::string(data);
}

std::string ArduinoMicro::setPWM(std::vector<std::string> dutyCycles){
  packet = this->createPacket(SetPWMDutyCycleString, dutyCycles).c_str();
  arduinoPort.writePort(packet);
  usleep(waitTime*1000); // Delay before reading buffer
  data = arduinoPort.readPort();
  return std::string(data);
}

void ArduinoMicro::setupSerial(std::string portName, int baudRate){
  arduinoPort.portName = portName.c_str();
  arduinoPort.baudRate = baudRate;
  arduinoPort.openPort();
  arduinoPort.setPort();
}
