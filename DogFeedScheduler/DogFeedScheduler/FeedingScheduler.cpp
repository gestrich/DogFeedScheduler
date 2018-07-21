//
//  FeedingScheduler.cpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 7/20/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#include "FeedingScheduler.hpp"
#include <string>

FeedingScheduler::FeedingScheduler()
:door(25), decrementButton(6), led1(18){
    
    segmentDisplay = SevenSegementDisplay();
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
                puts("Setting LED state to blink");
        led1.mode = LedBlink; //blinking for open door
    } else if (dueFeedings > 0) {
        puts( ("Setting LED state to solid. Due feedings = " + std::to_string(dueFeedings)).c_str());
        led1.mode = LedSolid; //solid for feeding due
    } else {
        puts("Setting LED state to off");
        led1.mode = LedOff; //off for all good
    }
    
    led1.updatePinOutput();
    
    InputEvent *decrementEvent = decrementButton.checkForEvent();
    
    if(decrementEvent && decrementEvent->eventType == LowToHigh){
        puts("Button Pressed");
    }
}