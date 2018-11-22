//
//  WasherEventWindow.cpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 11/18/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#include "WasherEventWindow.hpp"

bool WasherEventWindow::operator == (const WasherEventWindow & other){
    if((startTime == other.startTime) && (seconds == other.seconds)){
        return true;
    } else {
        return false;
    }
}
