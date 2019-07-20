//
//  WaterMonitor.cpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 11/18/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#include "WaterMonitor.hpp"
#include "ICloudMessenger.hpp"
#include "SPIWrapper.hpp"
#include "unistd.h"
#include <iostream>



void WaterMonitor::checkForEvents(){
    
    time_t lastAlert = 0;
    int secondsBeforeAlerting = 60 * 60 * 3; // 3 hours
    int onThreshhold = 10;
    
    while(true)
    {
        int a2dVal = SpiWrapper::test();
        cout << "Current value is: " << a2dVal << endl;
        sleep(1);
        
        bool eventOccurred = false;
        if(this->alertForWater){
            if(a2dVal > onThreshhold){
                eventOccurred = true;
            }
        } else {
            if(a2dVal < onThreshhold){
                eventOccurred = true;
            }
        }
        
        if (eventOccurred){
            
            time_t timeNow = time(0);
            time_t earliestTimeToAlert = lastAlert + secondsBeforeAlerting;
            
            if(timeNow >= earliestTimeToAlert){
                std::string firstPart = this->alertForWater ? "HIGH " : "LOW ";
                std::string message = firstPart + "WATER EVENT DETECTED: " + std::to_string(a2dVal);
                cout << message << endl;
                ICloudMessenger().sendIMessage(message, "4123773856");
                ICloudMessenger().sendMessage(message, "4123773856");
                lastAlert = time(0);
            } else {
                cout << "Skipping alert as too early" << endl;
            }
        }
    }
    
}
