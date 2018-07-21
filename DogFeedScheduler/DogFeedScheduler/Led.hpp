//
//  Led.hpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 7/20/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#ifndef Led_hpp
#define Led_hpp

#include <stdio.h>
#include "WiringPiWrapper.hpp"
class Led {
public:
    Led(){
        WiringPiWrapper::setupGPIO();
    };
    int gpioIndex = 0;
    int state = 0; // 0=off, 1=blink, 2=steady
    void updateState(int updatedState);
    void updatePinOutput();
};

#endif /* Led_hpp */
