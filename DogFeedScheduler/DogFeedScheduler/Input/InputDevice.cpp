//
//  InputDevice.cpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 7/20/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#include "InputDevice.hpp"
#include "WiringPiWrapper.hpp"


bool InputDevice::high(){
    return (WiringPiWrapper::readPi(gpioIndex) == 1);
}

void InputDevice::setHigh(bool high){
    if (high == true){
        WiringPiWrapper::writePi (gpioIndex, true);
    } else {
        WiringPiWrapper::writePi (gpioIndex, false);
    }
}
