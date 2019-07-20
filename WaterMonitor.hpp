//
//  WaterMonitor.hpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 11/18/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#ifndef WaterMonitor_hpp
#define WaterMonitor_hpp

#include "InputDevice.hpp"

#include <stdio.h>
/*InputDevice(int index){
    WiringPiWrapper::setupGPIO();
    gpioIndex = index;
    WiringPiWrapper::setPinModePi(index, false);
    lastProcessedWasHigh = high();
};
int gpioIndex = 0;
*/
class WaterMonitor {
public:
    WaterMonitor(bool waterAlert){
        alertForWater = waterAlert;
    }
    bool alertForWater;
    void checkForEvents();
};


#endif /* WaterMonitor_hpp */
