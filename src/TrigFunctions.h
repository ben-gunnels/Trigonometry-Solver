#ifndef TRIGFUNCTIONS
#define TRIGFUNCTIONS

#include <algorithm>
#include <iostream>

struct DataTruthTable {
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
    int sides[3];
    int angles[3];
    DataTruthTable TruthTable;

    TrigFunctions();
    TrigFunctions(int (&sid)[3], int (&ang)[3]);

    // Validation Functions
    bool SSS(); // Law of Cosine 0 
    
    bool SAS(); // Law of Cosine 1

    bool ASA(); // Law of Sine 2

    bool AAS(); // Law of Sine 3

    bool SSA(); // Law of Sine 4

    void LawOfSine(int method, int* solution);
    void LawOfCosine(int method, int* solution);
    void SolveSSS(int* solution); // The three sides
    void SolveSAS(int* solution, int s1, int a2, int s3); // The two sides with the angle between
private:
    DataTruthTable GetTruthValues(int (&sid)[3], int (&ang)[3]);
};


#endif // TRIGFUNCTIONS