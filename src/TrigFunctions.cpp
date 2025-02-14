#include <algorithm>
#include <cmath>
#include "TrigFunctions.h"
#include "Globals.h"

const double pi = 3.141592653;

double ConvertToRadians(double val);
int ConvertToDegrees(double val);

TrigFunctions::TrigFunctions(){};
TrigFunctions::TrigFunctions(int (&sid)[3], int (&ang)[3]) : 
                            sides{sid[0], sid[1], sid[2]}, 
                            angles{ang[0], ang[1], ang[2]}, 
                            TruthTable(GetTruthValues(sid, ang)){} // set up the truth values TruthTable

bool TrigFunctions::SSS()
{
    // Check that all sides have a valid value
    if (std::all_of(sides, sides + Globals::triSize, [](int x){ return x != 0; })) return true;
    return false;
}

bool TrigFunctions::SAS()
{
    int cases[3] {0, 0, 0}; // Holds the truth value for whether a ssa combination is true
    
    cases[0] = TruthTable.a & TruthTable.b & TruthTable.gamma; // ab + gamma
    cases[1] = TruthTable.a & TruthTable.c & TruthTable.beta; // ac + beta
    cases[2] = TruthTable.b & TruthTable.c & TruthTable.alpha; // bc + alpha
    return std::any_of(cases, cases + Globals::triSize, [](int x){ return x != 0; });
}

bool TrigFunctions::ASA()
{
    int cases[3] { 0, 0, 0 };

    cases[0] = TruthTable.alpha & TruthTable.beta & TruthTable.c; // alpha beta + c
    cases[1] = TruthTable.alpha & TruthTable.gamma & TruthTable.b; // alpha gamma + b
    cases[2] = TruthTable.beta & TruthTable.gamma & TruthTable.a; // beta gamma + a

    return std::any_of(cases, cases + Globals::triSize, [](int x){ return x != 0; });
}

bool TrigFunctions::AAS()
{
    int cases[3] { 0, 0, 0 };
    
    cases[0] = (TruthTable.alpha & TruthTable.beta) & (TruthTable.a | TruthTable.b); // side a or b is viable to complete aas
    cases[1] = (TruthTable.alpha & TruthTable.gamma) & (TruthTable.a | TruthTable.c); // side a or c is viable to complete aas
    cases[2] = (TruthTable.beta & TruthTable.gamma) & (TruthTable.b | TruthTable.c); // side b or c is viable to complete aas

    return std::any_of(cases, cases + Globals::triSize, [](int x){ return x != 0; });
}

bool TrigFunctions::SSA()
{
    int cases[3] { 0, 0, 0 };
    
    cases[0] = (TruthTable.a & TruthTable.b) & (TruthTable.alpha | TruthTable.beta); // angle alpha or beta is viable to complete ssa
    cases[1] = (TruthTable.alpha & TruthTable.gamma) & (TruthTable.alpha | TruthTable.gamma); // angle alpha or gamma is viable to complete ssa
    cases[2] = (TruthTable.beta & TruthTable.gamma) & (TruthTable.beta | TruthTable.gamma); // angle beta or gamma is viable to complete ssa

    return std::any_of(cases, cases + Globals::triSize, [](int x){ return x != 0; });
}

void TrigFunctions::LawOfSine(int method, int* solution)
{
    
}

void TrigFunctions::LawOfCosine(int method, int* solution)
{
    /*
        Law of Cosine: c^2 = a^2 + b^2 - 2abcos(gamma)
                        gamma = cos^-1((c^2-a^2-b^2)/2ab)
    */
    if (method == 0) // SSS
    {
        SolveSSS(solution);
    }
    else if (method == 1) // SAS 
    {
        int a2, b2, c2;
        a2 = sides[0] * sides[0];
        b2 = sides[1] * sides[1];
        c2 = sides[2] * sides[2];
        if (TruthTable.a & TruthTable.b & TruthTable.gamma) // aCb
        {
            solution[0] = sides[0];
            solution[1] = sides[1];
            solution[5] = angles[2];
            solution[2] = std::sqrt(a2 + b2 - 2.0f*solution[0]*solution[1]*std::cos(ConvertToRadians(solution[5]))); // Solve side c and angles
            c2 = solution[2] * solution[2];
            solution[3] = ConvertToDegrees(std::acos((a2-b2-c2) / -(2.0f * solution[1] * solution[2]))); // alpha
            solution[4] = (180 - solution[5] - solution[3]); // beta
        }
        else if (TruthTable.a & TruthTable.c & TruthTable.beta) // aBc
        {
            solution[0] = sides[0];
            solution[2] = sides[2];
            solution[4] = angles[1];
            solution[1] = std::sqrt(a2 + c2 - 2.0f*solution[0]*solution[2]*std::cos(ConvertToRadians(solution[4]))); // Solve side b and angles
            b2 = solution[1] * solution[1];
            solution[3] = ConvertToDegrees(std::acos((a2-b2-c2) / -(2.0f * solution[1] * solution[2]))); // alpha
            solution[5] = (180 - solution[4] - solution[3]); // gamma
        }
        else if (TruthTable.b & TruthTable.c & TruthTable.alpha) // bAc
        {
            solution[1] = sides[1];
            solution[2] = sides[2];
            solution[3] = angles[0];
            solution[0] = std::sqrt(b2 + c2 - 2.0f*solution[1]*solution[2]*std::cos(ConvertToRadians(solution[3]))); // Solve side a and angles
            a2 = solution[0] * solution[0];
            solution[4] = ConvertToDegrees(std::acos(ConvertToRadians((a2-b2-c2) / -(2.0f * solution[1] * solution[2])))); // beta
            solution[5] = (180 - solution[4] - solution[3]); // gamma
        }
    }
}

void TrigFunctions::SolveSSS(int* solution)
{
    int a2, b2, c2;
    a2 = sides[0] * sides[0];
    b2 = sides[1] * sides[1];
    c2 = sides[2] * sides[2];

    solution[0] = sides[0];
    solution[1] = sides[1];
    solution[2] = sides[2];

    solution[3] = ConvertToDegrees(std::acos((a2-b2-c2) / -(2.0f * solution[1] * solution[2]))); // alpha
    solution[4] = ConvertToDegrees(std::acos((b2-a2-c2) / -(2.0f * solution[0] * solution[2]))); // beta
    solution[5] = (180 - solution[3] - solution[4]);
} 
void TrigFunctions::SolveSAS(int* solution, int s1, int a2, int s3) 
{

}

double ConvertToRadians(double val) // pi/180
{
    return val * (pi / 180);
}

int ConvertToDegrees(double val)
{
    return val * (180 / pi);
}

DataTruthTable TrigFunctions::GetTruthValues(int (&sid)[3], int (&ang)[3])
{
    // Check which values are valid
    return {
            sid[0] != 0, // a 
            sid[1] != 0, // b
            sid[2] != 0, // c
            ang[0] != 0, // alpha
            ang[1] != 0, // beta
            ang[2] != 0 // gamma
        };
}