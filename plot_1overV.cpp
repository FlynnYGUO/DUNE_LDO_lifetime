#include <TCanvas.h>
#include <TGraph.h>
#include <TF1.h>
#include <TAxis.h>
#include <TLegend.h>
#include <TMath.h>
#include <TText.h>


void plot_1overV() {
    // Create the canvas
    TCanvas *c = new TCanvas("c", "Accelerated Lifetime Measurement", 2400, 1600);

    // Set log scale for both axes
    // c->SetLogx();
    // c->SetLogy();

    // Create a graph, here assuming you already have arrays x and y with the data
    // // batchNumber{17， 13， 16， 19， 15， 20}
    // double x[] = {1./9.5, 1./9.5, 1./10, 1./10, 1./10.5, 1./10.5}; // 1/V_DS values
    // // double y[] = {28.52203092, 26.88441412, 21.93553931, 10.46476363, 21.93212996, 29.29462041}; // Log10(Lifetime) values in hours
    // double y[] = {1.188417955, 1.120183922, 0.9139808048, 0.4360318177, 0.9138387483, 1.220609184};

    double x[] = {1./9, 1./9.5, 1./10, 1./10.5};
    double y[] = {1.674923836, 1.385305189, 1.02056528, 1.146807424};
    int n_points = 4; // Number of data points
    TGraph *gr = new TGraph(n_points, x, y);

    // Set graph styles
    gr->SetMarkerStyle(21); // Set the marker style to a suitable value
    gr->SetMarkerColor(kBlue); // Set marker color
    gr->SetLineColor(kBlue); // Set line color
    gr->SetTitle("Accelerated Lifetime Measurement;1/V_{DS} [V];Log10(Lifetime) [hour]");

    // Draw the graph
    gr->GetXaxis()->SetLimits(0, 0.25); // Set the limits for the x-axis of the multi-graph
    gr->GetXaxis()->SetTitleOffset(1);
    gr->SetMinimum(0); // Set the minimum for the y-axis
    gr->SetMaximum(10);  // Set the maximum for the y-axis (adjust as needed
    gr->Draw("AP"); // Axis, Line and Point

    // Fit the graph with a linear function since the log-log plot suggests a linear relationship
    TF1 *fitFunc = new TF1("fitFunc", "[0]*x + [1]", 0, 0.5); // Adjust the range as needed
    gr->Fit(fitFunc);

    // Optionally add other textual elements like in the image
    TLegend *leg = new TLegend(0.1, 0.8, 0.3, 0.9);
    leg->AddEntry(gr, "Lifetime estimation", "lp");
    leg->Draw();

    // Save the canvas
    c->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/Apr19/LP_Accelerated_Lifetime_Measurement.png");
}
