//
//  Leak.hpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/26/24.
//

#ifndef Leak_hpp
#define Leak_hpp

#include <stdio.h>
#include <stdlib.h>

class MemoryLeak{
private:
    float* leak;
    
public:
    MemoryLeak(){
        leak = (float*)calloc(10000000000, sizeof(float));
    }
    ~MemoryLeak(){
        return;
    }
};

#endif /* Leak_hpp */
