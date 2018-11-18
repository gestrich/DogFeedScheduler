//
//  WasherMonitor.hpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 11/18/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#ifndef WasherMonitor_hpp
#define WasherMonitor_hpp

#include "InputDevice.hpp"

#include <stdio.h>

class WasherMonitor {
public:
    WasherMonitor();  
    InputDevice knockSensor;
    void updatePins();
};


#endif /* WasherMonitor_hpp */
