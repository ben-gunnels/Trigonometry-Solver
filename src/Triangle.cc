#include <iostream>

Triangle::Triangle(int (&sid[3]), int (&ang[3])) : sides(sid), angles(ang), TrigFunct(new Trig(sid, ang)) {}


Triangle::CheckValidData()
{
    int cases[5] { 0, 0, 0, 0, 0 };

    cases[0] = Trig::SSS();
    cases[1] = Trig::SAS();
    cases[2] = Trig::ASA();
    cases[3] = Trig::AAS();
    cases[4] = Trig::SSA();

    return (std::any_of(cases, 5, [](int x){ return x != 0; }));
}