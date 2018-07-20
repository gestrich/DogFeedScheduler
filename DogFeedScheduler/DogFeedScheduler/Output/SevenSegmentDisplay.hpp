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

class SevenSegementDisplay {
public:
    int top = 20;
    int topLeft = 24;
    int topRight = 23;
    int middle = 16;
    int bottomLeft = 17;
    int bottomRight = 19;
    int bottom = 21;
    int dot = 26;
    void showDigit(int digit);
};

#endif /* SevenSegmentDisplay_hpp */
