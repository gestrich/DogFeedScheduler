//
//  DateTimeUtilities.cpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 7/20/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#include "DateTimeUtilities.hpp"

int DateTimeUtilities::yearFromTime(time_t timeVal){
    struct tm* tm_info = localtime(&timeVal);
    return tm_info->tm_year;
}

int DateTimeUtilities::monthFromTime(time_t timeVal){
    struct tm* tm_info = localtime(&timeVal);
    return tm_info->tm_mon;
}

int DateTimeUtilities::dayFromTime(time_t timeVal){
    struct tm* tm_info = localtime(&timeVal);
    return tm_info->tm_mday;
}

int DateTimeUtilities::hourFromTime(time_t timeVal){
    struct tm* tm_info = localtime(&timeVal);
    return tm_info->tm_hour;
}

int DateTimeUtilities::currentHourIndex(){
    return hourFromTime(time(0));
}
