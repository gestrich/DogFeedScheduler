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

void FeedingKeyValueStore::sendiCloudMessage(std::string message, std::string number){
    int maxMessages = 150;
    static int messagesSent = 0;
    if(messagesSent > maxMessages){
        return;
    }
    messagesSent++;
    std::string sshFirstPath = "ssh 'bill@billgesichsipro.fios-router.home' \"osascript ~/Desktop/shortcuts/message.scpt ";
    std::string recipientPart = std::string("'") + number + std::string("' ");
    std::string messagePart = std::string("'") + message + std::string("'");
    std::string endPart = " \"";
    std::string fullCommand = sshFirstPath + recipientPart + messagePart + endPart;
    printf("%s", fullCommand.c_str());
    fflush( stdout );
    system(fullCommand.c_str());
}    
