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
#include "WasherEventWindow.hpp"

#include <stdio.h>

class WasherMonitor {
    WasherEventWindow lastRecordedWindow;
    WasherEventWindow currentWindow();
public:
    WasherMonitor();  
    InputDevice knockSensor;
    void checkForEvents();
};


#endif /* WasherMonitor_hpp */
