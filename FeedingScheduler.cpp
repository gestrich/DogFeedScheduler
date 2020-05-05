//
//  FeedingScheduler.cpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 7/20/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#include "FeedingScheduler.hpp"
#include <string>
#include "ICloudMessenger.hpp"
#include "FeedingKeyValueStore.hpp"
#include "unistd.h"

using namespace std;

void testCcallback(void) {
//    puts("Callback called");
}

FeedingScheduler::FeedingScheduler()
:door(5), decrementButton(25), led1(27){
    WiringPiWrapper::registerCallback(decrementButton.gpioIndex, EdgeFalling, &testCPlusPlusFunction);
    segmentDisplay = SevenSegementDisplay();
}

int FeedingScheduler::idealFeedingCountToday(){
    int currentHour = DateTimeUtilities::currentHourIndex();
    if (currentHour >= 0 && currentHour <= 5){
        return 0; //Early Morning - no feeding
    } else if (currentHour < 12){
        return 1; //Morning
    } else if (currentHour < 18){
        return 2; //Afternoon
    } else {
        return 3; //Evening
    }
}

int FeedingScheduler::completedFeedingCountToday(){
    int total = 0;
    for (auto event: events) {
        if (event.today() == true) {
            total++;
        }
    }
    return total;
}

void FeedingScheduler::updatePins(){
    int completed = completedFeedingCountToday();
    FeedingKeyValueStore feedingsCompletedStore = FeedingKeyValueStore("feedingsComplete.txt");
    feedingsCompletedStore.updateValue(std::to_string(completed));
    
    int ideal = idealFeedingCountToday();
    int feedingsDueAsInt = ideal - completed;
    
    FeedingKeyValueStore feedingsDueStore = FeedingKeyValueStore("feedingsDue.txt");
    std::string previousFeedingsDueAsString = feedingsDueStore.getValue();
    std::string feedingsDueAsString = std::to_string(feedingsDueAsInt);
    
    int previousFeedingsDueAsInt = 0;
    try {
        previousFeedingsDueAsInt = stoi(previousFeedingsDueAsString);
    }
    catch(...) {
        previousFeedingsDueAsInt = 0;
    }
    
    if(previousFeedingsDueAsInt != feedingsDueAsInt){
        feedingsDueStore.updateValue(feedingsDueAsString);
        if(feedingsDueAsInt > 0 && (previousFeedingsDueAsInt < feedingsDueAsInt)){
            //Increased    
            int currentHour = DateTimeUtilities::currentHourIndex();
            if(currentHour >= 8){
                //std::string message = std::string("The babies are hungry.");
                //ICloudMessenger::sendMessage(message, "4123773856"); //Alert
            }
        }
    }

    segmentDisplay.showDigit(completed % 10);
    
    bool doorOpened = door.high();
    InputEvent *doorEvent = door.checkForEvent();
    
    if(doorEvent && doorEvent->eventType == LowToHigh){
        events.push_back(*doorEvent);
    }
    
    if(doorOpened){
        led1.setMode(LedBlink); //blinking for open door
    } else if (feedingsDueAsInt > 0) {
        led1.setMode(LedSolid); //solid for feeding due
    } else {
        led1.setMode(LedOff); //off for all good
    }
    
    led1.updatePinOutput();
    
    InputEvent *decrementEvent = decrementButton.checkForEvent();
    if(decrementEvent && decrementEvent->eventType == HighToLow && events.empty() == false){
        events.pop_back();
    }
    
}
