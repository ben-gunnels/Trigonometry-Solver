#ifndef TRIGFUNCTIONS
#define TRIGFUNCTIONS

#include <algorithm>
#include <iostream>

struct DataTruthTable { // Stores values to express that a value is valid meaning > 0
    int a;
    int b;
    int c;
    int alpha;
    int beta;
    int gamma;
};

class TrigFunctions {
public:
    // Data
    double sides[3];
    double angles[3];
    DataTruthTable TruthTable;

    TrigFunctions();
    TrigFunctions(double (&sid)[3], double (&ang)[3]);

    // Validation Functions
    bool SSS(); // Law of Cosine 0 
    
    bool SAS(); // Law of Cosine 1

    bool ASA(); // Law of Sine 2

    bool AAS(); // Law of Sine 3

    bool SSA(); // Law of Sine 4

    void LawOfSine(int method, double* solution);
    void LawOfCosine(int method, double* solution);
    void SolveSSS(double* solution); // The three sides
    void SolveSAS(double* solution); // The two sides with the angle between
    void SolveASA(double* solution); // The two angles with a side between
    void SolveAAS(double* solution); // Two angles with an included side
    void SolveSSA(double* solution); // Two sides with an included angle

private:
    DataTruthTable GetTruthValues(double (&sid)[3], double (&ang)[3]);
    double SolveSideLOC(double a, double b, double angle);
    double SolveAngleLOC(double a, double b, double c);
    double SolveSideLOS(double a, double alpha, double beta);
    double SolveAngleLOS(double a, double b, double alpha);
    bool CheckValidSSA(double a, double b, double alpha);
};


#endif // TRIGFUNCTIONS