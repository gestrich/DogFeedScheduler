//
//  SimpleMovementMonitor.cpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 11/18/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#include "SimpleMovementMonitor.hpp"
#include "ICloudMessenger.hpp"

SimpleMovementMonitor::SimpleMovementMonitor()
: knockSensor(2){
}

void SimpleMovementMonitor::checkForEvents(){

    InputEvent *knockSensorEvent = knockSensor.checkForEvent();
    if(knockSensorEvent && knockSensorEvent->eventType == LowToHigh){
        puts("Knock sensor event occurred");
        time_t timeNow = time(0);
        lastMotionTime = timeNow;
    }
}
