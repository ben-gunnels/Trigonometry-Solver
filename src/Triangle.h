#ifndef TRIANGLE
#define TRIANGLE

#include <array>
#include <iostream>
#include "TrigFunctions.h"

struct ValidationObj {
    bool valid;
    std::array<int, 5> cases; // Return the cases SSS SAS ASA AAS SSA 
};

struct Triangle {
    int sides[3]; // a b c
    int angles[3]; // alpha beta gamma
    TrigFunctions Trig; // Provides trigonemetric functions and data checking

    Triangle();
    Triangle(int (&sid)[3], int (&ang)[3]);
    ValidationObj ValidateData();
    int* SolveTriangle();
private:
    int UseMethod(std::array<int, 5> cases); // Which method to look for given the triangle inputs
};

#endif // TRIANGLE