#include <algorithm>
#include <cmath>
#include <iostream>
#include "TrigFunctions.h"
#include "Globals.h"

const double pi = 3.141592653;

double ConvertToRadians(double val);
int ConvertToDegrees(double val);

TrigFunctions::TrigFunctions(){};
TrigFunctions::TrigFunctions(double (&sid)[3], double (&ang)[3]) : 
                            sides{sid[0], sid[1], sid[2]}, 
                            angles{ang[0], ang[1], ang[2]}, 
                            TruthTable(GetTruthValues(sid, ang)){} // set up the truth values TruthTable

bool TrigFunctions::SSS()
{
    bool valid = false;
    // Check that all sides have a valid value
    valid = std::all_of(sides, sides + Globals::triSize, [](double x){ return x != 0; });
    
    // Check triangle inequality condition
    bool sumCases[3] = {
        sides[0] < (sides[1] + sides[2]),
        sides[1] < (sides[0] + sides[2]),
        sides[2] < (sides[0] + sides[1])
    };

    // Triangle is valid only if all conditions are true
    valid &= std::all_of(std::begin(sumCases), std::end(sumCases), [](bool x) { return x; });
    return valid;
}

bool TrigFunctions::SAS()
{
    int cases[3] {0, 0, 0}; // Holds the truth value for whether a ssa combination is true
    
    cases[0] = TruthTable.a > 0 & TruthTable.b > 0 & TruthTable.gamma > 0; // ab + gamma
    cases[1] = TruthTable.a > 0 & TruthTable.c  > 0 & TruthTable.beta > 0; // ac + beta
    cases[2] = TruthTable.b > 0 & TruthTable.c > 0 & TruthTable.alpha > 0; // bc + alpha
    return std::any_of(cases, cases + Globals::triSize, [](int x){ return x != 0; });
}

bool TrigFunctions::ASA()
{
    int cases[3] { 0, 0, 0 };

    cases[0] = TruthTable.alpha > 0 & TruthTable.beta > 0 & TruthTable.c > 0; // alpha beta + c
    cases[1] = TruthTable.alpha > 0 & TruthTable.gamma > 0 & TruthTable.b > 0; // alpha gamma + b
    cases[2] = TruthTable.beta > 0 & TruthTable.gamma > 0 & TruthTable.a > 0; // beta gamma + a
    return std::any_of(cases, cases + Globals::triSize, [](int x){ return x != 0; });
}

bool TrigFunctions::AAS()
{
    int cases[3] { 0, 0, 0 };
    
    cases[0] = (TruthTable.alpha > 0 & TruthTable.beta > 0) & (TruthTable.a > 0 | TruthTable.b > 0); // side a or b is viable to complete aas
    cases[1] = (TruthTable.alpha > 0 & TruthTable.gamma > 0) & (TruthTable.a > 0 | TruthTable.c > 0); // side a or c is viable to complete aas
    cases[2] = (TruthTable.beta > 0 & TruthTable.gamma > 0) & (TruthTable.b > 0 | TruthTable.c > 0); // side b or c is viable to complete aas

    return std::any_of(cases, cases + Globals::triSize, [](int x){ return x != 0; });
}

bool TrigFunctions::SSA()
{
    int cases[7] { 0, 0, 0, 0, 0, 0, 0 };
    
    cases[0] = (TruthTable.a > 0 & TruthTable.b > 0) & (TruthTable.alpha > 0); // angle alpha or beta is viable to complete ssa
    cases[1] = (TruthTable.a > 0 & TruthTable.b > 0) & (TruthTable.beta > 0); // angle alpha or beta is viable to complete ssa
    cases[2] = (TruthTable.a > 0 & TruthTable.c > 0) & (TruthTable.alpha > 0); // angle alpha or gamma is viable to complete ssa
    cases[3] = (TruthTable.a > 0 & TruthTable.c > 0) & (TruthTable.gamma > 0); // angle alpha or gamma is viable to complete ssa
    cases[4] = (TruthTable.b > 0 & TruthTable.c > 0) & (TruthTable.beta > 0); // angle beta or gamma is viable to complete ssa
    cases[5] = (TruthTable.b > 0 & TruthTable.c > 0) & (TruthTable.gamma > 0); // angle beta or gamma is viable to complete ssa
    
    struct SSACases
    {
        bool condition;
        int configuration[3];
    } ssacases[] = {
        { cases[0], { 0, 1, 0 } }, // Side a, side b, angle a
        { cases[1], { 1, 0, 1 } },
        { cases[2], { 0, 2, 0 } },
        { cases[3], { 2, 0, 2 } },
        { cases[4], { 1, 2, 1 } },
        { cases[5], { 2, 1, 2 } },
    };
    
    // Check that the height is valid
    for (const auto& c : ssacases)
    {
        if (c.condition)
        {
            if (CheckValidSSA(sides[c.configuration[0]], sides[c.configuration[1]], angles[c.configuration[2]]))
            {
                cases[6] = 1;
            }
        }
    }

    if (!cases[6]) return false; // No valid SSA height was found

    return std::any_of(cases, cases + Globals::triSize, [](int x){ return x != 0; });
}

