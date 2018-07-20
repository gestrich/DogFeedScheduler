//
//  DateTimeUtilities.hpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 7/20/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#ifndef DateTimeUtilities_hpp
#define DateTimeUtilities_hpp

#include <stdio.h>

#include <ctime>

class DateTimeUtilities {
public:
    static int dayFromTime(time_t timeVal);
    static int hourFromTime(time_t timeVal);
    static int currentHourIndex();
};


#endif /* DateTimeUtilities_hpp */
