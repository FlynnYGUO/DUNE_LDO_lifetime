#include <TCanvas.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TLegend.h>
#include <TMath.h>

#include "TRandom.h"
#include "TGraphErrors.h"
#include "TF1.h"

using namespace std;

void plot_degradation_LP_stress() {

    TString FileIn1 = "/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/Apr19/LP13_7.00to9.50_ADM13_7.00to19.50.root";
    TString FileIn2 = "/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/Apr19/LP16_7.00to10.00_ADM16_7.00to21.00.root";
    TString FileIn3 = "/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/Apr19/LP20_7.00to10.50_ADM20_7.00to18.00.root";


    // Create a new TChain instance to chain .root files together
    TChain *chain_s = new TChain("tree_s"); // Replace "tree_name" with the name of your TTree
    TChain *chain_n = new TChain("tree_n"); // Replace "tree_name" with the name of your TTree

    // Add .root files to the chain
    chain_s->Add(FileIn1.Data()); // Replace with the actual file paths and names
    chain_s->Add(FileIn2.Data()); // Replace with the actual file paths and names
    chain_s->Add(FileIn3.Data()); // Replace with the actual file paths and names

    chain_n->Add(FileIn1.Data()); // Replace with the actual file paths and names
    chain_n->Add(FileIn2.Data()); // Replace with the actual file paths and names
    chain_n->Add(FileIn3.Data()); // Replace with the actual file paths and names
    // Add as many files as you have

    // Variables to hold the data from the branches
    double ADM_ave_s, LP_ave_s, t_measure_s;
    double ADM_ave_n, LP_ave_n, t_measure_n;
    double D_LP_ini,D_LP_max,D_ADM_ini,D_ADM_max;
    double LP_ave_s_ini, LP_ave_s_min, LP_ave_s_max;
    double ADM_ave_s_ini, ADM_ave_s_min, ADM_ave_s_max;
    double LP_ave_n_ini, LP_ave_n_min, LP_ave_n_max;
    double ADM_ave_n_ini, ADM_ave_n_min, ADM_ave_n_max;
    int batchNumber_s, batchNumber_n;
    // Set branch addresses
    chain_s->SetBranchAddress("ADM_ave_s", &ADM_ave_s);
    chain_s->SetBranchAddress("LP_ave_s", &LP_ave_s);
    chain_s->SetBranchAddress("t_measure_s", &t_measure_s);
    chain_s->SetBranchAddress("LP_ave_s_ini", &LP_ave_s_ini);
    chain_s->SetBranchAddress("LP_ave_s_max", &LP_ave_s_max);
    chain_s->SetBranchAddress("ADM_ave_s_ini", &ADM_ave_s_ini);
    chain_s->SetBranchAddress("ADM_ave_s_max", &ADM_ave_s_max);
    chain_s->SetBranchAddress("batchNumber", &batchNumber_s);

    chain_n->SetBranchAddress("ADM_ave_n", &ADM_ave_n);
    chain_n->SetBranchAddress("LP_ave_n", &LP_ave_n);
    chain_n->SetBranchAddress("t_measure_n", &t_measure_n);
    chain_n->SetBranchAddress("LP_ave_n_ini", &LP_ave_n_ini);
    chain_n->SetBranchAddress("LP_ave_n_max", &LP_ave_n_max);
    chain_n->SetBranchAddress("ADM_ave_n_ini", &ADM_ave_n_ini);
    chain_n->SetBranchAddress("ADM_ave_n_max", &ADM_ave_n_max);
    chain_n->SetBranchAddress("batchNumber", &batchNumber_n);
    // Create graphs
    // TMultiGraph *mg = new TMultiGraph("mg",mg);
    TGraph *gr1 = new TGraph();
    gr1->SetMarkerColor(kBlue);
    gr1->SetMarkerStyle(20);
    gr1->SetLineColor(kBlue);

    TGraph *gr2 = new TGraph();
    gr2->SetMarkerColor(kRed);
    gr2->SetMarkerStyle(20);
    gr2->SetLineColor(kRed);

    TGraph *gr3 = new TGraph();
    gr3->SetMarkerColor(kGreen+2);
    gr3->SetMarkerStyle(20);
    gr3->SetLineColor(kGreen+2);
    // You might need to create as many TGraphs as your datasets

    int n1 = 0, n2 = 0, n3 = 0; // Indices for each graph
    double peaktime1 = 0.270833;
    double peaktime2 = 0.1875;
    double peaktime3 = 0.1875;

    bool firstFound = false; // Flag to check if the first occurrence is found

    // Loop over the chain and fill the graphs
    for (int i = 0; i < chain_s->GetEntries(); i++) {
        chain_s->GetEntry(i);
        D_LP_max = (LP_ave_s_max - LP_ave_s)*100/LP_ave_s_max;
        t_measure_s = t_measure_s/(60*24); // change units to day
        // cout << i << ", batchNumber: " << batchNumber_s << ", " << D_LP_max << ", " << t_measure_s<< ", "<< LP_ave_s << endl;
        if( D_LP_max == 0) cout<< i << "max time: "<< t_measure_s << endl;

        // if (batchNumber_s==13 && t_measure_s>peaktime1) {
        //     gr1->SetPoint(n1++, t_measure_s-peaktime1, D_LP_max);
        // } else if (batchNumber_s==16 && t_measure_s>peaktime2) {
        //     gr2->SetPoint(n2++, t_measure_s-peaktime2, D_LP_max);
        // } else if (batchNumber_s==20 && t_measure_s>=peaktime3 ) {
        //     gr3->SetPoint(n3++, t_measure_s-peaktime3, D_LP_max);
        // }
        if (batchNumber_s==13 ) {
            gr1->SetPoint(n1++, t_measure_s, D_LP_max);
        } else if (batchNumber_s==16 ) {
            gr2->SetPoint(n2++, t_measure_s, D_LP_max);
        } else if (batchNumber_s==20  ) {
            gr3->SetPoint(n3++, t_measure_s, D_LP_max);
        }
    }

    cout << "n1: " << n1 << endl;
    cout << "n2: " << n2 << endl;
    cout << "n3: " << n3 << endl;

    // // nominal
    // for (int i = 0; i < chain_s->GetEntries(); i++) {
    //     chain_s->GetEntry(i);
    //     // cout << i << ", " << D_LP_max << ", " << t_measure_s<< ", "<< LP_ave_s << endl;
    //     // if( LP_ave_s > LP_ave_s_max) continue;
    //     // cout << i << ", " << D_LP_max << ", " << t_measure_s<< ", "<< LP_ave_s << endl;
    //
    //     D_LP_max = (LP_ave_n_max - LP_ave_n)*100/LP_ave_n_max;
    //     // D_LP_ini = (LP_ave_s - LP_ave_s_ini)*100/LP_ave_s_ini;
    //
    //     t_measure_n = t_measure_n/(60*24); // change units to day
    //     if( D_LP_max == 0) cout<< i << "max time: "<< t_measure_n << endl;
    //     // gr1->SetPoint(n1++, t_measure_s, D_LP_max);
    //     // // Depending on your condition, assign points to different graphs
    //     // // This is a placeholder; you'll need to replace it with your actual logic
    //     // if (batchNumber==19 && t_measure_n>=0.125) {
    //     //     gr1->SetPoint(n1++, t_measure_n, D_LP_max);
    //     // } else if (batchNumber==20&& t_measure_n>0.1875) {
    //     //     gr2->SetPoint(n2++, t_measure_n, D_LP_max);
    //     // } else if (batchNumber== 18&& t_measure_n>0.4375) {
    //     //     gr3->SetPoint(n3++, t_measure_n, D_LP_max);
    //     // }
    //     if (batchNumber==19 ) {
    //         gr1->SetPoint(n1++, t_measure_n, D_LP_max);
    //     } else if (batchNumber==20) {
    //         gr2->SetPoint(n2++, t_measure_n, D_LP_max);
    //     } else if (batchNumber== 18) {
    //         gr3->SetPoint(n3++, t_measure_n, D_LP_max);
    //     }
    // }


    // Define fit functions, assuming you want to fit with a polynomial for example
    TF1 *fitFunc1 = new TF1("fitFunc1", "[0]*log(x+[1]) + [2]", peaktime1, 1e12); // Linear fit for graph1
    TF1 *fitFunc2 = new TF1("fitFunc2", "[0]*log(x+[1]) + [2]", peaktime2, 1e12); // Linear fit for graph2
    TF1 *fitFunc3 = new TF1("fitFunc3", "[0]*log(x+[1]) + [2]", peaktime3, 1e12); // Linear fit for graph2
   // Fit the graphs, "Q" is for Quiet, "R" is for using the function range
    gr1->Fit(fitFunc1, "LR+");
    gr2->Fit(fitFunc2, "LR+");
    gr3->Fit(fitFunc3, "LR+");
    // Create a canvas to draw the plots
    TCanvas *canvas = new TCanvas("canvas", "Voltage Degradation", 2400, 1600);
    // canvas->SetLeftMargin(0.1);
    // canvas->SetRightMargin(0.05);

    // Set log scale for x-axis and y-axis if needed
    gPad->SetLogx();
    gPad->SetLogy();
    gPad->Modified();
    gPad->Update();
    auto mg1 = new TMultiGraph();
    mg1->SetTitle("Lifetime study on LP LDO - stress; Time [days]; Vout Degradation [%]");
    // mg1->SetTitle("Lifetime study on LP LDO - nominal; Time [days]; Vout Degradation [%]");
    mg1->Add(gr1);
    mg1->Add(gr2);
    mg1->Add(gr3);
    mg1->Draw("AP");
    mg1->GetXaxis()->SetLimits(0.001, 1e12); // Set the limits for the x-axis of the multi-graph
    mg1->GetXaxis()->SetTitleOffset(1.5);
    mg1->SetMinimum(0.01); // Set the minimum for the y-axis
    mg1->SetMaximum(10);  // Set the maximum for the y-axis (adjust as needed)
    canvas->Update(); // Update the canvas to reflect the changes

    fitFunc1->SetLineColor(kBlue); // Optional: Set the line color to match the graph
    fitFunc1->Draw("SAME"); // Draw the fit on the same canvas

    fitFunc2->SetLineColor(kRed); // Optional: Set the line color to match the graph
    fitFunc2->Draw("SAME"); // Draw the fit on the same canvas

    fitFunc3->SetLineColor(kGreen+2); // Optional: Set the line color to match the graph
    fitFunc3->Draw("SAME"); // Draw the fit on the same canvas

    TLine *line1 = new TLine(0.001, 3, 1e12, 3);  // 3% degradation
    line1->SetLineColor(kBlack); // You can choose the color
    line1->SetLineStyle(2);       // Set the line style to dotted (2 is the style code for dotted lines in ROOT)
    line1->SetLineWidth(1);      // You can set the line width
    line1->Draw("same");         // "same" ensures it is drawn on the existing pad

    TLine *line2 = new TLine(pow(10, 4.039), 0.01, pow(10, 4.039), 10); // 30 years line
    line2->SetLineColor(kBlack); // You can choose the color
    line2->SetLineStyle(2);       // Set the line style to dotted (2 is the style code for dotted lines in ROOT)
    line2->SetLineWidth(1);      // You can set the line width
    line2->Draw("same");         // "same" ensures it is drawn on the existing pad

    TLine *line3 = new TLine(pow(10, 3.863), 0.01, pow(10, 3.863), 10); // 20 years line
    line3->SetLineColor(kBlack); // You can choose the color
    line3->SetLineStyle(2);       // Set the line style to dotted (2 is the style code for dotted lines in ROOT)
    line3->SetLineWidth(1);      // You can set the line width
    line3->Draw("same");         // "same" ensures it is drawn on the existing pad

    // // Add a legend
    TLegend *legend = new TLegend(0.1, 0.8, 0.3, 0.9);
    legend->AddEntry(gr1, "LP#13: Vnominal=7V, Vstress=9.5V", "lp");
    legend->AddEntry(gr2, "LP#16: Vnominal=7V, Vstress=10V", "lp");
    legend->AddEntry(gr3, "LP#20: Vnominal=7V, Vstress=10.5V", "lp");
    legend->Draw();

    // If you want to save the canvas as an ima
    canvas->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/Apr19/LP_stress_voltage_degradation_131620_wfit.png");
    canvas->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/Apr19/LP_stress_voltage_degradation_131620_wfit.root");
    // canvas->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/Apr19/LP_nominal_voltage_degradation.pdf");

}// end plot_degradation_LP_stress

