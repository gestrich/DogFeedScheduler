//
//  InputDevice.hpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 7/20/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#ifndef InputDevice_hpp
#define InputDevice_hpp

#include <stdio.h>
#include "WiringPiWrapper.hpp"
#include "DateTimeUtilities.hpp"
#include "InputEvent.hpp"

class InputDevice {
    bool lastProcessedWasHigh;
public:
    InputDevice(int index){
        WiringPiWrapper::setupGPIO();
        gpioIndex = index;
        WiringPiWrapper::setPinModePi(index, false);
        lastProcessedWasHigh = high();
    };
    int gpioIndex = 0;
    InputEvent * checkForEvent();
    
    bool high();
    void setHigh(bool high);
    
};

#endif /* InputDevice_hpp */
