//
//  SevenSegmentDisplay.hpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 7/20/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#ifndef SevenSegmentDisplay_hpp
#define SevenSegmentDisplay_hpp

#include <stdio.h>
#include "WiringPiWrapper.hpp"

class SevenSegementDisplay {
public:
    SevenSegementDisplay();
    //Top Pin Row - middle is ground
    int middle = 16;
    int topLeft = 12;
    int top = 20;
    int topRight = 21;
   
    //Bottom Pin Row - middle likely another ground? 
    int bottomLeft = 6;
    int bottom = 13;
    int bottomRight = 19;
    int dot = 26;
    void showDigit(int digit);
};

#endif /* SevenSegmentDisplay_hpp */
