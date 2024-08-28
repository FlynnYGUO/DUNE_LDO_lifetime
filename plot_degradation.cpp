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

    TString FileIn1 = "/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24Jul2/LP10_7.00to8.00_ADM10_7.00to16.00.root";
    TString FileIn2 = "/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24May9/LP22_7.00to10.30_ADM22_7.00to10.30.root";
    TString FileIn3 = "/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24May9/LP23_7.00to10.30_ADM23_7.00to10.30.root";
    TString FileIn4 = "/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24Jul3/LP25_7.00to10.30_ADM25_7.00to10.30.root";
    TString FileIn5 = "/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24Aug2/LP26_7.00to10.30_ADM26_7.00to10.30.root";
    TString FileIn6 = "/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24May9/LP19_7.00to10.00_ADM19_7.00to21.00.root";


    // Create a new TChain instance to chain .root files together
    TChain *chain_s = new TChain("tree_s"); // Replace "tree_name" with the name of your TTree
    TChain *chain_n = new TChain("tree_n"); // Replace "tree_name" with the name of your TTree

    // Add .root files to the chain
    chain_s->Add(FileIn1.Data()); // Replace with the actual file paths and names
    chain_s->Add(FileIn2.Data()); // Replace with the actual file paths and names
    chain_s->Add(FileIn3.Data()); // Replace with the actual file paths and names
    chain_s->Add(FileIn4.Data()); // Replace with the actual file paths and names
    chain_s->Add(FileIn5.Data()); // Replace with the actual file paths and names
    chain_s->Add(FileIn6.Data()); // Replace with the actual file paths and names

    chain_n->Add(FileIn1.Data()); // Replace with the actual file paths and names
    chain_n->Add(FileIn2.Data()); // Replace with the actual file paths and names
    chain_n->Add(FileIn3.Data()); // Replace with the actual file paths and names
    chain_n->Add(FileIn4.Data()); // Replace with the actual file paths and names
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
    // gr1->SetMarkerStyle(20);
    gr1->SetLineColor(kBlue);

    TGraph *gr2 = new TGraph();
    gr2->SetMarkerColor(kRed);
    // gr2->SetMarkerStyle(20);
    gr2->SetLineColor(kRed);

    TGraph *gr3 = new TGraph();
    gr3->SetMarkerColor(kGreen+2);
    // gr3->SetMarkerStyle(20);
    gr3->SetLineColor(kGreen+2);

    TGraph *gr4 = new TGraph();
    gr4->SetMarkerColor(kBlack);
    // gr4->SetMarkerStyle(20);
    gr4->SetLineColor(kBlack);

    TGraph *gr5 = new TGraph();
    gr5->SetMarkerColor(kMagenta);
    // gr5->SetMarkerStyle(20);
    gr5->SetLineColor(kMagenta);

    TGraph *gr6 = new TGraph();
    gr6->SetMarkerColor(kCyan);
    // gr6->SetMarkerStyle(20);
    gr6->SetLineColor(kCyan);
    // You might need to create as many TGraphs as your datasets

    int n1 = 0, n2 = 0, n3 = 0, n4 = 0, n5=0,n6=0; // Indices for each graph
    double peaktime1 = 2.625;
    double peaktime2 = 0.125;
    double peaktime3 = 0.104167;
    double peaktime4 = 0.0625;

    bool firstFound = false; // Flag to check if the first occurrence is found

    // Loop over the chain and fill the graphs
    for (int i = 0; i < chain_s->GetEntries(); i++) {
        chain_s->GetEntry(i);
        // D_LP_max = (LP_ave_s_max - LP_ave_s)*100/LP_ave_s_max;
        D_LP_max = (LP_ave_s - LP_ave_s_ini)*100/LP_ave_s_ini;

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
        if (batchNumber_s==10) {
            gr1->SetPoint(n1++, t_measure_s, D_LP_max);
            if(n1==2) cout << "batchNumber: " << batchNumber_s << ", ADM_ave_s_ini: " << ADM_ave_s_ini << endl;
        } else if (batchNumber_s==22 ) {
            gr2->SetPoint(n2++, t_measure_s, D_LP_max);
            if(n2==2) cout << "batchNumber: " << batchNumber_s << ", ADM_ave_s_ini: " << ADM_ave_s_ini << endl;
        } else if (batchNumber_s==23 ) {
            gr3->SetPoint(n3++, t_measure_s, D_LP_max);
            if(n3==2) cout << "batchNumber: " << batchNumber_s << ", ADM_ave_s_ini: " << ADM_ave_s_ini << endl;
        } else if (batchNumber_s==25 ) {
            gr4->SetPoint(n4++, t_measure_s, D_LP_max);
            if(n4==2) cout << "batchNumber: " << batchNumber_s << ", ADM_ave_s_ini: " << ADM_ave_s_ini << endl;
        } else if (batchNumber_s==26 ) {
            gr5->SetPoint(n5++, t_measure_s, D_LP_max);
            if(n5==2) cout << "batchNumber: " << batchNumber_s << ", ADM_ave_s_ini: " << ADM_ave_s_ini << endl;
        }else if (batchNumber_s==19 ) {
            gr6->SetPoint(n6++, t_measure_s, D_LP_max);
            if(n6==2) cout << "batchNumber: " << batchNumber_s << ", ADM_ave_s_ini: " << ADM_ave_s_ini << endl;
        }
    }

    cout << "n1: " << n1 << endl;
    cout << "n2: " << n2 << endl;
    cout << "n3: " << n3 << endl;
    cout << "n4: " << n4 << endl;
    cout << "n5: " << n5 << endl;
    cout << "n6: " << n6 << endl;

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


    // // Define fit functions, assuming you want to fit with a polynomial for example
    // TF1 *fitFunc1 = new TF1("fitFunc1", "[0]*log(x+[1]) + [2]", peaktime1, 1e12); // Linear fit for graph1
    // TF1 *fitFunc2 = new TF1("fitFunc2", "[0]*log(x+[1]) + [2]", peaktime2, 1e12); // Linear fit for graph2
    // TF1 *fitFunc3 = new TF1("fitFunc3", "[0]*log(x+[1]) + [2]", peaktime3, 1e12); // Linear fit for graph2
    // TF1 *fitFunc4 = new TF1("fitFunc4", "[0]*log(x+[1]) + [2]", peaktime4, 1e12); // Linear fit for graph2
    //
    // // Fit the graphs, "Q" is for Quiet, "R" is for using the function range
    // gr1->Fit(fitFunc1, "LR+");
    // gr2->Fit(fitFunc2, "LR+");
    // gr3->Fit(fitFunc3, "LR+");
    // gr4->Fit(fitFunc4, "LR+");
    // Create a canvas to draw the plots
    TCanvas *canvas = new TCanvas("canvas", "Voltage Degradation", 2400, 1600);
    // canvas->SetLeftMargin(0.1);
    // canvas->SetRightMargin(0.05);

    // Set log scale for x-axis and y-axis if needed
    gPad->SetLogx();
    // gPad->SetLogy();
    gPad->Modified();
    gPad->Update();
    auto mg1 = new TMultiGraph();
    mg1->SetTitle("Lifetime study on LP LDO - stress; Time [days]; Vout Degradation [%]");
    // mg1->SetTitle("Lifetime study on LP LDO - nominal; Time [days]; Vout Degradation [%]");
    // mg1->Add(gr1);
    mg1->Add(gr2);
    mg1->Add(gr3);
    mg1->Add(gr4);
    mg1->Add(gr5);
    mg1->Add(gr6);
    mg1->Draw("APL");
    mg1->GetXaxis()->SetLimits(0.001, 1e6); // Set the limits for the x-axis of the multi-graph
    mg1->GetXaxis()->SetTitleOffset(1.5);
    // mg1->SetMinimum(0.01); // Set the minimum for the y-axis
    // mg1->SetMaximum(10);  // Set the maximum for the y-axis (adjust as needed)
    mg1->SetMinimum(-1); // Set the minimum for the y-axis
    mg1->SetMaximum(1);  // Set the maximum for the y-axis (adjust as needed)
    canvas->Update(); // Update the canvas to reflect the changes

    // fitFunc1->SetLineColor(kBlue); // Optional: Set the line color to match the graph
    // fitFunc1->Draw("SAME"); // Draw the fit on the same canvas

    // fitFunc2->SetLineColor(kRed); // Optional: Set the line color to match the graph
    // fitFunc2->Draw("SAME"); // Draw the fit on the same canvas
    //
    // fitFunc3->SetLineColor(kGreen+2); // Optional: Set the line color to match the graph
    // fitFunc3->Draw("SAME"); // Draw the fit on the same canvas
    //
    // fitFunc4->SetLineColor(kBlack); // Optional: Set the line color to match the graph
    // fitFunc4->Draw("SAME"); // Draw the fit on the same canvas

    TLine *line1 = new TLine(0.001, 3, 1e12, 3);  // 3% degradation
    line1->SetLineColor(kBlack); // You can choose the color
    line1->SetLineStyle(2);       // Set the line style to dotted (2 is the style code for dotted lines in ROOT)
    line1->SetLineWidth(1);      // You can set the line width
    line1->Draw("same");         // "same" ensures it is drawn on the existing pad

    // TLine *line2 = new TLine(pow(10, 4.039), 0.01, pow(10, 4.039), 100);
    TLine *line2 = new TLine(pow(10, 4.039), -1, pow(10, 4.039), 1);
    line2->SetLineColor(kBlack); // You can choose the color
    line2->SetLineStyle(2);       // Set the line style to dotted (2 is the style code for dotted lines in ROOT)
    line2->SetLineWidth(1);      // You can set the line width
    line2->Draw("same");         // "same" ensures it is drawn on the existing pad

    // TLine *line3 = new TLine(pow(10, 3.863), 0.01, pow(10, 3.863), 100);
    TLine *line3 = new TLine(pow(10, 3.863), -1, pow(10, 3.863), 1);
    line3->SetLineColor(kBlack); // You can choose the color
    line3->SetLineStyle(2);       // Set the line style to dotted (2 is the style code for dotted lines in ROOT)
    line3->SetLineWidth(1);      // You can set the line width
    line3->Draw("same");         // "same" ensures it is drawn on the existing pad

    // Add a legend
    TLegend *legend = new TLegend(0.1, 0.7, 0.4, 0.9);
    // legend->AddEntry(gr1, "LP#10: Vnominal=7V, Vstress=8V, Vini=5.05167V", "lp");
    legend->AddEntry(gr2, "LP#22: Vnominal=7V, Vstress=10.3V, Vini=5.12677V", "lp");
    legend->AddEntry(gr3, "LP#23: Vnominal=7V, Vstress=10.3V, Vini=5.06292V", "lp");
    legend->AddEntry(gr4, "LP#25: Vnominal=7V, Vstress=10.3V, Vini=5.00844V", "lp");
    legend->AddEntry(gr5, "LP#26: Vnominal=7V, Vstress=10.3V, Vini=5.05683V", "lp");
    legend->AddEntry(gr6, "LP#19: Vnominal=7V, Vstress=10V, Vini=5.09114V", "lp");
    legend->Draw();

    // If you want to save the canvas as an ima
    canvas->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24Aug2/LP_stress_voltage_degradation_102223252619.png");
    canvas->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24Aug2/LP_stress_voltage_degradation_102223252619.root");
    // canvas->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24May9/LP_nominal_voltage_degradation.pdf");

}// end plot_degradation_LP_stress

