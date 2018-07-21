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
}

void Led::updateState(int updatedState){
    state = updatedState;
}

void Led::updatePinOutput(){
    if (state == 0){
        WiringPiWrapper::writePi (gpioIndex, false);
    } else if (state == 1){
        if (WiringPiWrapper::readPi(gpioIndex)){
            WiringPiWrapper::writePi (gpioIndex, false);
        } else {
            WiringPiWrapper::writePi (gpioIndex, true);
        }
        
        sleep(1.0);
    } else if (state == 2){
        WiringPiWrapper::writePi (gpioIndex, true);
    }
}
