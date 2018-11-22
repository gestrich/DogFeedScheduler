//
//  Led.cpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 7/20/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#include "Led.hpp"
#include "WiringPiWrapper.hpp"
#include <unistd.h>

Led::Led(int index){
    WiringPiWrapper::setupGPIO();
    gpioIndex = index;
    WiringPiWrapper::setPinModePi(index, true);
}

LEDMode Led::getMode(){
    return mode;
}

void Led::setMode(LEDMode newMode){
    mode = newMode;
    updatePinOutput();
}

void Led::updatePinOutput(){
    if (mode == LedOff){
        WiringPiWrapper::writePi (gpioIndex, false);
    } else if (mode == LedBlink){
        if (WiringPiWrapper::readPi(gpioIndex)){
            WiringPiWrapper::writePi (gpioIndex, false);
        } else {
            WiringPiWrapper::writePi (gpioIndex, true);
        }
        
        int microsecondToSleep = 200;
        static int nanosecondsInMicrosecond = 1000;
        usleep(microsecondToSleep * nanosecondsInMicrosecond); //usleep is in nanoseconds
    } else if (mode == LedSolid){
        WiringPiWrapper::writePi (gpioIndex, true);
    }
}
