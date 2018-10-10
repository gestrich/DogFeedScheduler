//
//  FeedingKeyValueStore.hpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 10/9/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#ifndef FeedingKeyValueStore_hpp
#define FeedingKeyValueStore_hpp

#include <stdio.h>
#include <string>

class FeedingKeyValueStore {
public:
    FeedingKeyValueStore(std::string key){
        this->key = key;
        //other initializer defaults go here
    };
    std::string key = "";
    void updateValue(std::string newValue);
    std::string getValue();
    std::string path();
    void sendiCloudMessage(std::string message, std::string number);
};

#endif /* FeedingKeyValueStore_hpp */

