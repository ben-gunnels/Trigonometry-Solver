#include <algorithm>
#include "TrigFunctions.h"
#include "Globals.cc"

TrigFunctions::TrigFunctions(int (&sid)[3], int (&ang)[3]) : sides(sid), angles(ang), TruthTable(GetTruthValues(sid, ang)){} // set up the truth values TruthTable

bool TrigFunctions::SSS()
{
    // Check that all sides have a valid value
    if (std::all_of(sides, sides + Globals::triSize, [](int x){ return x > Globals::defaultTriangleValue; })) return true;
    return false;
}

bool TrigFunctions::SAS()
{
    int cases[3] {0, 0, 0}; // Holds the truth value for whether a ssa combination is true
    
    cases[0] = TruthTable.a & TruthTable.b & TruthTable.gamma; // ab + gamma
    cases[1] = TruthTable.a & TruthTable.c & TruthTable.beta; // ac + beta
    cases[2] = TruthTable.b & TruthTable.c & TruthTable.alpha; // bc + alpha
    return std::any_of(cases, cases + Globals::triSize, [](int x){ return x > Globals::defaultTriangleValue; });
}

bool TrigFunctions::ASA()
{
    int cases[3] { 0, 0, 0 };

    cases[0] = TruthTable.alpha & TruthTable.beta & TruthTable.c; // alpha beta + c
    cases[1] = TruthTable.alpha & TruthTable.gamma & TruthTable.b; // alpha gamma + b
    cases[2] = TruthTable.beta & TruthTable.gamma & TruthTable.a; // beta gamma + a

    return std::any_of(cases, cases + Globals::triSize, [](int x){ return x > Globals::defaultTriangleValue; });
}

bool TrigFunctions::AAS()
{
    int cases[3] { 0, 0, 0 };
    
    cases[0] = (TruthTable.alpha & TruthTable.beta) & (TruthTable.a | TruthTable.b); // side a or b is viable to complete aas
    cases[1] = (TruthTable.alpha & TruthTable.gamma) & (TruthTable.a | TruthTable.c); // side a or c is viable to complete aas
    cases[2] = (TruthTable.beta & TruthTable.gamma) & (TruthTable.b | TruthTable.c); // side b or c is viable to complete aas

    return std::any_of(cases, cases + Globals::triSize, [](int x){ return x > Globals::defaultTriangleValue; }));
}

bool TrigFunctions::SSA()
{
    int cases[3] { 0, 0, 0 };
    
    cases[0] = (TruthTable.a & TruthTable.b) & (TruthTable.alpha | TruthTable.beta); // angle alpha or beta is viable to complete ssa
    cases[1] = (TruthTable.alpha & TruthTable.gamma) & (TruthTable.alpha | TruthTable.gamma); // angle alpha or gamma is viable to complete ssa
    cases[2] = (TruthTable.beta & TruthTable.gamma) & (TruthTable.beta | TruthTable.gamma); // angle beta or gamma is viable to complete ssa

    return std::any_of(cases, cases + Globals::triSize, [](int x){ return x > Globals::defaultTriangleValue; }));
}

DataTruthTable TrigFunctions::GetTruthValues(int (&sid)[3], int (&ang)[3])
{
    // Check which values are valid
    return {
            sid[0] > Globals::defaultTriangleValue, // a 
            sid[1] > Globals::defaultTriangleValue, // b
            sid[2] > Globals::defaultTriangleValue, // c
            ang[0] > Globals::defaultTriangleValue, // alpha
            ang[1] > Globals::defaultTriangleValue, // beta
            ang[2] > Globals::defaultTriangleValue // gamma
        }
}