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

    
    while(true) {
        scheduler.updatePins();
        //delay(1000);
    }
    
    return 0;
    
}
