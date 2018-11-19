//
//  WasherMonitor.cpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 11/18/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#include "WasherMonitor.hpp"

/*
 FeedingScheduler::FeedingScheduler()
 :door(25), decrementButton(6), led1(18){
 WiringPiWrapper::registerCallback(decrementButton.gpioIndex, EdgeFalling, &testCPlusPlusFunction);
 segmentDisplay = SevenSegementDisplay();
 }
 */

WasherMonitor::WasherMonitor()
:knockSensor(18){
//    lastRecordedWindow = currentWindow();
}

void WasherMonitor::updatePins(){
    InputEvent *knockSensorEvent = knockSensor.checkForEvent();
    if(knockSensorEvent && knockSensorEvent->eventType == LowToHigh){
        puts("Knock sensor event occurred");
    }
    
    currentWindow();
}

WasherEventWindow WasherMonitor::currentWindow(){
    time_t startTime = time(0);
    time_t endTime = startTime + 1;
    return WasherEventWindow(startTime, endTime);
}
