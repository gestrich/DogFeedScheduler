//
//  FeedingScheduler.hpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 7/20/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#ifndef FeedingScheduler_hpp
#define FeedingScheduler_hpp

#include <stdio.h>
#include <vector>
#include "InputDevice.hpp"
#include "SevenSegmentDisplay.hpp"
#include "Led.hpp"
#include "InputEvent.hpp"

class FeedingScheduler {
public:
    std::vector<InputEvent> events;
    int idealFeedingCountNow();
    int completedFeedingsNow();
    void updatePins();  
    InputDevice door;    
    SevenSegementDisplay segmentDisplay;
    Led led1;  
};

#endif /* FeedingScheduler_hpp */
