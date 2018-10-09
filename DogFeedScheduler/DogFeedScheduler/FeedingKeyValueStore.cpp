//
//  FeedingKeyValueStore.cpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 10/9/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#include "FeedingKeyValueStore.hpp"

#include <sstream>
#include <fstream> 
#include <unistd.h>
#include <pwd.h>

//FeedingKeyValueStore::FeedingKeyValueStore(std::string filename){}

void FeedingKeyValueStore::updateValue(int newValue){
    const char *homedir;
    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }
    
    std::string path = std::string(homedir) + "/Desktop/" + key;
    
    //Read feedings
    std::ifstream inputStream(path);
    std::stringstream buffer;
    buffer << inputStream.rdbuf();
    std::string fileContents = buffer.str();
    
    inputStream.close();
    
    std::string intAsString = std::to_string(newValue);
    
    //Write feedings if changed
    if(intAsString != fileContents){
        std::ofstream outputStream(path, std::ios::binary);
        if(outputStream.is_open())   
        {
            outputStream << intAsString;       
        }
        else    
        {
            //Error
        }
        
        outputStream.close();
    }    
}
