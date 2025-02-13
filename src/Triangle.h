#ifndef TRIANGLE
#define TRIANGLE

#include <iostream>

struct Triangle {
    int sides[3]; // a b c
    int angles[3]; // alpha beta gamma
    TrigFunctions Trig; // Provides trigonemetric functions and data checking

    Triangle(int (&sid[3]), int (&ang[3])){};
    
private:
    bool CheckValidData(){}
};

#endif // TRIANGLE