#include <wx/wx.h>

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

    resultLabel = new wxStaticText(panel, wxID_ANY, "Result: ");
    sizer->Add(resultLabel, 0, wxALL, 10);

    panel->SetSizer(sizer);
}

void TriangleSolverFrame::OnSolve(wxCommandEvent& event) {
    double sideA, sideB, angleC;
    
    if (!inputSideA->GetValue().ToDouble(&sideA) ||
        !inputSideB->GetValue().ToDouble(&sideB) ||
        !inputAngleC->GetValue().ToDouble(&angleC)) {
        wxMessageBox("Please enter valid numeric values.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    // Example calculation: Use Law of Cosines to find third side C
    double angleC_rad = angleC * M_PI / 180.0;
    double sideC = sqrt(sideA * sideA + sideB * sideB - 2 * sideA * sideB * cos(angleC_rad));

    wxString result;
    result.Printf("Side C: %.2f", sideC);
    resultLabel->SetLabel(result);
}