void TrigFunctions::LawOfCosine(int method, double* solution) {
    /*
       Law of Cosine: c^2 = a^2 + b^2 - 2abcos(gamma)
                      gamma = cos^-1((c^2-a^2-b^2)/2ab)
    */
    if (method == 0) 
    { // SSS
        SolveSSS(solution);
        return;
    }
    else if (method == 1)
    {
        SolveSAS(solution);
        return;
    }
}

void TrigFunctions::LawOfSine(int method, double* solution)
{
    if (method == 2)
    {
        SolveASA(solution);
        return;
    }
    else if (method == 3)
    {
        SolveAAS(solution);
        return;
    }
    else if (method == 4)
    {
        SolveSSA(solution);
        return;
    }
    
}

void TrigFunctions::SolveSSS(double* solution)
{
    solution[0] = sides[0];
    solution[1] = sides[1];
    solution[2] = sides[2];

    solution[3] = SolveAngleLOC(solution[0], solution[1], solution[2]); // alpha
    solution[4] = SolveAngleLOC(solution[1], solution[0], solution[2]); // beta
    solution[5] = (180 - solution[3] - solution[4]);
} 

void TrigFunctions::SolveSAS(double* solution) 
{
    // Solve SAS
    struct TriangleCase 
    {
        bool condition; // Which sides/angle are known
        int knownSides[2]; // index of known sides in solutions array
        int knownAngle; // index of known angle in solutions array
        int unknownSide; // index of side we are looking to solve for in solutions array
        int unknownAngles[2]; // index of angles we are looking to solve for in solutions array
    } cases[] = {
        {TruthTable.a && TruthTable.b && TruthTable.gamma, {0, 1}, 5, 2, {3, 4}},
        {TruthTable.a && TruthTable.c && TruthTable.beta, {0, 2}, 4, 1, {3, 5}},
        {TruthTable.b && TruthTable.c && TruthTable.alpha, {1, 2}, 3, 0, {4, 5}}
    };
    
    for (const auto& c : cases) 
    {
        if (c.condition) 
            {
            solution[c.knownSides[0]] = sides[c.knownSides[0]];
            solution[c.knownSides[1]] = sides[c.knownSides[1]];
            solution[c.knownAngle] = angles[c.knownAngle - 3];
            
            solution[c.unknownSide] = SolveSideLOC(
                solution[c.knownSides[0]], 
                solution[c.knownSides[1]], 
                solution[c.knownAngle]
            );
            
            solution[c.unknownAngles[0]] = SolveAngleLOC(solution[c.knownSides[0]], solution[c.knownSides[1]], solution[c.unknownSide]);
            solution[c.unknownAngles[1]] = 180.0 - solution[c.unknownAngles[0]] - solution[c.knownAngle];
            return;
        }
    }
}

void TrigFunctions::SolveASA(double* solution)
{
    struct TriangleCase 
    {
        bool condition;
        int knownSide;
        int knownAngles[2];
        int unknownSides[2];
        int unknownAngle;
    } cases[] = {
        { TruthTable.alpha & TruthTable.beta & TruthTable.c , 2, { 3, 4 }, { 0, 1 }, 5 }, // Ordering of known angles should correspond to unknown
        { TruthTable.alpha & TruthTable.gamma & TruthTable.b, 1, { 3, 5 }, { 0, 2 }, 4 }, // sides
        { TruthTable.beta & TruthTable.gamma & TruthTable.a, 0, { 4, 5 }, { 1, 2 }, 3 },
    };

    for (const auto& c : cases)
    {
        if (c.condition)
        {
            solution[c.knownSide] = sides[c.knownSide];
            solution[c.knownAngles[0]] = angles[c.knownAngles[0]-3]; // Angle values need to be decreased 3
            solution[c.knownAngles[1]] = angles[c.knownAngles[1]-3];
            solution[c.unknownAngle] = 180 - solution[c.knownAngles[0]] - solution[c.knownAngles[1]];
            solution[c.unknownSides[0]] = SolveSideLOS(solution[c.knownSide], solution[c.unknownAngle], solution[c.knownAngles[0]]);
            solution[c.unknownSides[1]] = SolveSideLOS(solution[c.knownSide], solution[c.unknownAngle], solution[c.knownAngles[1]]);
        }
    }
}

