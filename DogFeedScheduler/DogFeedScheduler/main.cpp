#include <iostream>


#include <stdio.h>
#include <stdlib.h>
#include "WiringPiWrapper.hpp"
#include "InputDevice.hpp"
#include "SevenSegmentDisplay.hpp"
#include "Led.hpp"
#include "FeedingScheduler.hpp"




int main (void)
{
    printf("***Starting Feeding Scheduler***\n");
    
    FeedingScheduler scheduler = FeedingScheduler();
    WiringPiWrapper::setupGPIO();
    
    scheduler.led1 = Led();
    scheduler.led1.gpioIndex = 18;
    scheduler.door = InputDevice();
    scheduler.door.gpioIndex = 25;
    
    scheduler.segmentDisplay = SevenSegementDisplay();

    WiringPiWrapper::setPinModePi(scheduler.segmentDisplay.top, true);
    WiringPiWrapper::setPinModePi(scheduler.segmentDisplay.topLeft, true);
    WiringPiWrapper::setPinModePi(scheduler.segmentDisplay.topRight, true);
    WiringPiWrapper::setPinModePi(scheduler.segmentDisplay.middle, true);
    WiringPiWrapper::setPinModePi(scheduler.segmentDisplay.bottomLeft, true);
    WiringPiWrapper::setPinModePi(scheduler.segmentDisplay.bottomRight, true);
    WiringPiWrapper::setPinModePi(scheduler.segmentDisplay.bottom, true);
    WiringPiWrapper::setPinModePi(scheduler.segmentDisplay.dot, true);
    
    while(true) {
        scheduler.updatePins();
        //delay(1000);
    }
    
    return 0;
    
}
