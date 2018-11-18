#include <iostream>
#include <unistd.h>


#include <stdio.h>
#include <stdlib.h>
#include "WiringPiWrapper.hpp"
#include "InputDevice.hpp"
#include "SevenSegmentDisplay.hpp"
#include "Led.hpp"
#include "FeedingScheduler.hpp"
#include <stdio.h>



int main(int argc, char *argv[])
{
    
    std::string dogProgramName = "dog";
    std::string washerProgramName = "washer";
    std::string instructionMessage = "Include program name to run: " + dogProgramName + ", " + washerProgramName; 
    
    if(argc < 2){ 
        puts(instructionMessage.c_str());
    } else {
        std::string program = argv[1];
        if(program == dogProgramName){
            
            puts("***Starting Dog Feeding Program***");
            FeedingScheduler scheduler = FeedingScheduler();
        
            while(true) {
                scheduler.updatePins();
            }       
        } else if (program == washerProgramName){
            puts("***Starting Washer Program***");
        } else {
            puts(instructionMessage.c_str());    
        }
    }
    
    return 0;
    
}
