//
//  WaterMonitor.cpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 11/18/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#include "WaterMonitor.hpp"
#include "ICloudMessenger.hpp"
#include "libraries/RaspberryPi-mcp3008Spi/mcp3008Spi.h"

WaterMonitor::WaterMonitor()
:knockSensor(18){
}

void WaterMonitor::checkForEvents(){

    mcp3008Spi a2d("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);
    int a2dVal = 0;
    int a2dChannel = 0;
    unsigned char data[3];
	bool eventTriggered = false;

    while(true)
    {
        data[0] = 1;  //  first byte transmitted -> start bit
        data[1] = 0b10000000 |( ((a2dChannel & 7) << 4)); // second byte transmitted -> (SGL/DIF = 1, D2=D1=D0=0)
        data[2] = 0; // third byte transmitted....don't care

        a2d.spiWriteRead(data, sizeof(data) );

        a2dVal = 0;
	a2dVal = (data[1]<< 8) & 0b1100000000; //merge data[1] & data[2] to get result
	a2dVal |=  (data[2] & 0xff);
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
