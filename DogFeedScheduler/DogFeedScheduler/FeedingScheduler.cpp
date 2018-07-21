//
//  FeedingScheduler.cpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 7/20/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#include "FeedingScheduler.hpp"
//#include "DateTimeUtilities.h"

FeedingScheduler::FeedingScheduler()
:door(25), decrementButton(6), led1(18){
    
    segmentDisplay = SevenSegementDisplay();
    
    WiringPiWrapper::setPinModePi(segmentDisplay.top, true);
    WiringPiWrapper::setPinModePi(segmentDisplay.topLeft, true);
    WiringPiWrapper::setPinModePi(segmentDisplay.topRight, true);
    WiringPiWrapper::setPinModePi(segmentDisplay.middle, true);
    WiringPiWrapper::setPinModePi(segmentDisplay.bottomLeft, true);
    WiringPiWrapper::setPinModePi(segmentDisplay.bottomRight, true);
    WiringPiWrapper::setPinModePi(segmentDisplay.bottom, true);
    WiringPiWrapper::setPinModePi(segmentDisplay.dot, true);
}

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
    InputEvent *doorEvent = door.checkForEvent();
    
    if(doorEvent && doorEvent->eventType == LowToHigh){
        events.push_back(*doorEvent);
    }
    
    if(doorOpened){
        led1.updateState(1); //blinking for open door
    } else if (dueFeedings > 0) {
        led1.updateState(2); //solid for feeding due
    } else {
        led1.updateState(0); //off for all good
    }
    
    led1.updatePinOutput();
    
    InputEvent *decrementEvent = decrementButton.checkForEvent();
    
    if(decrementEvent && decrementEvent->eventType == LowToHigh){
        puts("Button Pressed");
    }
}
