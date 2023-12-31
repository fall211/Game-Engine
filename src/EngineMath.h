#ifndef ENGINEMATH_H
#define ENGINEMATH_H


class EngineMath {
    public:
        static float dist2(float x1, float y1, float x2, float y2) {
            return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
        }

        static float sgn(float x) {
            if (x > 0) return 1;
            else if (x == 0) return 0;
            else return -1;
        }
};



#endif
