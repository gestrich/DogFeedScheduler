//
//  FeedingScheduler.cpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 7/20/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#include "FeedingScheduler.hpp"
#include <string>

#include <sstream>
#include <fstream> 
#include <unistd.h>
#include <pwd.h>


void testCcallback(void) {
    puts("Callback called");
}

FeedingScheduler::FeedingScheduler()
:door(25), decrementButton(6), led1(18){
    WiringPiWrapper::registerCallback(decrementButton.gpioIndex, EdgeFalling, &testCPlusPlusFunction);
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
    const char *homedir;
    
    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }
    
    std::string path = std::string(homedir) + "/Desktop/completedFeedings.txt";
    
    //Read feedings
    std::ifstream inputStream(path);
    std::stringstream buffer;
    buffer << inputStream.rdbuf();
    std::string fileContents = buffer.str();
    
    inputStream.close();

    std::string intAsString = std::to_string(completed);
    
    //Write feedings if changed
    if(intAsString != fileContents){
        std::ofstream outputStream(path);
        if(outputStream.is_open())   
        {
            outputStream << intAsString;       
        }
        else    
        {
            //Error
        }
        
        outputStream.close();
        system("ssh 'bill@billgesichsipro.fios-router.home' \"osascript ~/Desktop/shortcuts/message.scpt '4123773856' 'AUTOMATED: Completed Feeding Changed'\"");
    }    
    
    int ideal = idealFeedingCountNow();
    int dueFeedings = ideal - completed;
    segmentDisplay.showDigit(completed % 10);
    
    bool doorOpened = door.high();
    InputEvent *doorEvent = door.checkForEvent();
    
    if(doorEvent && doorEvent->eventType == LowToHigh){
        events.push_back(*doorEvent);
    }
    
    if(doorOpened){
        led1.setMode(LedBlink); //blinking for open door
    } else if (dueFeedings > 0) {
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
