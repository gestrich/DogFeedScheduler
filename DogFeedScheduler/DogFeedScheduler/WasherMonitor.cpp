//
//  WasherMonitor.cpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 11/18/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#include "WasherMonitor.hpp"

WasherMonitor::WasherMonitor()
:knockSensor(18){
}

void WasherMonitor::updatePins(){
    InputEvent *knockSensorEvent = knockSensor.checkForEvent();
    if(knockSensorEvent && knockSensorEvent->eventType == LowToHigh){
        puts("Knock sensor event occurred");
    }
    
}
