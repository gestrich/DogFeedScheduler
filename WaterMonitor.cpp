//
//  WaterMonitor.cpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 11/18/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#include "WaterMonitor.hpp"
#include "ICloudMessenger.hpp"

WaterMonitor::WaterMonitor()
:knockSensor(18){
}

void WaterMonitor::checkForEvents(){
    InputEvent *knockSensorEvent = knockSensor.checkForEvent();
    if(knockSensorEvent && knockSensorEvent->eventType == LowToHigh){
        puts("Water sensor event occurred");
        ICloudMessenger().sendMessage("WATER EVENT DETECTED", "4123773856");
       puts("here" );
    } else if(knockSensorEvent && knockSensorEvent->eventType == HighToLow){
        puts("Water sensor event occurred");
        ICloudMessenger().sendMessage("WATER EVENT DETECTED", "4123773856");
       puts("here" );
    } else {
       puts("here but not event" );
        //No movement, check if message needs delivered
    }

}
