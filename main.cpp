/*
 *	main.cpp
 *
 *	MSU STARX Exosuit
 *	Software Version 2.3
 *	Created on: September 30, 2018
 *	All rights reserved
 */

// Local includes
#include "exosuit.h"

ExoSuit sparty;

int main(){
    sparty.initialize();
    while(1) {
        sparty.updateADC();
        sparty.updateSensors();
        sparty.updatePressurePID();
        sparty.updatePWM();
    }
    return 0;
}
