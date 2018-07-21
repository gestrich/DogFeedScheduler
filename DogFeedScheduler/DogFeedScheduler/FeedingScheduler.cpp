//
//  FeedingScheduler.cpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 7/20/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#include "FeedingScheduler.hpp"
//#include "DateTimeUtilities.h"


int FeedingScheduler::idealFeedingCountNow(){
    int currentHour = DateTimeUtilities::currentHourIndex();
    if (currentHour > 0 && currentHour < 5){
        return 0; //Early Morning - no feeding
    } else if (currentHour < 12){
        return 1; //Morning
    } else if (currentHour < 18){
        return 2; // Afternoon
    } else {
        return 3; //Midnight
    }
}

int FeedingScheduler::completedFeedingsNow(){
    int total = 0;
    for (auto event: events) {
        if (event.today() == true) {
            total++;
        }
    }
    return total;
}

void FeedingScheduler::updatePins(){
    int completed = completedFeedingsNow();
    int ideal = idealFeedingCountNow();
    int dueFeedings = ideal = completed;
    segmentDisplay.showDigit(completed % 10);
    
    bool doorOpened = door.high();
    InputEvent *event = door.checkForEvent();
    
    if(event && event->eventType == LowToHigh){
        events.push_back(*event);
    }
    
    if(doorOpened){
        led1.updateState(1); //blinking for open door
    } else if (dueFeedings > 0) {
        led1.updateState(2); //solid for feeding due
    } else {
        led1.updateState(0); //off for all good
    }
    
    led1.updatePinOutput();
}
