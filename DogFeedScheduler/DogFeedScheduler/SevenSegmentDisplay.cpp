//
//  SevenSegmentDisplay.cpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 7/20/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#include "SevenSegmentDisplay.hpp"
#include "WiringPiWrapper.hpp"


void SevenSegementDisplay::showDigit(int digit){
    fflush(stdout); 
    WiringPiWrapper::writePi(top, false);
    WiringPiWrapper::writePi(topLeft, false);
    WiringPiWrapper::writePi(topRight, false);
    WiringPiWrapper::writePi(middle, false);
    WiringPiWrapper::writePi(bottomLeft, false);
    WiringPiWrapper::writePi(bottomRight, false);
    WiringPiWrapper::writePi(bottom, false);
    WiringPiWrapper::writePi(dot, false);
    
    //top
    if ((digit == 0) || (digit == 2) || (digit == 3) || (digit == 5) || (digit == 6) || (digit == 7) || (digit == 8) || (digit == 9)){
        WiringPiWrapper::writePi(top, true);
    }
    
    //top left
    if ((digit == 0) || (digit == 4) || (digit == 5) || (digit == 6) || (digit == 7) || (digit == 8) || (digit == 9)){
        WiringPiWrapper::writePi(topLeft, true);
    }
    
    //top right 
    if ((digit == 0) || (digit == 1) || (digit == 2) || (digit == 3) || (digit == 4) || (digit == 7) || (digit == 8) || (digit == 9)){
        WiringPiWrapper::writePi(topRight, true);
    }
    
    //middle 
    if ((digit == 2) || (digit == 3) || (digit == 4) || (digit == 5) || (digit == 6) || (digit == 8) || (digit == 9)){
        WiringPiWrapper::writePi(middle, true);
    }
    
    //bottom left 
    if ((digit == 0) || (digit == 2) || (digit == 6) || (digit == 8)){
        WiringPiWrapper::writePi(bottomLeft, true);
    }
    
    //bottom right 
    if ((digit == 0) || (digit == 1) || (digit == 3) || (digit == 4) || (digit == 5) || (digit == 6) || (digit == 7) || (digit == 8) || (digit == 9)){
        WiringPiWrapper::writePi(bottomRight, true);
    }
    
    //bottom 
    if ((digit == 0) || (digit == 2) || (digit == 3) || (digit == 5) || (digit == 6) || (digit == 8)){
        WiringPiWrapper::writePi(bottom, true);
    }
}