void TrigFunctions::SolveAAS(double* solution)
{
    struct TriangleCase 
    {
        bool condition;
        int knownSide;
        int knownAngles[2];
        int unknownSides[2];
        int unknownAngle;
    } cases[] = {
        { TruthTable.alpha & TruthTable.beta & TruthTable.a , 0, { 3, 4 }, { 1, 2 }, 5 }, // Have the known angle of the known side come first
        { TruthTable.alpha & TruthTable.beta & TruthTable.b, 1, { 4, 3 }, { 0, 2 }, 5 }, // Have unknownSide of the unknownAngle come last
        { TruthTable.alpha & TruthTable.gamma & TruthTable.a, 0, { 3, 5 }, { 2, 1 }, 4 },
        { TruthTable.alpha & TruthTable.gamma & TruthTable.c, 2, { 5, 3 }, { 0, 1 }, 4 },
        { TruthTable.beta & TruthTable.gamma & TruthTable.b, 1, { 4, 5 }, { 2, 0 }, 3 },
        { TruthTable.beta & TruthTable.gamma & TruthTable.c, 2, { 5, 4 }, { 1, 0 }, 3 },
    };

    for (const auto& c : cases)
    {
        if (c.condition)
        {
            solution[c.knownAngles[0]] = angles[c.knownAngles[0]-3];
            solution[c.knownAngles[1]] = angles[c.knownAngles[1]-3];
            solution[c.knownSide] = sides[c.knownSide];
            solution[c.unknownAngle] = 180 - solution[c.knownAngles[0]] - solution[c.knownAngles[1]];
            solution[c.unknownSides[0]] = SolveSideLOS(solution[c.knownSide], solution[c.knownAngles[0]], solution[c.knownAngles[1]]);
            solution[c.unknownSides[1]] = SolveSideLOS(solution[c.knownSide], solution[c.knownAngles[0]], solution[c.unknownAngle]);
        }
    }
}

void TrigFunctions::SolveSSA(double* solution)
{
    struct TriangleCase 
    {
        bool condition;
        int knownSides[2];
        int knownAngle;
        int unknownSide;
        int unknownAngles[2];
    } cases[] = {
            {(TruthTable.a > 0 & TruthTable.b > 0) & (TruthTable.alpha > 0), {0, 1}, 3, 2, {4, 5}},
            {(TruthTable.a > 0 & TruthTable.b > 0) & (TruthTable.beta > 0), {1, 0}, 4, 2, {3, 5}},
            {(TruthTable.a > 0 & TruthTable.c > 0) & (TruthTable.alpha > 0), {0, 2}, 3, 1, {5, 4}},
            {(TruthTable.a > 0 & TruthTable.c > 0) & (TruthTable.gamma > 0), {2, 0}, 5, 1, {3, 4}},
            {(TruthTable.b > 0 & TruthTable.c > 0) & (TruthTable.beta > 0), {1, 2}, 4, 0, {5, 3}},
            {(TruthTable.b > 0 & TruthTable.c > 0) & (TruthTable.gamma > 0), {2, 1}, 5, 0, {4, 3}}, 
    };

    for (const auto& c : cases)
    {
        if (c.condition)
        {   
            solution[c.knownSides[0]] = sides[c.knownSides[0]];
            solution[c.knownSides[1]] = sides[c.knownSides[1]];
            solution[c.knownAngle] = angles[c.knownAngle-3];
            solution[c.unknownAngles[0]] = SolveAngleLOS(solution[c.knownSides[0]], solution[c.knownSides[1]], solution[c.knownAngle]);
            solution[c.unknownAngles[1]] = 180 - solution[c.knownAngle] - solution[c.unknownAngles[0]];
            solution[c.unknownSide] = SolveSideLOS(solution[c.knownSides[0]], solution[c.knownAngle], solution[c.unknownAngles[1]]);
        }
    }
}

double TrigFunctions::SolveSideLOC(double a, double b, double angle) {
    double a2, b2;
    a2 = a * a;
    b2 = b * b;
    return std::sqrt(a2 + b2 - 2.0 * a * b * std::cos(ConvertToRadians(angle))); // Side you are solving for is c
}

double TrigFunctions::SolveAngleLOC(double a, double b, double c) {
    double a2, b2, c2;
    a2 = a * a;
    b2 = b * b;
    c2 = c * c;
    std::cout << ConvertToDegrees(std::acos((a2 - b2 - c2) / (-2.0 * b * c))) << "\n";
    return ConvertToDegrees(std::acos((a2 - b2 - c2) / (-2.0 * b * c))); // Angle you are solving for is "alpha"
}

double TrigFunctions::SolveSideLOS(double a, double alpha, double beta) // replace a with the side you know
{
    return (a * std::sin(ConvertToRadians(beta))) / std::sin(ConvertToRadians(alpha));
}

double TrigFunctions::SolveAngleLOS(double a, double b, double alpha) // replace alpha with the angle you know
{
    return ConvertToDegrees(std::asin((b * std::sin(ConvertToRadians(alpha))) / a));
}

bool TrigFunctions::CheckValidSSA(double a, double b, double alpha)
{
    if (a < b * std::cos(alpha)) // a's height must be tall enough to form a valid triangle 
    {
        return false;
    }
    return true;
}

double ConvertToRadians(double val) // pi/180
{
    return val * (pi / 180);
}

int ConvertToDegrees(double val)
{
    return val * (180 / pi);
}

DataTruthTable TrigFunctions::GetTruthValues(double (&sid)[3], double (&ang)[3])
{
    // Check which values are valid
    return {
            sid[0] > 0, // a 
            sid[1] > 0, // b
            sid[2] > 0, // c
            ang[0] > 0, // alpha
            ang[1] > 0, // beta
            ang[2] > 0 // gamma
        };
}
