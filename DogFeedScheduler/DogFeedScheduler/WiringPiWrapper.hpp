//
//  WiringPiWrapper.hpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 7/20/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#ifndef WiringPiWrapper_hpp
#define WiringPiWrapper_hpp

#include <stdio.h>

class WiringPiWrapper {
public:
    static void setupGPIO();
    static void setPinModePi(int gpio_index, bool output);
    static void writePi(int gpio_index, bool high);
    static bool readPi(int gpio_index);
};



#endif /* WiringPiWrapper_hpp */
