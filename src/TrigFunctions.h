#ifndef TRIGFUNCTIONS
#define TRIGFUNCTIONS

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
    int* sides;
    int* angles;
    DataTruthTable TruthTable;

    TrigFunctions(){}
    TrigFunctions(int (&sid)[3], int (&ang)[3]){}

    // Validation Functions
    bool SSS(){}
    
    bool SAS(){}

    bool ASA(){}

    bool AAS(){}

    bool SSA(){}
private:
    DataTruthTable GetTruthValues(int (&sid)[3], int (&ang)[3]){}
};


#endif // TRIGFUNCTIONS