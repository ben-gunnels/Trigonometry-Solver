#include <iostream>
#include <algorithm>
#include "Triangle.h"
#include "Globals.h"

Triangle::Triangle(){};

Triangle::Triangle(double (&sid)[3], double (&ang)[3]) 
                    : sides{sid[0], sid[1], sid[2]}, 
                    angles{ang[0], ang[1], ang[2]}, 
                    Trig(sid, ang) {}


ValidationObj Triangle::ValidateData()
{
    ValidationObj result;

    result.cases = {Trig.SSS(), Trig.SAS(), Trig.ASA(), Trig.AAS(), Trig.SSA()};

    result.valid = std::any_of(result.cases.begin(), result.cases.end(), 
            [](double x){ return x != 0; });

    result.valid = angles[0] < 180 && angles[1] < 180 && angles[2] < 180; // No angle greater than 180
    
    // Check triangle inequality condition
    bool sumCases[3] = {
        sides[0] < (sides[1] + sides[2]),
        sides[1] < (sides[0] + sides[2]),
        sides[2] < (sides[0] + sides[1])
    };

    // Triangle is valid only if all conditions are true
    result.valid = std::all_of(std::begin(sumCases), std::end(sumCases), [](bool x) { return x; });


    return result; 
}

double* Triangle::SolveTriangle()
{
    double* solution = new double[6]{0, 0, 0, 0, 0, 0};
    ValidationObj validator = ValidateData();

    if (!validator.valid)
    {
        return solution;
    }

    int method = UseMethod(validator.cases);
    // First two methods are law of cosine
    // Last three methods are law of sine
    if (method < 2 && method > -1)
    {
        Trig.LawOfCosine(method, solution);
    }
    else if (method > 1 && method < 6)
    {
        Trig.LawOfSine(method, solution);
    }
    std::cout << "Solution: ";
    for (int i = 0; i < sizeof(solution) / sizeof(solution[0]); ++i)
    {
        std::cout << solution[i] << " ";
    }

    std::cout << "\n";
    return solution;
}

int Triangle::UseMethod(std::array<int, 5> cases)
{
    /* 
        Gives a hint for which method to use to solve for the triangle.
    */
    for (int i = 0; i < 5; ++i)
    {
        if (cases[i] != 0)
        {
            return i; // Return the first valid conformation
        }
    }
    return -1;
}

