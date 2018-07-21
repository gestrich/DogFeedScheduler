//
//  InputDevice.cpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 7/20/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#include "InputDevice.hpp"
#include "WiringPiWrapper.hpp"

InputEvent * InputDevice::checkForEvent(){

    bool currentlyHigh = high();
    if (currentlyHigh != lastProcessedWasHigh){
        //Door has been opened. Record the event.
        lastProcessedWasHigh = currentlyHigh;
        InputEvent event = InputEvent();
        if (currentlyHigh){
            event.eventType = LowToHigh;    
        } else {
            event.eventType = HighToLow;
        }
         
        return new InputEvent();
        
    } else {
        return nullptr;
    }
}

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
