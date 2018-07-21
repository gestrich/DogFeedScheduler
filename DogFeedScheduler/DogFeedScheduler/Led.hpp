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

enum LEDMode {
    LedOff,
    LedSolid,
    LedBlink
};

class Led {
public:
    Led(int index);
    int gpioIndex = 0;
    LEDMode mode = LedOff;
    void updatePinOutput();
};

#endif /* Led_hpp */
