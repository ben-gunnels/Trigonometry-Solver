#include <iostream>
#include <cmath>
#include <exception>
#include <sstream>
#include "TrigSolver.h"
#include "Triangle.h"
#include "TrigFunctions.h"

#include <wx/wx.h>


void SetInputValue(wxTextCtrl* input, double value);

class TriangleSolverApp : public wxApp {
public:
    virtual bool OnInit();
};

class TriangleSolverFrame : public wxFrame {
public:
    TriangleSolverFrame();

private:
    void OnSolve(wxCommandEvent& event);

    wxTextCtrl* inputSide_a;
    wxTextCtrl* inputSide_b;
    wxTextCtrl* inputSide_c;
    wxTextCtrl* inputAngle_A;
    wxTextCtrl* inputAngle_B;
    wxTextCtrl* inputAngle_C;
    wxStaticText* resultLabel;
};

wxIMPLEMENT_APP(TriangleSolverApp);

bool TriangleSolverApp::OnInit() {
    TriangleSolverFrame* frame = new TriangleSolverFrame();
    frame->Show(true);
    return true;
}

TriangleSolverFrame::TriangleSolverFrame()
    : wxFrame(nullptr, wxID_ANY, "Triangle Solver", wxDefaultPosition, wxSize(500, 500)) {

    wxPanel* panel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(new wxStaticText(panel, wxID_ANY, "Side A:"), 0, wxALL, 5);
    inputSide_a = new wxTextCtrl(panel, wxID_ANY);
    sizer->Add(inputSide_a, 0, wxEXPAND | wxALL, 5);

    sizer->Add(new wxStaticText(panel, wxID_ANY, "Side B:"), 0, wxALL, 5);
    inputSide_b = new wxTextCtrl(panel, wxID_ANY);
    sizer->Add(inputSide_b, 0, wxEXPAND | wxALL, 5);

    sizer->Add(new wxStaticText(panel, wxID_ANY, "Side C:"), 0, wxALL, 5);
    inputSide_c = new wxTextCtrl(panel, wxID_ANY);
    sizer->Add(inputSide_c, 0, wxEXPAND | wxALL, 5);

    sizer->Add(new wxStaticText(panel, wxID_ANY, "Angle A (degrees):"), 0, wxALL, 5);
    inputAngle_A = new wxTextCtrl(panel, wxID_ANY);
    sizer->Add(inputAngle_A, 0, wxEXPAND | wxALL, 5);

    sizer->Add(new wxStaticText(panel, wxID_ANY, "Angle B (degrees):"), 0, wxALL, 5);
    inputAngle_B = new wxTextCtrl(panel, wxID_ANY);
    sizer->Add(inputAngle_B, 0, wxEXPAND | wxALL, 5);

    sizer->Add(new wxStaticText(panel, wxID_ANY, "Angle C (degrees):"), 0, wxALL, 5);
    inputAngle_C = new wxTextCtrl(panel, wxID_ANY);
    sizer->Add(inputAngle_C, 0, wxEXPAND | wxALL, 5);

    wxButton* solveButton = new wxButton(panel, wxID_ANY, "Solve");
    sizer->Add(solveButton, 0, wxALIGN_CENTER | wxALL, 10);
    solveButton->Bind(wxEVT_BUTTON, &TriangleSolverFrame::OnSolve, this);

    // resultLabel = new wxStaticText(panel, wxID_ANY, "Result: ");
    // sizer->Add(resultLabel, 0, wxALL, 10);

    panel->SetSizer(sizer);
}

