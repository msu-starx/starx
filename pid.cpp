#include "pid.h"

//PID::PID(double* input, double* output, double* setpoint, double Kp, double Ki, double Kd, double controllerDirection){
//}
//PID::PID(){
//}

unsigned long PID::millis(void){
  struct timeval tp;
  gettimeofday(&tp, NULL);
  return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

bool PID::computeValues(void){
  if(!inAuto) return false;
  unsigned long currentTime = this->millis();
  unsigned long elapsedTime = currentTime - lastTime;
  if(elapsedTime >= sampleTime){
    errorValue = setPoint - inputValue;
    iTerm += kiGain * errorValue;
    if(iTerm > outMax) iTerm = outMax;
    else if(iTerm < outMin) iTerm = outMin;
    dInput = inputValue - lastInput;
    // PID Equation
    outputValue = (kpGain * errorValue) + (iTerm) - (kdGain * dInput);
    //
    if(outputValue > outMax) outputValue = outMax;
    else if(outputValue < outMin) outputValue = outMin;
    lastInput = inputValue;
    lastTime = currentTime;
    return true;
  }
  else return false;
}

void PID::setTunings(double Kp, double Ki, double Kd){
  if(Kp < 0 || Ki < 0 || Kd < 0) return;
  double sampleTimeInSec = ((double)sampleTime) / 1000;
  kpGain = Kp;
  kiGain = Ki * sampleTimeInSec;
  kdGain = Kd / sampleTimeInSec;
  if(controllerDirection == REVERSE){
    kpGain = (0 - kpGain);
    kiGain = (0 - kiGain);
    kdGain = (0 - kdGain);
  }
}

void PID::setSampleTime(int newSampleTime){
  if(newSampleTime > 0){
    double ratio = newSampleTime / sampleTime;
    kiGain *= ratio;
    kdGain /= ratio;
    sampleTime = newSampleTime;
  }
}

void PID::setOutputLimits(double Min, double Max){
  if(Min >= Max) return;
  outMin = Min;
  outMax = Max;
  if(inAuto){
    if(outputValue > outMax) outputValue = outMax;
    else if(outputValue < outMin) outputValue = outMin;
    if(iTerm > outMax) iTerm = outMax;
    else if(iTerm < outMin) iTerm = outMin;
  }
}

void PID::setMode(int Mode){
  bool newAuto = Mode == AUTOMATIC;
  if(newAuto && !inAuto){
    this->initialize();
  }
  inAuto = newAuto;
}

void PID::setControllerDirection(int Direction){
  if(inAuto && Direction != controllerDirection){
    kpGain = (0 - kpGain);
    kiGain = (0 - kiGain);
    kdGain = (0 - kdGain);
  }
  controllerDirection = Direction;
}

void PID::initialize(void){
  lastInput = inputValue;
  iTerm = outputValue;
  if(iTerm > outMax) iTerm = outMax;
  else if(iTerm < outMin) iTerm = outMin;
}
