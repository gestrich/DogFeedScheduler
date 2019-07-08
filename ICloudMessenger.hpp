//
//  ICloudMessenger.hpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 11/16/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#ifndef ICloudMessenger_hpp
#define ICloudMessenger_hpp

#include <stdio.h>
#include <string>

using namespace std;

class ICloudMessenger {
public:
    static void sendMessage(std::string message, std::string number);
    static void sendIMessage(std::string message, std::string number);
};

#endif /* ICloudMessenger_hpp */
