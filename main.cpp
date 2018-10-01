// MSU STARX Exosuit Software
// Version 2.0 (May 2, 2018)
// All rights reserved

#include "exosuit.h"

ExoSuit sparty;

int main(){
  sparty.initialize();
  while(1){
    sparty.updateADC();
    sparty.updateSensors();
    sparty.updatePressurePID();
    sparty.updatePWM();
  }
  //
  return 0;
}
