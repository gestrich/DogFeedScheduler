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
        sendiCloudMessage(std::to_string(newValue), "4123773856"); 

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

void FeedingKeyValueStore::sendiCloudMessage(std::string message, std::string number){
    system("ssh 'bill@billgesichsipro.fios-router.home' \"osascript ~/Desktop/shortcuts/message.scpt '4123773856' 'AUTOMATED: Completed Feeding Changed'\"");
}    
