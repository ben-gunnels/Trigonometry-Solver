#include <iostream>
#include <cmath>
#include <exception>

int main()
{
    Triangle triangle;
    ValidationObj validator;
    
    std::cout << "Welcome to Trig Solver! Please enter some sides and angles of a triangle in this format: \n"
        << "(side a) (side b) (side c) (angle alpha) (angle beta) (angle gamma)\n" << "If you don't know a side or angle, please enter 0. \n";

    std::cin >> triangle.sides[0] >> triangle.sides[1] >> triangle.sides[2] >> triangle.angles[0] >> triangle.angles[1] >> triangle.angles[2];

    validator = triangle.ValidateData();

    if (validator.valid)
    {
        std::cout << "Your data is valid and the triangle can be solved. \n";
    }

    else 
    {
        std::cout << "Your data is invalid. You need to enter more valid sides or angles to conform to the ASA, AAS, SSA, SAS, or SSS properties.\n";
    }
}