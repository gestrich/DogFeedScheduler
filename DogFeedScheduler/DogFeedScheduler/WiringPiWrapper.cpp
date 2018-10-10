//
//  WiringPiWrapper.cpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 7/20/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#include "WiringPiWrapper.hpp"

#define RASPBERRY_PI 1 

#if RASPBERRY_PI
#include <wiringPi.h>
#endif


//Raspberry Pi Wrappers

void WiringPiWrapper::setupGPIO(){
    
#if RASPBERRY_PI
    
    static bool initialized;
    if (!initialized) {
        puts("setting up wiring pi");
        initialized = true;
        wiringPiSetupGpio ();
    }
    
#endif
    
}

void WiringPiWrapper::setPinModePi(int gpio_index, bool output){
    
#if RASPBERRY_PI
    if (output == true){
        pinMode(gpio_index, OUTPUT);        
    } else {
        pinMode(gpio_index, INPUT);
    }
#endif
    
}

void WiringPiWrapper::writePi(int gpio_index, bool high){
    
#if RASPBERRY_PI
    if(high){
        digitalWrite(gpio_index, HIGH);        
    } else {
        digitalWrite(gpio_index, LOW);
    }
#endif
    
}

bool WiringPiWrapper::readPi(int gpio_index){
    
    bool toRet = false;
#if RASPBERRY_PI
    toRet = digitalRead(gpio_index);
#endif
    return toRet;
}

void WiringPiWrapper::registerCallback(int gpio_pin, EdgeType edgeType, void (*function)(void)){
#if RASPBERRY_PI
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
