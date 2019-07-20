//
//  SPIWrapper.hpp
//  DogFeedScheduler
//
//  Created by Bill Gestrich on 7/20/19.
//  Copyright © 2019 Bill Gestrich. All rights reserved.
//

#ifndef SPIWrapper_hpp
#define SPIWrapper_hpp

#include <stdio.h>

class SpiWrapper {
public:
    SpiWrapper();
    static int test();
    unsigned char data[3];
};

#endif /* SPIWrapper_hpp */
