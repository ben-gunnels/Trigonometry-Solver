#include <iostream>
#include <cmath>
#include <exception>
#include "TrigSolver.h"
#include "Triangle.h"
#include "TrigFunctions.h"
#include "Test.h"

int main()
{
    double sides[3] {0, 0, 0};
    double angles[3] {0, 0, 0};
    double* solution;
    
    // std::cout << "Welcome to Trig Solver! Please enter some sides and angles of a triangle in this format: \n"
    //     << "(side a) (side b) (side c) (angle alpha) (angle beta) (angle gamma)\n" << "If you don't know a side or angle, please enter 0. \n";

    // std::cin >> sides[0] >> sides[1] >> sides[2] >> angles[0] >> angles[1] >> angles[2];
    // {Trig.SSS(), Trig.SAS(), Trig.ASA(), Trig.AAS(), Trig.SSA()}
    struct TestTriangles 
    {
        std::string descriptor;
        double sides[3];
        double angles[3];
    } tests[] = {
        { "SSS: ", { 3, 7, 9 }, { 0, 0, 0 } }, // SSS
        { "SAS: ", { 8, 3, 0 }, { 0, 0, 60 } }, // SAS
        { "ASA: ", { 0, 5, 0 }, { 55, 0, 100 } }, // ASA
        { "AAS: ", { 6, 0, 0 }, { 20, 45, 0 } }, // AAS
        { "SSA: ", { 5, 8, 0 }, { 0, 45, 0 } }, // SSA
    };

    for (auto& t : tests) {
        Triangle triangle(t.sides, t.angles);
        ValidationObj validator = triangle.ValidateData();

        if (validator.valid) {
            std::cout << t.descriptor << "\n";
            std::cout << "Input: ";
            for (double s : t.sides) std::cout << s << " ";
            for (double a : t.angles) std::cout << a << " ";
            std::cout << "\n";
            solution = triangle.SolveTriangle();  // Solve for missing sides/angles


            // std::cout << "Solution: ";
            // if (solution) {  // Ensure the pointer is valid
            //     for (int i = 0; i < 6; ++i) {
            //         std::cout << solution[i] << " ";  // Equivalent to *(solution + i)
            //     }
            //     std::cout << "\n";
            // } else {
            //     std::cout << "Error: No solution found.\n";
            // }

            // If dynamically allocated, free memory
            delete[] solution;  
        } else {
            std::cout << "Invalid triangle data.\n";
        }
    }
    return 0;
}