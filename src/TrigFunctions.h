#ifndef TRIANGLE
#define TRIANGLE

#include <iostream>

struct DataTruthTable {
    int a;
    int b;
    int c;
    int alpha;
    int beta;
    int gamma;

}

class TrigFunctions {
public:
    // Data
    int sid[3];
    int ang[3];
    DataTruthTable TruthTable;
    // Functs
    TrigFunctions(int (&sid[3]), int (&ang[3])){}
    bool SSS(int (&sid[3]), int (&ang[3])){}
    
    bool SAS(int (&sid[3]), int (&ang[3])){}

    bool ASA(int (&sid[3]), int (&ang[3])){}

    bool AAS(int (&sid[3]), int (&ang[3])){}

    bool SSA(int (&sid[3]), int (&ang[3])){}
};
private:
    DataTruthTable GetTruthValues(int (&sid[3]), int (&ang[3])){}


#endif // TRIANGLE