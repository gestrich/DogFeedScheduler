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

void FeedingKeyValueStore::updateValue(std::string newValue){
    
    //Write feedings if changed
    if(newValue != getValue()){

        std::ofstream outputStream(path(), std::ios::binary);
        if(outputStream.is_open())   
        {
            outputStream << newValue;       
        }
        else    
        {
            //Error
        }
        
        outputStream.close();
    }
}

std::string FeedingKeyValueStore::getValue(){
    std::ifstream inputStream(path());
    std::stringstream buffer;
    buffer << inputStream.rdbuf();
    std::string fileContents = buffer.str();
    inputStream.close();
    return fileContents;    
}

std::string FeedingKeyValueStore::path(){
    const char *homedir;
    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }
    
    std::string path = std::string(homedir) + "/Desktop/" + key;
    return path;    
}    
