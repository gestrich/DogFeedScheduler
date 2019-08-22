//
//  SimpleMovementMonitor.hpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 11/18/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#ifndef SimpleMovementMonitor_hpp
#define SimpleMovementMonitor_hpp

#include "InputDevice.hpp"
#include "WasherEventWindow.hpp"
#include "WasherState.hpp"

#include <stdio.h>

class SimpleMovementMonitor {
    time_t lastMotionTime;
public:
    SimpleMovementMonitor();
    InputDevice knockSensor;
    void checkForEvents();
};


#endif /* SimpleMovementMonitor_hpp */
