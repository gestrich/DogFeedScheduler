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
    return DateTimeUtilities::dayFromTime(time(0)) == DateTimeUtilities::dayFromTime(pressTime) &&
    DateTimeUtilities::monthFromTime(time(0)) == DateTimeUtilities::monthFromTime(pressTime) &&
    DateTimeUtilities::yearFromTime(time(0)) == DateTimeUtilities::yearFromTime(pressTime);
}
