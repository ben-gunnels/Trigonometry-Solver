#include <alorithm>

TrigFunctions::TrigFunctions(int (&sid)[3], int (&ang)[3]) : sid(sid), ang(ang), TruthTruthTable(GetTruthValues(sid, ang)){} // set up the truth values TruthTable

TrigFunctions::SSS()
{
    // Check that all sides have a valid value
    if (std::all_of(sid, Globals.triSize, [](int x){ return x > Globals.defaultTriangleValue; })) return true;
    return false;
}

TrigFunctions::SAS()
{
    int cases[3] {0, 0, 0}; // Holds the truth value for whether a ssa combination is true
    
    cases[0] = TruthTable.a & TruthTable.b & TruthTable.gamma; // ab + gamma
    cases[1] = TruthTable.a & TruthTable.c & TruthTable.beta; // ac + beta
    cases[2] = TruthTable.b & TruthTable.c & TruthTable.alpha; // bc + alpha
    return (std::any_of(cases, 3, [](int x){ return x != 0; }));
}

TrigFunctions::ASA()
{
    int cases[3] { 0, 0, 0 };

    cases[0] = TruthTable.alpha & TruthTable.beta & TruthTable.c; // alpha beta + c
    cases[1] = TruthTable.alpha & TruthTable.gamma & TruthTable.b; // alpha gamma + b
    cases[2] = TruthTable.beta & TruthTable.gamma & TruthTable.a; // beta gamma + a

    return std::any_of(cases, 3, [](int x){ return x != 0; });
}

TrigFunctions::AAS()
{
    int cases[3] { 0, 0, 0 };
    
    cases[0] = (TruthTable.alpha & TruthTable.beta) & (TruthTable.a | TruthTable.b); // side a or b is viable to complete aas
    cases[1] = (TruthTable.alpha & TruthTable.gamma) & (TruthTable.a | TruthTable.c); // side a or c is viable to complete aas
    cases[2] = (TruthTable.beta & TruthTable.gamma) & (TruthTable.b | TruthTable.c); // side b or c is viable to complete aas

    return std::any_of(cases, 3, [](int x){ return x != 0; });
}

TrigFunctions::SSA()
{
    int cases[3] { 0, 0, 0 };
    
    cases[0] = (TruthTable.a & TruthTable.b) & (TruthTable.alpha | TruthTable.beta); // angle alpha or beta is viable to complete ssa
    cases[1] = (TruthTable.alpha & TruthTable.gamma) & (TruthTable.alpha | TruthTable.gamma); // angle alpha or gamma is viable to complete ssa
    cases[2] = (TruthTable.beta & TruthTable.gamma) & (TruthTable.beta | TruthTable.gamma); // angle beta or gamma is viable to complete ssa

    return std::any_of(cases, 3, [](int x){ return x != 0; });
}

TrigFunctions::GetTruthValues(int (&sid[3]), int (&ang[3]))
{
    // Check which values are valid
    return {
            sid[0] > globals.defaultTriangleValue, // a 
            sid[1] > globals.defaultTriangleValue, // b
            sid[2] > globals.defaultTriangleValue, // c
            ang[0] > globals.defaultTriangleValue, // alpha
            ang[1] > globals.defaultTriangleValue, // beta
            ang[2] > globals.defaultTriangleValue // gamma
        }
}