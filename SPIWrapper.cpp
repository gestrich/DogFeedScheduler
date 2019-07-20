//
//  SPIWrapper.cpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 7/20/19.
//  Copyright © 2019 Bill Gestrich. All rights reserved.
//

#include "SPIWrapper.hpp"

#if !defined(SPI_DISABLED)
#include "libraries/RaspberryPi-mcp3008Spi/mcp3008Spi.h"
#endif

SpiWrapper::SpiWrapper(){
    
}

int SpiWrapper::test(){
    int a2dVal = 0;

#if !defined(SPI_DISABLED)
    mcp3008Spi a2d("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);
    int a2dChannel = 0;
    unsigned char data[3];
    bool eventTriggered = false;
    data[0] = 1;  //  first byte transmitted -> start bit
    data[1] = 0b10000000 |( ((a2dChannel & 7) << 4)); // second byte transmitted -> (SGL/DIF = 1, D2=D1=D0=0)
    data[2] = 0; // third byte transmitted....don't care
    
    a2d.spiWriteRead(data, sizeof(data) );
    
    a2dVal = 0;
    a2dVal = (data[1]<< 8) & 0b1100000000; //merge data[1] & data[2] to get result
    a2dVal |=  (data[2] & 0xff);
    
#else
    puts("Spi disabled");
#endif

    return a2dVal;
    
}
