//
//  InputEvent.hpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 7/20/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#ifndef InputEvent_hpp
#define InputEvent_hpp

#include <stdio.h>
#include <ctime>

enum InputEventType {
    LowToHigh,
    HighToLow
};

class InputEvent {
public:
    bool today();
    time_t pressTime = time(0);
    int minute();
    InputEventType eventType;
};

#endif /* InputEvent_hpp */
