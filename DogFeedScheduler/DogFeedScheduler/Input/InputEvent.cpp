//
//  InputEvent.cpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 7/20/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#include "InputEvent.hpp"
#include "DateTimeUtilities.hpp"

bool InputEvent::today(){
    return DateTimeUtilities::dayFromTime(time(0)) == DateTimeUtilities::dayFromTime(pressTime); 
}

int InputEvent::minute(){
    struct tm* tm_info;
    tm_info = localtime(&pressTime);
    return tm_info->tm_sec;
}
