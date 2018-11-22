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
#define EVENT_WINDOW_SECONDS 600
#define SECONDS_BEFORE_ALERTING 60*10

WasherMonitor::WasherMonitor()
:knockSensor(18), lastRecordedWindow(time(0), EVENT_WINDOW_SECONDS){
}

void WasherMonitor::checkForEvents(){
    InputEvent *knockSensorEvent = knockSensor.checkForEvent();
    if(knockSensorEvent && knockSensorEvent->eventType == LowToHigh){
//        puts("Knock sensor event occurred");
        
        time_t timeNow = time(0);
        if(lastRecordedWindow.windowIncludesTime(timeNow)){
            //Last window still active - track event
            if(lastRecordedWindow.eventCount >= EVENT_COUNT_TRIGGERING_CYCLE){
                washer_state_value cycleArg = CYCLE;
                lastState = WasherState(cycleArg);
                puts("State set to CYCLE");
            }
        } else {
            //New window
            WasherEventWindow newWindow = WasherEventWindow(timeNow, EVENT_WINDOW_SECONDS);
            if(lastState.stateValue == CYCLE){
                //Already cycling
                
                if(lastRecordedWindow.isOtherWindowAdjacent(newWindow)){
                    //Assume still in cycle when events occur between adjacent windows.
                } else {
                    //Break in windows since last event.
                    //Assume Lid was opened.
                    puts("State set to None after lid opened.");
                    washer_state_value cycleArg = NONE;
                    lastState = WasherState(cycleArg);
                    static bool messageSent = false;
                    if(messageSent == false){
                        ICloudMessenger().sendMessage("Washer likely just emptied", "4123773856");
                        messageSent = true;
                    }
                }
            } else {
                //First event so not in cycle mode yet.
            }
            
            printf("starting new window. Old window count = %d\n", lastRecordedWindow.eventCount);
            lastRecordedWindow = newWindow;
        }
        
        lastRecordedWindow.eventCount++;
        lastState.stateLastMovement = timeNow;
    } else {
        //No movement, check if message needs delivered

        if(lastState.stateValue == CYCLE){
            time_t timeNow = time(0);
            time_t minimumTimeToAlert = lastState.stateLastMovement + SECONDS_BEFORE_ALERTING;
            
            if(timeNow >= minimumTimeToAlert){
                static bool messageSent = false;
                if(messageSent == false){
                    ICloudMessenger().sendMessage("Washer needs emptied", "4123773856");
                    messageSent = true;
                }
            }
        }
    }
}
