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

WaterMonitor::WaterMonitor()
:knockSensor(18){
}

void WaterMonitor::checkForEvents(){
    
    bool eventTriggered = false;
    
    while(true)
    {
        int a2dVal = SpiWrapper::test();
        sleep(1);
        if (a2dVal > 1){
            cout << "The Result is: " << a2dVal << endl;
            if (eventTriggered == false){
                ICloudMessenger().sendIMessage("WATER EVENT DETECTED", "4123773856");
                ICloudMessenger().sendMessage("WATER EVENT DETECTED", "4123773856");
            }
            eventTriggered = true;
        }
    }
    
}
