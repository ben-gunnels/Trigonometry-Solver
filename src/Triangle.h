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
    double sides[3]; // a b c
    double angles[3]; // alpha beta gamma
    TrigFunctions Trig; // Provides trigonemetric functions and data checking

    Triangle();
    Triangle(double (&sid)[3], double (&ang)[3]);
    ValidationObj ValidateData();
    double* SolveTriangle();
private:
    int UseMethod(std::array<int, 5> cases); // Which method to look for given the triangle inputs
    void Display(double& solution);
};

#endif // TRIANGLE