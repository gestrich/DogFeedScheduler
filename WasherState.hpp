//
//  WasherState.hpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 11/22/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#ifndef WasherState_hpp
#define WasherState_hpp

#include <stdio.h>
#include <ctime>

    enum washer_state_value {
    NONE,
    CYCLE
};

class WasherState {
    //Private Definitions
public:
    WasherState(){
        stateValue = NONE;
    };
    WasherState(washer_state_value & stateValueArg){
        stateValue  = stateValueArg;
    };
    
    time_t stateBeginTime = time(0);
    time_t stateLastMovement = 0;
    washer_state_value stateValue;
    
};

#endif /* WasherState_hpp */
