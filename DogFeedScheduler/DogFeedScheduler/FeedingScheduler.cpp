//
//  FeedingScheduler.cpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 7/20/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#include "FeedingScheduler.hpp"
#include <string>

#include "FeedingKeyValueStore.hpp"

using namespace std;

void testCcallback(void) {
//    puts("Callback called");
}

FeedingScheduler::FeedingScheduler()
:door(25), decrementButton(6), led1(18){
    WiringPiWrapper::registerCallback(decrementButton.gpioIndex, EdgeFalling, &testCPlusPlusFunction);
    segmentDisplay = SevenSegementDisplay();
}

int FeedingScheduler::idealFeedingCountToday(){
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

int FeedingScheduler::completedFeedingCountToday(){
    int total = 0;
    for (auto event: events) {
        if (event.today() == true) {
            printf("Is today = True");
            fflush(stdout);
            total++;
        } else {
            printf("Is today = false");
            fflush(stdout);            
        }
    }
    return total;
}

void FeedingScheduler::updatePins(){
    int completed = completedFeedingCountToday();
    
    printf("Completed feedings = %u\n", completed);
    fflush(stdout);
    
    FeedingKeyValueStore feedingsCompletedStore = FeedingKeyValueStore("feedingsComplete");
    feedingsCompletedStore.updateValue(std::to_string(completed));
    
    int ideal = idealFeedingCountToday();
    int feedingsDueAsInt = ideal - completed;
    
    FeedingKeyValueStore feedingsDueStore = FeedingKeyValueStore("feedingsDue");
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
        if(previousFeedingsDueAsInt < feedingsDueAsInt){
            //Increased
            std::string message = std::string("The babies are hungry.");
            feedingsDueStore.sendiCloudMessage(message, "4123773856"); //Alert   
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
    if(decrementEvent && decrementEvent->eventType == LowToHigh && events.empty() == false){
        events.pop_back();
    }
    
}