void TriangleSolverFrame::OnSolve(wxCommandEvent& event) {
    double sides[3] {0, 0, 0};
    double angles[3] {0, 0, 0};
    double side_a, side_b, side_c, angle_A, angle_B, angle_C;
    double* solution;
    
    if (!inputSide_a->GetValue().ToDouble(&side_a) ||
        !inputSide_b->GetValue().ToDouble(&side_b) ||
        !inputSide_c->GetValue().ToDouble(&side_c) ||
        !inputAngle_A->GetValue().ToDouble(&angle_A) ||
        !inputAngle_B->GetValue().ToDouble(&angle_B) ||
        !inputAngle_C->GetValue().ToDouble(&angle_C)) {
        wxMessageBox("Please enter valid numeric values.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    // wxMessageBox(wxString::Format("Side a: %.2f\nSide b: %.2f\nSide c: %.2f\nAngle A: %.2f\nAngle B: %.2f\nAngle C: %.2f",
    //     side_a, side_b, side_c, angle_A, angle_B, angle_C), 
    //     "Debug: Parsed Inputs", wxOK | wxICON_INFORMATION);
        
    double zero = 0;
    sides[0] = std::max(side_a, zero);
    sides[1] = std::max(side_b, zero);
    sides[2] = std::max(side_c, zero);
    angles[0] = std::max(angle_A, zero);
    angles[1] = std::max(angle_B, zero);
    angles[2] = std::max(angle_C, zero);

    // wxLogMessage("Processed Sides: %.2f, %.2f, %.2f", sides[0], sides[1], sides[2]);
    // wxLogMessage("Processed Angles: %.2f, %.2f, %.2f", angles[0], angles[1], angles[2]);

    Triangle triangle(sides, angles);
    ValidationObj validator = triangle.ValidateData();
    if (!validator.valid)
    {
        wxMessageBox("The data you entered for the triangle is not solvable. Try again.", "Error", wxOK | wxICON_ERROR);
    }

    solution = triangle.SolveTriangle();  // Solve for missing sides/angles

    // wxString result;
    // result.Printf("Side a: %.2f, Side b: %.2f, Side c: %.2f, Angle A: %.2f, Angle B: %.2f, Angle C: %.2f", 
    //                             solution[0], solution[1], solution[2], 
    //                             solution[3], solution[4], solution[5]);
    // resultLabel->SetLabel(result);
    SetInputValue(inputSide_a, solution[0]);
    SetInputValue(inputSide_b, solution[1]);
    SetInputValue(inputSide_c, solution[2]);
    SetInputValue(inputAngle_A, solution[3]);
    SetInputValue(inputAngle_B, solution[4]);
    SetInputValue(inputAngle_C, solution[5]);
   
}

void SetInputValue(wxTextCtrl* input, double value) {
    std::ostringstream stream;
    stream.precision(3);  // Set precision (adjust as needed)
    stream << std::fixed << value; 

    input->SetValue(stream.str());  // Convert to string and set value
}

// int main()
// {
//     double sides[3] {0, 0, 0};
//     double angles[3] {0, 0, 0};
//     double* solution;
    
//     // std::cout << "Welcome to Trig Solver! Please enter some sides and angles of a triangle in this format: \n"
//     //     << "(side a) (side b) (side c) (angle alpha) (angle beta) (angle gamma)\n" << "If you don't know a side or angle, please enter 0. \n";

//     // std::cin >> sides[0] >> sides[1] >> sides[2] >> angles[0] >> angles[1] >> angles[2];
//     // {Trig.SSS(), Trig.SAS(), Trig.ASA(), Trig.AAS(), Trig.SSA()}
//     struct TestTriangles 
//     {
//         std::string descriptor;
//         double sides[3];
//         double angles[3];
//     } tests[] = {
//         { "SSS: ", { 3, 7, 9 }, { 0, 0, 0 } }, // SSS
//         { "SAS: ", { 8, 3, 0 }, { 0, 0, 60 } }, // SAS
//         { "ASA: ", { 0, 5, 0 }, { 55, 0, 100 } }, // ASA
//         { "AAS: ", { 6, 0, 0 }, { 20, 45, 0 } }, // AAS
//         { "SSA: ", { 5, 8, 0 }, { 0, 45, 0 } }, // SSA
//     };

//     for (auto& t : tests) {
//         Triangle triangle(t.sides, t.angles);
//         ValidationObj validator = triangle.ValidateData();

//         if (validator.valid) {
//             std::cout << t.descriptor << "\n";
//             std::cout << "Input: ";
//             for (double s : t.sides) std::cout << s << " ";
//             for (double a : t.angles) std::cout << a << " ";
//             std::cout << "\n";
//             solution = triangle.SolveTriangle();  // Solve for missing sides/angles


//             // std::cout << "Solution: ";
//             // if (solution) {  // Ensure the pointer is valid
//             //     for (int i = 0; i < 6; ++i) {
//             //         std::cout << solution[i] << " ";  // Equivalent to *(solution + i)
//             //     }
//             //     std::cout << "\n";
//             // } else {
//             //     std::cout << "Error: No solution found.\n";
//             // }

//             // If dynamically allocated, free memory
//             delete[] solution;  
//         } else {
//             std::cout << "Invalid triangle data.\n";
//         }
//     }
//     return 0;
// }
