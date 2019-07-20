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
    
    bool eventTriggered = false;
    time_t lastAlert = 0;
    int secondsBeforeAlerting = 30;// 60 * 60 * 3; // 3 hours
    
    while(true)
    {
        int a2dVal = SpiWrapper::test();
        sleep(1);
        
        bool eventOccurred = false;
        if(this->alertForWater){
            if(a2dVal > 1){
                eventOccurred = true;
            }
        } else {
            if(a2dVal < 1){
                eventOccurred = true;
            }
        }
        
        if (eventOccurred){
            
            time_t timeNow = time(0);
            time_t earliestTimeToAlert = lastAlert + secondsBeforeAlerting;
            
            if(timeNow >= earliestTimeToAlert){
                cout << "Current value is: " << a2dVal << endl;
                std::string firstPart = this->alertForWater ? "High " : "Low";
                std::string message = firstPart + "WATER EVENT DETECTED: " + std::to_string(a2dVal);
                ICloudMessenger().sendIMessage(message, "4123773856");
                ICloudMessenger().sendMessage(message, "4123773856");
                lastAlert = time(0);
            } else {
                cout << "Skipping alert as too early" << endl;
            }
        }
    }
    
}
