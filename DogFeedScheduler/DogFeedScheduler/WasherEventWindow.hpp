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
    WasherEventWindow(time_t thisStartTime, int theseSeconds){
        startTime = thisStartTime;
        seconds = thisStartTime + theseSeconds;
    };
    time_t startTime = 0;
    time_t seconds = 0;
    int eventCount = 0;
    bool isOtherWindowAdjacent(const WasherEventWindow& other);
    bool windowIncludesTime(time_t timeToCheck);
    bool operator==(const WasherEventWindow& other );
    
};

#endif /* WasherEventWindow_hpp */
