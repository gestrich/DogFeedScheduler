//
//  ICloudMessenger.cpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 11/16/18.
//  Copyright © 2018 Bill Gestrich. All rights reserved.
//

#include "ICloudMessenger.hpp"

void ICloudMessenger::sendMessage(string message, std::string number){
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
