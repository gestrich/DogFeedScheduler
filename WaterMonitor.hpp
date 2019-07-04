//
//  WaterMonitor.hpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 11/18/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#ifndef WaterMonitor_hpp
#define WaterMonitor_hpp

#include "InputDevice.hpp"

#include <stdio.h>

class WaterMonitor {
public:
    WaterMonitor();  
    InputDevice knockSensor;
    void checkForEvents();
};


#endif /* WaterMonitor_hpp */
