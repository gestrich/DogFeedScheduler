//
//  WasherEventWindow.cpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 11/18/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#include "WasherEventWindow.hpp"

bool WasherEventWindow::isOtherWindowAdjacent(const WasherEventWindow& other){
    if(seconds != other.seconds){
        return false;
    }
    
    time_t difference = 0;
    if(startTime > other.startTime){
        difference = startTime - other.startTime;
    } else {
        difference = other.startTime - startTime;
    }
    
    time_t secondsInTwoCycles = seconds * 2;
    if(difference < secondsInTwoCycles){
        return true;
    }
    
    return false;
    
//    if( startTime == (other.startTime + seconds)){
//        return true; //other is right before this one
//    }
//
//    if( (startTime + seconds) == (other.startTime)){
//        return true; //other is right after this one
//    }

//    return false;
}

bool WasherEventWindow::windowIncludesTime(time_t timeToCheck){
    time_t endTime = startTime + seconds;
    return startTime <= timeToCheck && endTime >= timeToCheck;
}

bool WasherEventWindow::operator == (const WasherEventWindow & other){
    if((startTime == other.startTime) && (seconds == other.seconds)){
        return true;
    } else {
        return false;
    }
}
