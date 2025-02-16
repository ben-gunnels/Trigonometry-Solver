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

    wxTextCtrl* inputSideA;
    wxTextCtrl* inputSideB;
    wxTextCtrl* inputAngleC;
    wxStaticText* resultLabel;
};

wxIMPLEMENT_APP(TriangleSolverApp);

bool TriangleSolverApp::OnInit() {
    TriangleSolverFrame* frame = new TriangleSolverFrame();
    frame->Show(true);
    return true;
}

TriangleSolverFrame::TriangleSolverFrame()
    : wxFrame(nullptr, wxID_ANY, "Triangle Solver", wxDefaultPosition, wxSize(400, 300)) {

    wxPanel* panel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(new wxStaticText(panel, wxID_ANY, "Side A:"), 0, wxALL, 5);
    inputSideA = new wxTextCtrl(panel, wxID_ANY);
    sizer->Add(inputSideA, 0, wxEXPAND | wxALL, 5);

    sizer->Add(new wxStaticText(panel, wxID_ANY, "Side B:"), 0, wxALL, 5);
    inputSideB = new wxTextCtrl(panel, wxID_ANY);
    sizer->Add(inputSideB, 0, wxEXPAND | wxALL, 5);

    sizer->Add(new wxStaticText(panel, wxID_ANY, "Angle C (degrees):"), 0, wxALL, 5);
    inputAngleC = new wxTextCtrl(panel, wxID_ANY);
    sizer->Add(inputAngleC, 0, wxEXPAND | wxALL, 5);

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