void plot_degradation_ADM_stress() {

    TString FileIn1 = "/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/Apr19/LP19_7.00to10.00_ADM19_7.00to21.00.root";
    TString FileIn2 = "/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/Apr19/LP20_7.00to10.50_ADM20_7.00to18.00.root";
    TString FileIn3 = "/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/Apr19/LP18_7.00to9.50_ADM18_7.00to19.50.root";
    TString FileIn4 = "/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/Apr19/LP10_7.00to8.00_ADM10_7.00to16.00.root";


    // Create a new TChain instance to chain .root files together
    TChain *chain_s = new TChain("tree_s"); // Replace "tree_name" with the name of your TTree

    // Add .root files to the chain
    chain_s->Add(FileIn1.Data()); // Replace with the actual file paths and names
    chain_s->Add(FileIn2.Data()); // Replace with the actual file paths and names
    chain_s->Add(FileIn3.Data()); // Replace with the actual file paths and names
    chain_s->Add(FileIn4.Data()); // Replace with the actual file paths and names
    // Add as many files as you have

    // Variables to hold the data from the branches
    double degradationIni,degradationMax; // Replace with the actual branch names and appropriate data types
    double ADM_ave_s, LP_ave_s, t_measure_s;
    double D_LP_ini,D_LP_max,D_ADM_ini,D_ADM_max;
    double LP_ave_s_ini, LP_ave_s_min, LP_ave_s_max;
    double ADM_ave_s_ini, ADM_ave_s_min, ADM_ave_s_max;
    int batchNumber;
    // Set branch addresses
    chain_s->SetBranchAddress("ADM_ave_s", &ADM_ave_s);
    chain_s->SetBranchAddress("LP_ave_s", &LP_ave_s);
    chain_s->SetBranchAddress("t_measure_s", &t_measure_s);
    chain_s->SetBranchAddress("LP_ave_s_ini", &LP_ave_s_ini);
    chain_s->SetBranchAddress("LP_ave_s_max", &LP_ave_s_max);
    chain_s->SetBranchAddress("ADM_ave_s_ini", &ADM_ave_s_ini);
    chain_s->SetBranchAddress("ADM_ave_s_max", &ADM_ave_s_max);
    chain_s->SetBranchAddress("batchNumber", &batchNumber);
    // Create graphs
    // TMultiGraph *mg = new TMultiGraph("mg",mg);
    TGraph *gr1 = new TGraph();
    gr1->SetMarkerColor(kBlue);
    gr1->SetLineColor(kBlue);

    TGraph *gr2 = new TGraph();
    gr2->SetMarkerColor(kRed);
    gr2->SetLineColor(kRed);

    TGraph *gr3 = new TGraph();
    gr3->SetMarkerColor(kGreen+2);
    gr3->SetLineColor(kGreen+2);

    TGraph *gr4 = new TGraph();
    gr4->SetMarkerColor(kBlack);
    gr4->SetLineColor(kBlack);
    // You might need to create as many TGraphs as your datasets

    int n1 = 0, n2 = 0, n3 = 0, n4=0; // Indices for each graph
    double peaktime1 = 0.0208333;
    double peaktime2 = 0.0208333;
    double peaktime3 = 0.0208333;
    double peaktime4 = 0.0833333;
    // Loop over the chain and fill the graphs
    for (int i = 0; i < chain_s->GetEntries(); i++) {
        chain_s->GetEntry(i);
        // cout << i << ", " << D_LP_max << ", " << t_measure_s<< ", "<< LP_ave_s << endl;
        // if( LP_ave_s > LP_ave_s_max) continue;
        // cout << i << ", " << D_LP_max << ", " << t_measure_s<< ", "<< LP_ave_s << endl;

        D_ADM_max = (ADM_ave_s_max - ADM_ave_s)*100/ADM_ave_s_max;
        // D_LP_ini = (LP_ave_s - LP_ave_s_ini)*100/LP_ave_s_ini;

        t_measure_s = t_measure_s/(60*24); // change units to day
        if( D_ADM_max == 0) cout<< i << "max time: "<< t_measure_s << endl;
        // gr1->SetPoint(n1++, t_measure_s, D_LP_max);
        // // Depending on your condition, assign points to different graphs
        // // This is a placeholder; you'll need to replace it with your actual logic
        if (batchNumber==19 && t_measure_s>=peaktime1) {
            gr1->SetPoint(n1++, t_measure_s-peaktime1, D_ADM_max);
        } else if (batchNumber==20&& t_measure_s>=peaktime2) {
            gr2->SetPoint(n2++, t_measure_s-peaktime2, D_ADM_max);
        } else if (batchNumber== 18&& t_measure_s>=peaktime3) {
            gr3->SetPoint(n3++, t_measure_s-peaktime3, D_ADM_max);
        } else if (batchNumber== 10&& t_measure_s>=peaktime4) {
            gr4->SetPoint(n4++, t_measure_s-peaktime4, D_ADM_max);
        }
    }
    // Define fit functions, assuming you want to fit with a polynomial for example
    // TF1 *fitFunc1 = new TF1("fitFunc1", "[0]+x*[1]", 0.0208333, 1e12); // Linear fit for graph1
    // TF1 *fitFunc2 = new TF1("fitFunc2", "[0]+x*[1]", 0.0208333, 1e12); // Linear fit for graph2
    // TF1 *fitFunc3 = new TF1("fitFunc3", "[0]+x*[1]", 0.0208333, 1e12); // Linear fit for graph2
    //
    // // Fit the graphs, "Q" is for Quiet, "R" is for using the function range
    // gr1->Fit(fitFunc1, "QR");
    // gr2->Fit(fitFunc2, "QR");
    // gr3->Fit(fitFunc3, "QR");
    // Create a canvas to draw the plots
    TCanvas *canvas = new TCanvas("canvas", "Voltage Degradation", 2400, 1600);
    // canvas->SetLeftMargin(0.1);
    // canvas->SetRightMargin(0.05);

    // Set log scale for x-axis and y-axis if needed
    gPad->SetLogx();
    gPad->SetLogy();
    gPad->Modified();
    gPad->Update();
    auto mg1 = new TMultiGraph();
    mg1->SetTitle("Lifetime study on ADM LDO - stress; Time [days]; Vout Degradation [%]");
    mg1->Add(gr1);
    mg1->Add(gr2);
    mg1->Add(gr3);
    mg1->Add(gr4);
    // Draw the graphs on the canvas
    // gr1->SetLineColor(kBlue);
    mg1->Draw("APL");
    mg1->GetXaxis()->SetLimits(0.001, 1e12); // Set the limits for the x-axis of the multi-graph
    mg1->GetXaxis()->SetTitleOffset(1.5);
    mg1->SetMinimum(0.01); // Set the minimum for the y-axis
    mg1->SetMaximum(100);  // Set the maximum for the y-axis (adjust as needed)
    canvas->Update(); // Update the canvas to reflect the changes

    // fitFunc1->SetLineColor(kBlue); // Optional: Set the line color to match the graph
    // fitFunc1->Draw("SAME"); // Draw the fit on the same canvas
    //
    // fitFunc2->SetLineColor(kRed); // Optional: Set the line color to match the graph
    // fitFunc2->Draw("SAME"); // Draw the fit on the same canvas
    //
    // fitFunc3->SetLineColor(kGreen+2); // Optional: Set the line color to match the graph
    // fitFunc3->Draw("SAME"); // Draw the fit on the same canvas

    TLine *line1 = new TLine(0.001, 3, 1e12, 3);
    line1->SetLineColor(kBlack); // You can choose the color
    line1->SetLineStyle(2);       // Set the line style to dotted (2 is the style code for dotted lines in ROOT)
    line1->SetLineWidth(1);      // You can set the line width
    line1->Draw("same");         // "same" ensures it is drawn on the existing pad

    TLine *line2 = new TLine(pow(10, 4.039), 0.01, pow(10, 4.039), 100);
    line2->SetLineColor(kBlack); // You can choose the color
    line2->SetLineStyle(2);       // Set the line style to dotted (2 is the style code for dotted lines in ROOT)
    line2->SetLineWidth(1);      // You can set the line width
    line2->Draw("same");         // "same" ensures it is drawn on the existing pad

    TLine *line3 = new TLine(pow(10, 3.863), 0.01, pow(10, 3.863), 100);
    line3->SetLineColor(kBlack); // You can choose the color
    line3->SetLineStyle(2);       // Set the line style to dotted (2 is the style code for dotted lines in ROOT)
    line3->SetLineWidth(1);      // You can set the line width
    line3->Draw("same");         // "same" ensures it is drawn on the existing pad

    // // Add a legend
    TLegend *legend = new TLegend(0.1, 0.75, 0.35, 0.9);
    legend->AddEntry(gr1, "ADM#19: Vnominal=7V, Vstress=21V", "lp");
    legend->AddEntry(gr2, "ADM#20: Vnominal=7V, Vstress=18V", "lp");
    legend->AddEntry(gr3, "ADM#18: Vnominal=7V, Vstress=19.5V", "lp");
    legend->AddEntry(gr4, "ADM#10: Vnominal=7V, Vstress=16V", "lp");
    legend->Draw();

    // Draw the lifetime line and text
    // TLine *line = new TLine(1e7, 0.01, 1e7, 10); // Replace with the actual values
    // line->SetLineColor(kRed);
    // line->SetLineStyle(2);
    // line->Draw();

    // TText *text = new TText(1e7, 10, "Lifetime 4.1x10^{7} yrs");
    // text->SetTextAngle(90);
    // text->Draw();



    // If you want to save the canvas as an image
    canvas->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/Apr19/ADM_stress_voltage_degradation19201810.png");
    canvas->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/Apr19/ADM_stress_voltage_degradation19201810.root");

}// end plot_degradation_ADM_stress
