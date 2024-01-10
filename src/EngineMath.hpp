//
//  EngineMath.hpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/6/24.
//

#ifndef EngineMath_h
#define EngineMath_h


class EngineMath {
    public:
        static float dist2(float x1, float y1, float x2, float y2) {
            return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
        }
};


#endif /* EngineMath_h */
