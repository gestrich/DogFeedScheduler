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
#include "Led.hpp"
#include <stdio.h>

class WaterMonitor {
public:
    WaterMonitor(bool waterAlert){
        alertForWater = waterAlert;
    }
    Led powerOutput = Led(18);
    bool alertForWater;
    void checkForEvents();
};


#endif /* WaterMonitor_hpp */
