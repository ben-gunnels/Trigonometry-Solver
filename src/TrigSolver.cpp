#include <iostream>
#include <cmath>
#include <exception>
#include "TrigSolver.h"
#include "Triangle.h"
#include "TrigFunctions.h"
#include "Test.h"

int main()
{
    int sides[3] {0, 0, 0};
    int angles[3] {0, 0, 0};
    int* solution;
    
    std::cout << "Welcome to Trig Solver! Please enter some sides and angles of a triangle in this format: \n"
        << "(side a) (side b) (side c) (angle alpha) (angle beta) (angle gamma)\n" << "If you don't know a side or angle, please enter 0. \n";

    std::cin >> sides[0] >> sides[1] >> sides[2] >> angles[0] >> angles[1] >> angles[2];
    Triangle triangle(sides, angles);
    ValidationObj validator;
    validator = triangle.ValidateData();

    if (validator.valid)
    {
        solution = triangle.SolveTriangle();
    }

    else 
    {
        std::cout << "Your data is invalid. You need to enter more valid sides or angles to conform to the ASA, AAS, SSA, SAS, or SSS properties.\n";
    }
}