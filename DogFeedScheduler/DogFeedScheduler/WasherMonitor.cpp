//
//  WasherMonitor.cpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 11/18/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#include "WasherMonitor.hpp"
#include "ICloudMessenger.hpp"

#define EVENT_COUNT_TRIGGERING_CYCLE 500
#define EVENT_WINDOW_SECONDS 60

WasherMonitor::WasherMonitor()
:knockSensor(18), lastRecordedWindow(time(0), EVENT_WINDOW_SECONDS){
}

void WasherMonitor::checkForEvents(){
    InputEvent *knockSensorEvent = knockSensor.checkForEvent();
    if(knockSensorEvent && knockSensorEvent->eventType == LowToHigh){
//        puts("Knock sensor event occurred");
        
        WasherEventWindow current = currentWindow();
        if(current == lastRecordedWindow){
            //Same window - track event
            
            lastRecordedWindow.eventCount++;
            
            if(lastRecordedWindow.eventCount >= EVENT_COUNT_TRIGGERING_CYCLE){
                state = CYCLE;
                puts("State set to CYCLE");
            }
        } else {
            //New window
            
            if(state == CYCLE){
                //Already cycling
                
                if(lastRecordedWindow.isOtherWindowAdjacent(current)){
                    //Assume still in cycle when events occur between adjacent windows.
                } else {
                    //Break in windows since last event.
                    //Assume Lid was opened.
                    puts("State set to None after lid opened.");
                    state = NONE;
                    static bool messageSent = false;
                    if(messageSent == false){
                        ICloudMessenger().sendMessage("Washer needs emptied", "4123773856");
                        messageSent = true;
                    }
                }
            } else {
                //First event so not in cycle mode yet.
            }
            
            printf("starting new window. Old window count = %d\n", lastRecordedWindow.eventCount);
            lastRecordedWindow = current;
            lastRecordedWindow.eventCount++;
        }
    }
}

WasherEventWindow WasherMonitor::currentWindow(){
    time_t startTime = time(0);
    return WasherEventWindow(startTime, EVENT_WINDOW_SECONDS);
}
