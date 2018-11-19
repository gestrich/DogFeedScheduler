//
//  WasherEventWindow.hpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 11/18/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#ifndef WasherEventWindow_hpp
#define WasherEventWindow_hpp

#include <stdio.h>
#include <ctime>

class WasherEventWindow {
    //Private Definitions
public:
    WasherEventWindow(time_t thisStartTime, time_t thisEndTime){
        startTime = thisStartTime;
        endTime = thisEndTime;
    };
    time_t startTime = 0;
    time_t endTime = 0;
    
};

#endif /* WasherEventWindow_hpp */
