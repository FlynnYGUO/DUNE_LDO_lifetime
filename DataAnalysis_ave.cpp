#include <iostream>
#include <fstream>
#include <cstdlib> // For exit()
#include <string>  // For string
#include <vector>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstdlib>


#include <TSystem.h> // For gSystem

using namespace std;

void DataAnalysis_ave(string fileName, string date, int batchNumber, float LP_NominalV, float LP_StressV, float ADM_NominalV, float ADM_StressV)
// void DataAnalysis_ave(const char* fileName, const char* date, const char* batchNumber)
{
  // // Ensure at least two arguments are provided (the filename and the date)
  // if (argc < 3) {
  //     cout << "Usage: " << argv[0] << " <filename> <date>" << endl;
  //     exit(1); // Exit if the required arguments are not given
  // }
  // string fullPath = basePath + fileName + "/" + fileName + ".csv";

  string basePath = "/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/";
  // string fileName = argv[1];
  // string date = argv[2]; // The second command line argument for the date
  string fullPath = basePath + fileName + "/" + fileName + ".csv";

  // Create directory with the date provided
  TString dirPath = TString::Format("%sPlots/%s/", basePath.c_str(), date.c_str());
  gSystem->mkdir(dirPath, kTRUE); // Ensure the directory is created
  TString basePlotPath = TString::Format("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/%s/", date.c_str());

  fstream dataset1(fullPath.c_str(), ios::in); // Open the file

  // // Read File1
  // fstream dataset1("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Tester1_LP12NewBatch_Vin7-9p5_Tester2_ADM12NewBatch_Vin7-19p5_LN2_StressTest_Jan8/Tester1_LP12NewBatch_Vin7-9p5_Tester2_ADM12NewBatch_Vin7-19p5_LN2_StressTest_Jan8.csv",ios::in);
  // Get rid of the 1st line;
  string dummyLine1;
  getline(dataset1, dummyLine1);
  string oneline1;

  // Make vectors
  vector<double> time_year,time_hour,K2470_V,K2470_I,K2460_V,K2460_I,LP_Vout,ADM_Vout;

  //read data from cvs
  while(dataset1)
  {
    getline(dataset1,oneline1);
    TString x = oneline1;
    if(dataset1.eof()) break;
    TObjArray *tx = x.Tokenize(", ");

    for (int i = 0; i < tx->GetEntries(); i++)
    {
      TString y;//without comma
      y = ((TObjString *)(tx->At(i)))->String();
      double b = y.Atof();
      if ( i == 0) {time_year.emplace_back(b);}
      if ( i == 1) {time_hour.emplace_back(b);}
      if ( i == 2) {K2470_V.emplace_back(b);}
      if ( i == 3) {K2470_I.emplace_back(b);}
      if ( i == 4) {K2460_V.emplace_back(b);}
      if ( i == 5) {K2460_I.emplace_back(b);}
      if ( i == 6) {LP_Vout.emplace_back(b);}
      if ( i == 7) {ADM_Vout.emplace_back(b);}
    }// end read data loop
  } // end read data from file 1

  // Find avarage_Stress
  double ADM_sum_s = 0, counter_s = 0, ADM_Average_s = 0;
  double ADM_sum_n = 0, counter_n = 0, ADM_Average_n = 0;
  vector<double> ADM_ave_s,ADM_ave_n;

  double LP_sum_s = 0, LP_Average_s = 0;
  double LP_sum_n = 0, LP_Average_n = 0;
  vector<double> LP_ave_s,LP_ave_n;

  double K2460_sum_s = 0, Kcounter_s = 0, K2460_Average_s = 0;
  double K2460_sum_n = 0, Kcounter_n = 0, K2460_Average_n = 0;
  vector<double> K2460_ave_s,K2460_ave_n;

  double K2470_sum_s = 0, K2470_Average_s = 0;
  double K2470_sum_n = 0, K2470_Average_n = 0;
  vector<double> K2470_ave_s,K2470_ave_n;

  for (int i = 0; i < time_year.size(); i++)
  {
    // Discard abNominal data
    if( K2460_V.at(i) < 6 )
    {
      cout << "abNominal voltage which is smaller than 6V" << endl;
      continue;
    }
    // Stress
    while(K2460_V.at(i)>9)
    {
      ADM_sum_s += ADM_Vout.at(i);
      ++counter_s;
      ADM_Average_s =  ADM_sum_s / counter_s;

      LP_sum_s += LP_Vout.at(i);
      LP_Average_s = LP_sum_s / counter_s;

      K2460_sum_s += K2460_I.at(i);
      ++Kcounter_s;
      K2460_Average_s =  K2460_sum_s / Kcounter_s;

      K2470_sum_s += K2470_I.at(i);
      K2470_Average_s =  K2470_sum_s / Kcounter_s;


      cout << "Stress_i: " << i << endl;

      if(i < time_year.size()-2 && K2460_V.at(i+1)<9)
      {
        ADM_ave_s.emplace_back(ADM_Average_s);
        ADM_sum_s = 0;
        counter_s = 0;
        ADM_Average_s = 0;

        LP_ave_s.emplace_back(LP_Average_s);
        LP_sum_s = 0;
        LP_Average_s = 0;

        K2460_ave_s.emplace_back(K2460_Average_s);
        K2460_sum_s = 0;
        Kcounter_s = 0;
        K2460_Average_s = 0;

        K2470_ave_s.emplace_back(K2470_Average_s);
        K2470_sum_s = 0;
        K2470_Average_s = 0;
      }
      break;
    }
    // Nominal
    while(K2460_V.at(i)<9)
    {
      ADM_sum_n += ADM_Vout.at(i);
      ++counter_n;
      ADM_Average_n =  ADM_sum_n / counter_n;

      LP_sum_n += LP_Vout.at(i);
      LP_Average_n = LP_sum_n / counter_n;

      K2460_sum_n += K2460_I.at(i);
      ++Kcounter_n;
      K2460_Average_n =  K2460_sum_n / Kcounter_n;

      K2470_sum_n += K2470_I.at(i);
      K2470_Average_n =  K2470_sum_n / Kcounter_n;


      cout << "Nominal_i: " << i << endl;

      if(i < time_year.size()-2 && K2460_V.at(i+1)>9)
      {
        ADM_ave_n.emplace_back(ADM_Average_n);
        ADM_sum_n = 0;
        counter_n = 0;
        ADM_Average_n = 0;

        LP_ave_n.emplace_back(LP_Average_n);
        LP_sum_n = 0;
        LP_Average_n = 0;

        K2460_ave_n.emplace_back(K2460_Average_n);
        K2460_sum_n = 0;
        Kcounter_n = 0;
        K2460_Average_n = 0;

        K2470_ave_n.emplace_back(K2470_Average_n);
        K2470_sum_n = 0;
        K2470_Average_n = 0;
      }
      break;
    }
  }

  // Draw plots
  int size_s = ADM_ave_s.size();
  int size_n = ADM_ave_n.size();
  cout << "ADM_ave_s size: " << size_s << endl;
  // for (int i = 0; i < size_s; i++)
  // {
  //   // cout<< "ADM_Stress_ave_i: " << ADM_ave_s.at(i) << endl;
  //   // cout<< "LP_Stress_ave_i: " << LP_ave_s.at(i) << endl;
  //   cout<< "K2470_ave_i: " << K2470_ave_s.at(i) << endl;
  //   cout<< "K2460_ave_i: " << K2460_ave_s.at(i) << endl;
  // }

  cout << "ADM_ave_n size: " << size_n << endl;
  // for (int i = 0; i < size_n; i++)
  // {
  //   // cout<< "ADM_Nominal_ave_i: " << ADM_ave_n.at(i) << endl;
  //   // cout<< "LP_Nominal_ave_i: " << LP_ave_n.at(i) << endl;
  //   cout<< "K2470_ave_i: " << K2470_ave_n.at(i) << endl;
  //   cout<< "K2460_ave_i: " << K2460_ave_n.at(i) << endl;
  // }

  double A_ADM_ave_s[size_s], A_ADM_ave_n[size_n];
  double A_LP_ave_s[size_s], A_LP_ave_n[size_n];
  double A_K2460_ave_s[size_s], A_K2460_ave_n[size_n];
  double A_K2470_ave_s[size_s], A_K2470_ave_n[size_n];
  double A_t_measure_S[size_s], A_t_measure_N[size_n];

  double A_ADM_ave_s_ini = ADM_ave_s.at(0), A_ADM_ave_s_min = ADM_ave_s.at(0), A_ADM_ave_s_max = ADM_ave_s.at(0);
  double A_ADM_ave_n_ini = ADM_ave_n.at(0), A_ADM_ave_n_min = ADM_ave_n.at(0), A_ADM_ave_n_max = ADM_ave_n.at(0);
  double A_LP_ave_s_ini = LP_ave_s.at(0), A_LP_ave_s_min = LP_ave_s.at(0), A_LP_ave_s_max = LP_ave_s.at(0);
  double A_LP_ave_n_ini = LP_ave_n.at(0), A_LP_ave_n_min = LP_ave_n.at(0), A_LP_ave_n_max = LP_ave_n.at(0);
  double A_K2460_ave_s_ini = K2460_ave_s.at(0), A_K2460_ave_s_min = K2460_ave_s.at(0), A_K2460_ave_s_max = K2460_ave_s.at(0);
  double A_K2460_ave_n_ini = K2460_ave_n.at(0), A_K2460_ave_n_min = K2460_ave_n.at(0), A_K2460_ave_n_max = K2460_ave_n.at(0);
  double A_K2470_ave_s_ini = K2470_ave_s.at(0), A_K2470_ave_s_min = K2470_ave_s.at(0), A_K2470_ave_s_max = K2470_ave_s.at(0);
  double A_K2470_ave_n_ini = K2470_ave_n.at(0), A_K2470_ave_n_min = K2470_ave_n.at(0), A_K2470_ave_n_max = K2470_ave_n.at(0);

  size_s = 67; // zoom in the first 2000 min of Stress test 67=2000/30
  size_n = 136; //zoom in the first 500 min of Nominal test 100=500/5

  // Stress
  for (int i = 0; i < size_s; i++)
  {

    A_ADM_ave_s[i]=ADM_ave_s.at(i);
    if ( A_ADM_ave_s[i] < A_ADM_ave_s_min ) A_ADM_ave_s_min = A_ADM_ave_s[i];
    if ( A_ADM_ave_s[i] > A_ADM_ave_s_max ) A_ADM_ave_s_max = A_ADM_ave_s[i];

    A_LP_ave_s[i]=LP_ave_s.at(i);
    if ( A_LP_ave_s[i] < A_LP_ave_s_min ) A_LP_ave_s_min = A_LP_ave_s[i];
    if ( A_LP_ave_s[i] > A_LP_ave_s_max ) A_LP_ave_s_max = A_LP_ave_s[i];

    A_K2460_ave_s[i]=K2460_ave_s.at(i);
    if ( A_K2460_ave_s[i] < A_K2460_ave_s_min ) A_K2460_ave_s_min = A_K2460_ave_s[i];
    if ( A_K2460_ave_s[i] > A_K2460_ave_s_max ) A_K2460_ave_s_max = A_K2460_ave_s[i];

    A_K2470_ave_s[i]=K2470_ave_s.at(i);
    if ( A_K2470_ave_s[i] < A_K2470_ave_s_min ) A_K2470_ave_s_min = A_K2470_ave_s[i];
    if ( A_K2470_ave_s[i] > A_K2470_ave_n_max ) A_K2470_ave_n_max = A_K2470_ave_s[i];

    A_t_measure_S[i]=(i+1)*30;

  }
  // Nominal
  for (int i = 0; i < size_n; i++)
  {

    A_ADM_ave_n[i]=ADM_ave_n.at(i);
    if ( A_ADM_ave_n[i] < A_ADM_ave_n_min ) A_ADM_ave_n_min = A_ADM_ave_n[i];
    if ( A_ADM_ave_n[i] > A_ADM_ave_n_max ) A_ADM_ave_n_max = A_ADM_ave_n[i];

    A_LP_ave_n[i]=LP_ave_n.at(i);
    if ( A_LP_ave_n[i] <= A_LP_ave_n_min ) A_LP_ave_n_min = A_LP_ave_n[i];
    if ( A_LP_ave_n[i] >= A_LP_ave_n_max ) A_LP_ave_n_max = A_LP_ave_n[i];

    A_K2460_ave_n[i]=K2460_ave_n.at(i);
    if ( A_K2460_ave_n[i] < A_K2460_ave_n_min ) A_K2460_ave_n_min = A_K2460_ave_n[i];
    if ( A_K2460_ave_n[i] > A_K2460_ave_n_max ) A_K2460_ave_n_max = A_K2460_ave_n[i];

    A_K2470_ave_n[i]=K2470_ave_n.at(i);
    if ( A_K2470_ave_n[i] < A_K2470_ave_n_min ) A_K2470_ave_n_min = A_K2470_ave_n[i];
    if ( A_K2470_ave_n[i] > A_K2470_ave_n_max ) A_K2470_ave_n_max = A_K2470_ave_n[i];

    A_t_measure_N[i]=(i+1)*5;
  }
  //

  //
  TGraph *gr1  = new TGraph(size_s,A_t_measure_S,A_ADM_ave_s);
  gr1->SetMarkerColor(kBlue);
  gr1->SetMarkerStyle(20);

  TGraph *gr2  = new TGraph(size_n,A_t_measure_N,A_ADM_ave_n);
  gr2->SetMarkerColor(kBlue);
  gr2->SetMarkerStyle(21);

  TGraph *gr3  = new TGraph(size_s,A_t_measure_S,A_LP_ave_s);
  gr3->SetMarkerColor(kRed);
  gr3->SetMarkerStyle(20);

  TGraph *gr4  = new TGraph(size_n,A_t_measure_N,A_LP_ave_n);
  gr4->SetMarkerColor(kRed);
  gr4->SetMarkerStyle(21);

  TGraph *gr5  = new TGraph(size_s,A_t_measure_S,A_K2470_ave_s); // 2470=LP
  gr5->SetMarkerColor(kGreen+2);
  gr5->SetMarkerStyle(20);

  TGraph *gr6  = new TGraph(size_n,A_t_measure_N,A_K2470_ave_n); // 2470=LP
  gr6->SetMarkerColor(kGreen+2);
  gr6->SetMarkerStyle(21);

  TGraph *gr7  = new TGraph(size_s,A_t_measure_S,A_K2460_ave_s);
  gr7->SetMarkerColor(kBlack);
  gr7->SetMarkerStyle(20);

  TGraph *gr8  = new TGraph(size_n,A_t_measure_N,A_K2460_ave_n);
  gr8->SetMarkerColor(kBlack);
  gr8->SetMarkerStyle(21);



  TCanvas *c1 = new TCanvas("c1","LPNominalTest",2600,1600);
  c1->SetLeftMargin(0.15);
  c1->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg1 = new TMultiGraph();
  TString title1 = Form("LP#%d LDO Nominal test (Vin=%.2fV) in LN2; Total measured time (min); LDO Vout (V)", batchNumber, LP_NominalV);
  mg1->SetTitle(title1);
  mg1->Add(gr4);
  mg1->Draw("AP"); // deleta "Ap" if you want to draw lines
  // c1->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24Jan16/LP12_LDO_NominalTest_ave.png");
  c1->SaveAs(TString::Format("%sLP%d_LDO_NominalTest_ave.png", basePlotPath.Data(), batchNumber));

  TCanvas *c2 = new TCanvas("c2","LPStressTest",2600,1600);
  c2->SetLeftMargin(0.15);
  c2->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg2 = new TMultiGraph();
  TString title2 = Form("LP#%d LDO Stress test (Vin=%.2fV) in LN2; Total measured time (min); LDO Vout (V)", batchNumber, LP_StressV);
  mg2->SetTitle(title2);
  mg2->Add(gr3);
  // mg2->GetYaxis()->SetRangeUser(5.710,5.855);
  mg2->Draw("AP"); // deleta "Ap" if you want to draw lines
  // c2->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24Jan16/LP12_LDO_StressTest_ave.png");
  c2->SaveAs(TString::Format("%sLP%d_LDO_StressTest_ave.png", basePlotPath.Data(), batchNumber));

  TCanvas *c3 = new TCanvas("c3","ADMNominalTest",2600,1600);
  c3->SetLeftMargin(0.15);
  c3->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg3 = new TMultiGraph();
  TString title3 = Form("ADM#%d LDO Nominal test (Vin=%.2fV) in LN2; Total measured time (min); LDO Vout (V)", batchNumber, ADM_NominalV);
  mg3->SetTitle(title3);
  mg3->Add(gr2);
  mg3->Draw("AP"); // deleta "Ap" if you want to draw lines
  // c3->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24Jan16/ADM12_LDO_NominalTest_ave.png");
  c3->SaveAs(TString::Format("%sADM%d_LDO_NominalTest_ave.png", basePlotPath.Data(), batchNumber));

  TCanvas *c5 = new TCanvas("c5","ADMStressTest",2600,1600);
  c5->SetLeftMargin(0.15);
  c5->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg5 = new TMultiGraph();
  TString title5 = Form("ADM#%d LDO Stress test (Vin=%.2fV) in LN2; Total measured time (min); LDO Vout (V)", batchNumber, ADM_StressV);
  mg5->SetTitle(title5);
  mg5->Add(gr1);
  mg5->Draw("AP"); // deleta "Ap" if you want to draw lines
  // c5->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24Jan16/ADM12_LDO_StressTest_ave.png");
  c5->SaveAs(TString::Format("%sADM%d_LDO_StressTest_ave.png", basePlotPath.Data(), batchNumber));

  TCanvas *c6 = new TCanvas("c6","LPNominalTest",2600,1600);
  c6->SetLeftMargin(0.15);
  c6->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg6 = new TMultiGraph();
  TString title6 = Form("LP#%d LDO Nominal test (Vin=%.2fV) in LN2; Total measured time (min); Power Supply Iout (A)", batchNumber, LP_NominalV);
  mg6->SetTitle(title6);
  mg6->Add(gr6);
  mg6->Draw("AP"); // deleta "Ap" if you want to draw lines

  // c6->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24Jan16/LP12_LDO_NominalTest_PS_Iout_ave.png");
  c6->SaveAs(TString::Format("%sLP%d_LDO_NominalTest_PS_Iout_ave.png", basePlotPath.Data(), batchNumber));


  TCanvas *c7 = new TCanvas("c7","LPStressTest",2600,1600);
  c7->SetLeftMargin(0.15);
  c7->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg7 = new TMultiGraph();
  TString title7 = Form("LP#%d LDO Stress test (Vin=%.2fV) in LN2; Total measured time (min); Power Supply Iout (A)", batchNumber, LP_StressV);
  mg7->SetTitle(title7);
  mg7->Add(gr5);
  // mg2->GetYaxis()->SetRangeUser(5.710,5.855);
  mg7->Draw("AP"); // deleta "Ap" if you want to draw lines
  // c7->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24Jan16/LP12_LDO_StressTest_PS_Iout_ave.png");
  c7->SaveAs(TString::Format("%sLP%d_LDO_StressTest_PS_Iout_ave.png", basePlotPath.Data(), batchNumber));

  TCanvas *c8 = new TCanvas("c8","ADMNominalTest",2600,1600);
  c8->SetLeftMargin(0.15);
  c8->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg8 = new TMultiGraph();
  TString title8 = Form("ADM#%d LDO Nominal test (Vin=%.2fV) in LN2; Total measured time (min); Power Supply Iout (A)", batchNumber, LP_StressV);
  mg8->SetTitle(title8);
  mg8->Add(gr8);
  mg8->Draw("AP"); // deleta "Ap" if you want to draw lines
  // c8->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24Jan16/ADM12_LDO_NominalTest_PS_Iout_ave.png");
  c8->SaveAs(TString::Format("%sADM%d_LDO_NominalTest_PS_Iout_ave.png", basePlotPath.Data(), batchNumber));


  TCanvas *c9 = new TCanvas("c9","LPStressTest",2600,1600);
  c9->SetLeftMargin(0.15);
  c9->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg9 = new TMultiGraph();
  TString title9 = Form("ADM#%d LDO Stress test (Vin=%.2fV) in LN2; Total measured time (min); Power Supply Iout (A)", batchNumber, LP_StressV);
  mg9->SetTitle(title9);
  mg9->Add(gr7);
  // mg2->GetYaxis()->SetRangeUser(5.710,5.855);
  mg9->Draw("AP"); // deleta "Ap" if you want to draw lines
  // c9->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24Jan16/AMD12_LDO_StressTest_PS_Iout_ave.png");
  c9->SaveAs(TString::Format("%sADM%d_LDO_StressTest_PS_Iout_ave.png", basePlotPath.Data(), batchNumber));

  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  TCanvas *c10 = new TCanvas("c10","c10",2600,1600);
  c10->SetLeftMargin(0.2);
  c10->SetRightMargin(0.2);
  TPad *pad10_1 = new TPad("pad10_1","",0,0,1,1);
  TPad *pad10_2 = new TPad("pad10_2","",0,0,1,1);
  gPad->Modified();
  gPad->Update();

  pad10_1->Draw();
  pad10_1->cd();
  auto mg10_1 = new TMultiGraph();
  mg10_1->Add(gr4);
  mg10_1->Draw("AP"); // deleta "Ap" if you want to draw lines
  TString title10_1 = Form("LP#%d LDO Nominal test (Vin=%.2fV) during Stress test in LN2; Total measured time (min); LDO Vout (V)", batchNumber, LP_NominalV);
  mg10_1->SetTitle(title10_1);
  mg10_1->GetYaxis()->SetTitleSize(0.025);
  mg10_1->GetYaxis()->SetTitleOffset(1.8);
  mg10_1->GetYaxis()->SetLabelSize(0.025);
  mg10_1->GetYaxis()->SetLabelColor(kRed);
  mg10_1->GetYaxis()->SetTitleColor(kRed);
  // Draw the 2nd TMultiGraph
  pad10_2->SetFrameFillStyle(0);
  pad10_2->SetFillStyle(4000);
  pad10_2->Draw();
  pad10_2->cd();
  auto mg10_2 = new TMultiGraph();
  mg10_2->Add(gr6);
  mg10_2->Draw("AP"); // deleta "Ap" if you want to draw lines

  TAxis *mg10Xaxis = mg10_2->GetHistogram()->GetXaxis();
  TAxis *mg10Yaxis = mg10_2->GetHistogram()->GetYaxis();
  Double_t xmin_10 = mg10Xaxis->GetXmin();
  Double_t xmax_10 = mg10Xaxis->GetXmax();
  Double_t ymin_10 = mg10Yaxis->GetXmin();
  Double_t ymax_10 = mg10Yaxis->GetXmax();
  mg10Yaxis->SetLabelSize(0);
  mg10Yaxis->SetTickLength(0);
  TGaxis *yaxis10 = new TGaxis(xmax_10,ymin_10,xmax_10,ymax_10,ymin_10,ymax_10,510,"+L");
  yaxis10->SetLabelColor(kGreen+2);
  yaxis10->SetLabelSize(0.025);
  yaxis10->SetTitleColor(kGreen+2);
  yaxis10->SetTitleOffset(1.8);
  yaxis10->SetTitleSize(0.025);
  yaxis10->SetTitle("Power Supply I_out (A)");
  yaxis10->Draw();
  // TPaveText *pt10 = new TPaveText(0.25, 0.80, 0.35, 0.90, "NDC"); // coordinates in NDC - ALL
  TPaveText *pt10 = new TPaveText(0.35, 0.80, 0.45, 0.90, "NDC"); // coordinates in NDC - First 500 min
  pt10->AddText(Form("Initial V_out: %.5f", A_LP_ave_n_ini));
  pt10->AddText(Form("Min V_out: %.5f", A_LP_ave_n_min));
  pt10->AddText(Form("Max V_out: %.5f", A_LP_ave_n_max));
  pt10->Draw();

  c10->SaveAs(TString::Format("%sLP%d_LDO_NominalTest_VaI_ave.png", basePlotPath.Data(), batchNumber));
  // c10->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24Jan16/LP12_LDO_NominalTest_VaI_ave.png");
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  TCanvas *c11 = new TCanvas("c11","c11",2600,1600);
  c11->SetLeftMargin(0.2);
  c11->SetRightMargin(0.2);
  TPad *pad11_1 = new TPad("pad11_1","",0,0,1,1);
  TPad *pad11_2 = new TPad("pad11_2","",0,0,1,1);
  gPad->Modified();
  gPad->Update();

  pad11_1->Draw();
  pad11_1->cd();
  auto mg11_1 = new TMultiGraph();
  mg11_1->Add(gr3);
  mg11_1->Draw("AP"); // deleta "Ap" if you want to draw lines
  TString title11_1 = Form("LP#%d LDO Stress test (Vin=%.2fV) in LN2; Total measured time (min); LDO Vout (V)", batchNumber, LP_StressV);
  mg11_1->SetTitle(title11_1);
  mg11_1->GetYaxis()->SetTitleSize(0.025);
  mg11_1->GetYaxis()->SetTitleOffset(1.8);
  mg11_1->GetYaxis()->SetLabelSize(0.025);
  mg11_1->GetYaxis()->SetLabelColor(kRed);
  mg11_1->GetYaxis()->SetTitleColor(kRed);
  // Draw the 2nd TMultiGraph
  pad11_2->SetFrameFillStyle(0);
  pad11_2->SetFillStyle(4000);
  pad11_2->Draw();
  pad11_2->cd();
  auto mg11_2 = new TMultiGraph();
  mg11_2->Add(gr5);
  mg11_2->Draw("AP"); // deleta "Ap" if you want to draw lines

  TAxis *mg11Xaxis = mg11_2->GetHistogram()->GetXaxis();
  TAxis *mg11Yaxis = mg11_2->GetHistogram()->GetYaxis();
  Double_t xmin_11 = mg11Xaxis->GetXmin();
  Double_t xmax_11 = mg11Xaxis->GetXmax();
  Double_t ymin_11 = mg11Yaxis->GetXmin();
  Double_t ymax_11 = mg11Yaxis->GetXmax();
  mg11Yaxis->SetLabelSize(0);
  mg11Yaxis->SetTickLength(0);
  TGaxis *yaxis11 = new TGaxis(xmax_11,ymin_11,xmax_11,ymax_11,ymin_11,ymax_11,510,"+L");
  yaxis11->SetLabelColor(kGreen+2);
  yaxis11->SetLabelSize(0.025);
  yaxis11->SetTitleColor(kGreen+2);
  yaxis11->SetTitleOffset(1.8);
  yaxis11->SetTitleSize(0.025);
  yaxis11->SetTitle("Power Supply I_out (A)");
  yaxis11->Draw();
  // TPaveText *pt11 = new TPaveText(0.25, 0.80, 0.35, 0.90, "NDC"); // coordinates in NDC - ALL
  TPaveText *pt11 = new TPaveText(0.35, 0.80, 0.45, 0.90, "NDC"); // coordinates in NDC - First 500 min
  pt11->AddText(Form("Initial V_out: %.5f", A_LP_ave_s_ini));
  pt11->AddText(Form("Min V_out: %.5f", A_LP_ave_s_min));
  pt11->AddText(Form("Max V_out: %.5f", A_LP_ave_s_max));
  pt11->Draw();

  c11->SaveAs(TString::Format("%sLP%d_LDO_StressTest_VaI_ave.png", basePlotPath.Data(), batchNumber));
  // c11->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24Jan16/LP12_LDO_StressTest_VaI_ave.png");
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  TCanvas *c12 = new TCanvas("c12","c12",2600,1600);
  c12->SetLeftMargin(0.2);
  c12->SetRightMargin(0.2);
  TPad *pad12_1 = new TPad("pad12_1","",0,0,1,1);
  TPad *pad12_2 = new TPad("pad12_2","",0,0,1,1);
  gPad->Modified();
  gPad->Update();

  pad12_1->Draw();
  pad12_1->cd();
  auto mg12_1 = new TMultiGraph();
  mg12_1->Add(gr1);
  mg12_1->Draw("AP"); // deleta "Ap" if you want to draw lines
  TString title12_1 = Form("ADM#%d LDO Stress test (Vin=%.2fV) in LN2; Total measured time (min); LDO Vout (V)", batchNumber, ADM_StressV);
  mg12_1->SetTitle(title12_1);
  mg12_1->GetYaxis()->SetTitleSize(0.025);
  mg12_1->GetYaxis()->SetTitleOffset(1.8);
  mg12_1->GetYaxis()->SetLabelSize(0.025);
  mg12_1->GetYaxis()->SetLabelColor(kBlue);
  mg12_1->GetYaxis()->SetTitleColor(kBlue);
  // Draw the 2nd TMultiGraph
  pad12_2->SetFrameFillStyle(0);
  pad12_2->SetFillStyle(4000);
  pad12_2->Draw();
  pad12_2->cd();
  auto mg12_2 = new TMultiGraph();
  mg12_2->Add(gr7);
  mg12_2->Draw("AP"); // deleta "Ap" if you want to draw lines

  TAxis *mg12Xaxis = mg12_2->GetHistogram()->GetXaxis();
  TAxis *mg12Yaxis = mg12_2->GetHistogram()->GetYaxis();
  Double_t xmin_12 = mg12Xaxis->GetXmin();
  Double_t xmax_12 = mg12Xaxis->GetXmax();
  Double_t ymin_12 = mg12Yaxis->GetXmin();
  Double_t ymax_12 = mg12Yaxis->GetXmax();
  mg12Yaxis->SetLabelSize(0);
  mg12Yaxis->SetTickLength(0);
  TGaxis *yaxis12 = new TGaxis(xmax_12,ymin_12,xmax_12,ymax_12,ymin_12,ymax_12,510,"+L");
  yaxis12->SetLabelColor(kBlack);
  yaxis12->SetLabelSize(0.025);
  yaxis12->SetTitleColor(kBlack);
  yaxis12->SetTitleOffset(1.8);
  yaxis12->SetTitleSize(0.025);
  yaxis12->SetTitle("Power Supply I_out (A)");
  yaxis12->Draw();
  // TPaveText *pt12 = new TPaveText(0.25, 0.80, 0.35, 0.90, "NDC"); // coordinates in NDC - ALL
  TPaveText *pt12 = new TPaveText(0.35, 0.80, 0.45, 0.90, "NDC"); // coordinates in NDC - First 500 min
  pt12->AddText(Form("Initial V_out: %.5f", A_ADM_ave_s_ini));
  pt12->AddText(Form("Min V_out: %.5f", A_ADM_ave_s_min));
  pt12->AddText(Form("Max V_out: %.5f", A_ADM_ave_s_max));
  pt12->Draw();

  c12->SaveAs(TString::Format("%sADM%d_LDO_StressTest_VaI_ave.png", basePlotPath.Data(), batchNumber));
  // c12->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24Jan16/ADM12_LDO_StressTest_VaI_ave.png");
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  TCanvas *c13 = new TCanvas("c13","c13",2600,1600);
  c13->SetLeftMargin(0.2);
  c13->SetRightMargin(0.2);
  TPad *pad13_1 = new TPad("pad13_1","",0,0,1,1);
  TPad *pad13_2 = new TPad("pad13_2","",0,0,1,1);
  gPad->Modified();
  gPad->Update();

  pad13_1->Draw();
  pad13_1->cd();
  auto mg13_1 = new TMultiGraph();
  mg13_1->Add(gr2);
  mg13_1->Draw("AP"); // deleta "Ap" if you want to draw lines
  TString title13_1 = Form("ADM#%d LDO Nominal test (Vin=%.2fV) during Stress test in LN2; Total measured time (min); LDO Vout (V)", batchNumber, ADM_NominalV);
  mg13_1->SetTitle(title13_1);
  mg13_1->GetYaxis()->SetTitleSize(0.025);
  mg13_1->GetYaxis()->SetTitleOffset(1.8);
  mg13_1->GetYaxis()->SetLabelSize(0.025);
  mg13_1->GetYaxis()->SetLabelColor(kBlue);
  mg13_1->GetYaxis()->SetTitleColor(kBlue);
  // Draw the 2nd TMultiGraph
  pad13_2->SetFrameFillStyle(0);
  pad13_2->SetFillStyle(4000);
  pad13_2->Draw();
  pad13_2->cd();
  auto mg13_2 = new TMultiGraph();
  mg13_2->Add(gr8);
  mg13_2->Draw("AP"); // deleta "Ap" if you want to draw lines

  TAxis *mg13Xaxis = mg13_2->GetHistogram()->GetXaxis();
  TAxis *mg13Yaxis = mg13_2->GetHistogram()->GetYaxis();
  Double_t xmin_13 = mg13Xaxis->GetXmin();
  Double_t xmax_13 = mg13Xaxis->GetXmax();
  Double_t ymin_13 = mg13Yaxis->GetXmin();
  Double_t ymax_13 = mg13Yaxis->GetXmax();
  mg13Yaxis->SetLabelSize(0);
  mg13Yaxis->SetTickLength(0);
  TGaxis *yaxis13 = new TGaxis(xmax_13,ymin_13,xmax_13,ymax_13,ymin_13,ymax_13,510,"+L");
  yaxis13->SetLabelColor(kBlack);
  yaxis13->SetLabelSize(0.025);
  yaxis13->SetTitleColor(kBlack);
  yaxis13->SetTitleOffset(1.8);
  yaxis13->SetTitleSize(0.025);
  yaxis13->SetTitle("Power Supply I_out (A)");
  yaxis13->Draw();
  // TPaveText *pt13 = new TPaveText(0.25, 0.80, 0.35, 0.90, "NDC"); // coordinates in NDC - ALL
  TPaveText *pt13 = new TPaveText(0.35, 0.80, 0.45, 0.90, "NDC"); // coordinates in NDC - First 500 min
  pt13->AddText(Form("Initial V_out: %.5f", A_ADM_ave_n_ini));
  pt13->AddText(Form("Min V_out: %.5f", A_ADM_ave_n_min));
  pt13->AddText(Form("Max V_out: %.5f", A_ADM_ave_n_max));
  pt13->Draw();

  c13->SaveAs(TString::Format("%sADM%d_LDO_NominalTest_VaI_ave.png", basePlotPath.Data(), batchNumber));
  // c13->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/24Jan16/ADM12_LDO_NominalTest_VaI_ave.png");
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
}// end DataAnalysis_ave
