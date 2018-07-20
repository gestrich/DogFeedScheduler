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

class InputDevice {
public:
    int gpioIndex = 0;
    bool lastHigh;
    
    bool high();
    void setHigh(bool high);
    
};

#endif /* InputDevice_hpp */
