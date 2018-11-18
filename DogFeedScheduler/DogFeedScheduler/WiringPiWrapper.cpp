//
//  WiringPiWrapper.cpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 7/20/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#include "WiringPiWrapper.hpp"

#if !defined(WIRING_PI_DISABLED)
#include <wiringPi.h>
#endif


//Raspberry Pi Wrappers

void WiringPiWrapper::setupGPIO(){
    
    
    static bool initialized;
    if (!initialized) {
        initialized = true;
#if !defined(WIRING_PI_DISABLED)
        wiringPiSetupGpio ();
        puts("Wiring Pi Enabled");
#else
        puts("Wiring Pi Disabled");
#endif
    }
    

    
}

void WiringPiWrapper::setPinModePi(int gpio_index, bool output){
    
#if !defined(WIRING_PI_DISABLED)
    if (output == true){
        pinMode(gpio_index, OUTPUT);        
    } else {
        pinMode(gpio_index, INPUT);
    }
#endif
    
}

void WiringPiWrapper::writePi(int gpio_index, bool high){
    
#if !defined(WIRING_PI_DISABLED)
    if(high){
        digitalWrite(gpio_index, HIGH);        
    } else {
        digitalWrite(gpio_index, LOW);
    }
#endif
    
}

bool WiringPiWrapper::readPi(int gpio_index){
    
    bool toRet = false;
#if !defined(WIRING_PI_DISABLED)
    toRet = digitalRead(gpio_index);
#endif
    return toRet;
}

void WiringPiWrapper::registerCallback(int gpio_pin, EdgeType edgeType, void (*function)(void)){
#if !defined(WIRING_PI_DISABLED)
    //INT_EDGE_FALLING, INT_EDGE_RISING, INT_EDGE_BOTH or INT_EDGE_SETUP
    int edgeTypeInt =  INT_EDGE_FALLING;
    switch (edgeType){
        case EdgeFalling:
            edgeTypeInt =  INT_EDGE_FALLING;
            break;
        case EdgeRising:
            edgeTypeInt =  INT_EDGE_RISING;
            break;
        case EdgeBoth:
            edgeTypeInt =  INT_EDGE_BOTH;
            break;
        case EdgeSetup:
            edgeTypeInt =  INT_EDGE_SETUP;
            break;
        default:
            puts("Unknown edge type");
    }
    
    wiringPiISR(gpio_pin, edgeTypeInt, function);
#endif    
}