void plot_degradation_ADM_stress() {

    TString FileIn1 = "/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24May9/LP19_7.00to10.00_ADM19_7.00to21.00.root";
    // TString FileIn2 = "/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24May9/LP11_7.00to9.00_ADM11_7.00to18.00.root";
    TString FileIn2 = "/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24May9/LP22_7.00to10.30_ADM22_7.00to10.30.root";
    TString FileIn3 = "/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24May9/LP12_7.00to9.50_ADM12_7.00to19.50.root";
    TString FileIn4 = "/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24May9/LP10_7.00to8.00_ADM10_7.00to16.00.root";
    TString FileIn5 = "/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24May9/LP23_7.00to10.30_ADM23_7.00to10.30.root";
    TString FileIn6 = "/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24Jul3/LP25_7.00to10.30_ADM25_7.00to10.30.root";
    TString FileIn7 = "/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24Aug2/LP26_7.00to10.30_ADM26_7.00to10.30.root";


    // Create a new TChain instance to chain .root files together
    TChain *chain_s = new TChain("tree_s"); // Replace "tree_name" with the name of your TTree

    // Add .root files to the chain
    chain_s->Add(FileIn1.Data()); // Replace with the actual file paths and names
    chain_s->Add(FileIn2.Data()); // Replace with the actual file paths and names
    chain_s->Add(FileIn3.Data()); // Replace with the actual file paths and names
    chain_s->Add(FileIn4.Data()); // Replace with the actual file paths and names
    chain_s->Add(FileIn5.Data()); // Replace with the actual file paths and names
    chain_s->Add(FileIn6.Data()); // Replace with the actual file paths and names
    chain_s->Add(FileIn7.Data()); // Replace with the actual file paths and names
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

    TGraph *gr5 = new TGraph();
    gr5->SetMarkerColor(kRed-2);
    gr5->SetLineColor(kRed-2);

    TGraph *gr6 = new TGraph();
    gr6->SetMarkerColor(kMagenta);
    gr6->SetLineColor(kMagenta);

    TGraph *gr7 = new TGraph();
    gr7->SetMarkerColor(kCyan);
    gr7->SetLineColor(kCyan);
    // You might need to create as many TGraphs as your datasets

    int n1 = 0, n2 = 0, n3 = 0, n4=0, n5=0, n6=0,n7=0; // Indices for each graph
    // double peaktime1 = 0.0208333;
    // double peaktime2 = 0.0208333;
    // double peaktime3 = 0.0208333;
    // double peaktime4 = 0.0833333;
    // double peaktime5 = 1.02083;
    // Loop over the chain and fill the graphs
    for (int i = 0; i < chain_s->GetEntries(); i++) {
        chain_s->GetEntry(i);
        // cout << i << ", " << D_LP_max << ", " << t_measure_s<< ", "<< LP_ave_s << endl;
        // if( LP_ave_s > LP_ave_s_max) continue;
        // cout << i << ", " << D_LP_max << ", " << t_measure_s<< ", "<< LP_ave_s << endl;

        // Compared to the first peak value
        // D_ADM_max = (ADM_ave_s_max - ADM_ave_s)*100/ADM_ave_s_max;
        // Compared to the initial value
        D_ADM_max = (ADM_ave_s - ADM_ave_s_ini)*100/ADM_ave_s_ini;
        // cout << "D_ADM_max: " << D_ADM_max << endl;
        t_measure_s = t_measure_s/(60*24); // change units to day
        if( D_ADM_max == 0) cout<< i << ", max time: "<< t_measure_s << endl;
        // gr1->SetPoint(n1++, t_measure_s, D_LP_max);
        // // Depending on your condition, assign points to different graphs
        // // This is a placeholder; you'll need to replace it with your actual logic
        if ( batchNumber==19 ) {
            gr1->SetPoint(n1++, t_measure_s, D_ADM_max);
            if(n1==2) cout << "batchNumber: " << batchNumber << ", ADM_ave_s_ini: " << ADM_ave_s_ini << endl;
        } else if ( batchNumber==22 ) {
            gr2->SetPoint(n2++, t_measure_s, D_ADM_max);
            if(n2==2) cout << "batchNumber: " << batchNumber << ", ADM_ave_s_ini: " << ADM_ave_s_ini << endl;
        } else if ( batchNumber== 12 ) {
            gr3->SetPoint(n3++, t_measure_s, D_ADM_max);
            if(n3==2) cout << "batchNumber: " << batchNumber << ", ADM_ave_s_ini: " << ADM_ave_s_ini << endl;
        } else if ( batchNumber== 10 ) {
            gr4->SetPoint(n4++, t_measure_s, D_ADM_max);
            if(n4==2) cout << "batchNumber: " << batchNumber << ", ADM_ave_s_ini: " << ADM_ave_s_ini << endl;
        } else if ( batchNumber== 23 ) {
            gr5->SetPoint(n5++, t_measure_s, D_ADM_max);
            if(n5==2) cout << "batchNumber: " << batchNumber << ", ADM_ave_s_ini: " << ADM_ave_s_ini << endl;
        } else if ( batchNumber== 25 ) {
            gr6->SetPoint(n6++, t_measure_s, D_ADM_max);
            if(n6==2) cout << "batchNumber: " << batchNumber << ", ADM_ave_s_ini: " << ADM_ave_s_ini << endl;
        } else if ( batchNumber== 26 ) {
            gr7->SetPoint(n7++, t_measure_s, D_ADM_max);
            if(n7==2) cout << "batchNumber: " << batchNumber << ", ADM_ave_s_ini: " << ADM_ave_s_ini << endl;
        }
    }

    cout << "n1: " << n1 << endl;
    cout << "n2: " << n2 << endl;
    cout << "n3: " << n3 << endl;
    cout << "n4: " << n4 << endl;
    cout << "n5: " << n5 << endl;
    cout << "n6: " << n6 << endl;
    cout << "n7: " << n7 << endl;


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
    // gPad->SetLogy();
    gPad->Modified();
    gPad->Update();
    auto mg1 = new TMultiGraph();
    mg1->SetTitle("Lifetime study on ADM LDO - stress; Time [days]; Vout Degradation [%]");
    mg1->Add(gr1);
    mg1->Add(gr2);
    mg1->Add(gr3);
    mg1->Add(gr4);
    mg1->Add(gr5);
    mg1->Add(gr6);
    mg1->Add(gr7);
    // Draw the graphs on the canvas
    // gr1->SetLineColor(kBlue);
    mg1->Draw("APL");
    mg1->GetXaxis()->SetLimits(0.001, 1e6); // Set the limits for the x-axis of the multi-graph
    mg1->GetXaxis()->SetTitleOffset(1.5);
    // mg1->SetMinimum(0.01); // Set the minimum for the y-axis
    // mg1->SetMaximum(100);  // Set the maximum for the y-axis (adjust as needed)
    mg1->SetMinimum(-1); // Set the minimum for the y-axis
    mg1->SetMaximum(1);  // Set the maximum for the y-axis (adjust as needed)
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

    // TLine *line2 = new TLine(pow(10, 4.039), 0.01, pow(10, 4.039), 100);
    TLine *line2 = new TLine(pow(10, 4.039), -1, pow(10, 4.039), 1);
    line2->SetLineColor(kBlack); // You can choose the color
    line2->SetLineStyle(2);       // Set the line style to dotted (2 is the style code for dotted lines in ROOT)
    line2->SetLineWidth(1);      // You can set the line width
    line2->Draw("same");         // "same" ensures it is drawn on the existing pad

    // TLine *line3 = new TLine(pow(10, 3.863), 0.01, pow(10, 3.863), 100);
    TLine *line3 = new TLine(pow(10, 3.863), -1, pow(10, 3.863), 1);
    line3->SetLineColor(kBlack); // You can choose the color
    line3->SetLineStyle(2);       // Set the line style to dotted (2 is the style code for dotted lines in ROOT)
    line3->SetLineWidth(1);      // You can set the line width
    line3->Draw("same");         // "same" ensures it is drawn on the existing pad

    // // Add a legend
    TLegend *legend = new TLegend(0.1, 0.7, 0.4, 0.9);
    legend->AddEntry(gr1, "ADM#19: Vnominal=7V, Vstress=21V, Vini=5.09114V", "lp");
    legend->AddEntry(gr2, "ADM#22: Vnominal=7V, Vstress=10.3V, Vini=5.12677V", "lp");
    legend->AddEntry(gr3, "ADM#12: Vnominal=7V, Vstress=19.5V, Vini=5.0344V", "lp");
    legend->AddEntry(gr4, "ADM#10: Vnominal=7V, Vstress=16V, Vini=5.05167V", "lp");
    legend->AddEntry(gr5, "ADM#23: Vnominal=7V, Vstress=10.3V, Vini=5.06292V", "lp");
    legend->AddEntry(gr6, "ADM#25: Vnominal=7V, Vstress=10.3V, Vini=5.00844V", "lp");
    legend->AddEntry(gr7, "ADM#26: Vnominal=7V, Vstress=10.3V, Vini=5.05683V", "lp");
    legend->Draw();

    // If you want to save the canvas as an image
    canvas->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24Aug2/ADM_stress_voltage_degradation19221210232526.png");
    canvas->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24Aug2/ADM_stress_voltage_degradation19221210232526.root");

}// end plot_degradation_ADM_stress
