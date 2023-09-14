#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

void StitchData()
{
  // Read File1
  fstream dataset1("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Tester1_LP7_Vin7-10_ADM6_Vin7-21_Unstress5min_Stress30min_LN2_Aug9/Tester1_LP7_Vin7-10_ADM6_Vin7-21_Unstress5min_Stress30min_LN2_Aug9.csv",ios::in);
  // Get rid of the 1st line;
  string dummyLine1;
  getline(dataset1, dummyLine1);
  string oneline1;

  // Read File2
  fstream dataset2("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Tester1_LP7_Vin7-10_ADM6_Vin7-21_Unstress5min_Stress30min_LN2_Aug9_continuedafterPCrebootAug17/Tester1_LP7_Vin7-10_ADM6_Vin7-21_Unstress5min_Stress30min_LN2_Aug9_continuedafterPCrebootAug17.csv",ios::in);
  // Get rid of the 1st line;
  string dummyLine2;
  getline(dataset2, dummyLine2);
  string oneline2;

  // // Read File3
  // fstream dataset3("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Tester1_LP5_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July31/Tester1_LP5_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July31.csv",ios::in);
  // // Get rid of the 1st line;
  // string dummyLine3;
  // getline(dataset3, dummyLine3);
  // string oneline3;

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

  while(dataset2)
  {
    getline(dataset2,oneline2);
    TString x = oneline2;
    if(dataset2.eof()) break;
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
  } // end read data from file 2

  // while(dataset3)
  // {
  //   getline(dataset3,oneline3);
  //   TString x = oneline3;
  //   if(dataset3.eof()) break;
  //   TObjArray *tx = x.Tokenize(", ");
  //
  //   for (int i = 0; i < tx->GetEntries(); i++)
  //   {
  //     TString y;//without comma
  //     y = ((TObjString *)(tx->At(i)))->String();
  //     double b = y.Atof();
  //     if ( i == 0) {time_year.emplace_back(b);}
  //     if ( i == 1) {time_hour.emplace_back(b);}
  //     if ( i == 2) {K2470_V.emplace_back(b);}
  //     if ( i == 3) {K2470_I.emplace_back(b);}
  //     if ( i == 4) {K2460_V.emplace_back(b);}
  //     if ( i == 5) {K2460_I.emplace_back(b);}
  //     if ( i == 6) {LP_Vout.emplace_back(b);}
  //     if ( i == 7) {ADM_Vout.emplace_back(b);}
  //   }// end read data loop
  // } // end read data from file 3

  cout << "size: " << time_year.size()<< endl;

  int size = time_hour.size();
  double x[size],A_LP_Vout[size],A_ADM_Vout[size];
  for (int i = 0; i < time_hour.size(); i++)
  {
    A_LP_Vout[i]=LP_Vout.at(i);
    A_ADM_Vout[i]=ADM_Vout.at(i);
    x[i]=i;
  }

  // LP_Vout
  TGraph *gr1  = new TGraph(time_year.size(),x,A_LP_Vout);
  TCanvas *c1 = new TCanvas("c","LP_Vout",2600,1600);
  gr1->SetTitle("LP_Vout_Aug9th-Aug27th;Time;Value");
  // 5.86-5.7 upper; 4.86-4.88 lower
  gr1->GetHistogram()->SetMaximum(4.874);
  gr1->GetHistogram()->SetMinimum(4.864);
  gr1->SetMarkerColor(4);
  gr1->SetMarkerSize(5);
  gr1->Draw("AP"); // deleta "ap" if you want to draw lines
  c1->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/LP_Vout_Aug9Aug27_DownZoom.png");

  // ADM_Vout
  TGraph *gr2  = new TGraph(time_year.size(),x,A_ADM_Vout);
  TCanvas *c2 = new TCanvas("c2","ADM_Vout",2600,1600);
  gr2->SetTitle("ADM_Vout_Aug9th-Aug27th;Time;Value");
  gr2->Draw("AP");
  c2->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/ADM_Vout_Aug9Aug27.png");

}// end StitchData

void StitchData_CombineLP7ADM6()
{
  // Read File1
  fstream dataset1("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Tester1_LP7_Vin7-10_ADM6_Vin7-21_Unstress5min_Stress30min_LN2_Aug9/Tester1_LP7_Vin7-10_ADM6_Vin7-21_Unstress5min_Stress30min_LN2_Aug9.csv",ios::in);
  // Get rid of the 1st line;
  string dummyLine1;
  getline(dataset1, dummyLine1);
  string oneline1;

  // Read File2
  fstream dataset2("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Tester1_LP7_Vin7-10_ADM6_Vin7-21_Unstress5min_Stress30min_LN2_Aug9_continuedafterPCrebootAug17/Tester1_LP7_Vin7-10_ADM6_Vin7-21_Unstress5min_Stress30min_LN2_Aug9_continuedafterPCrebootAug17.csv",ios::in);
  // Get rid of the 1st line;
  string dummyLine2;
  getline(dataset2, dummyLine2);
  string oneline2;

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

  int d1_size,d2_size; // size of dataset1&2
  d1_size = time_year.size();
  cout << "dataset1 size: " << d1_size << endl;

  while(dataset2)
  {
    getline(dataset2,oneline2);
    TString x = oneline2;
    if(dataset2.eof()) break;
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
  } // end read data from file 2

  d2_size = time_year.size() - d1_size;
  cout << "dataset2 size: " << d2_size<< endl;
  cout << "dataset1&2 size: " << time_year.size()<< endl;

  int size = time_year.size();
  double x[size],A_LP_Vout[size],A_ADM_Vout[size];

  // vector for stress and normal
  vector<double> LP_Vout_s,LP_Vout_n,ADM_Vout_s,ADM_Vout_n,t_measure_s,t_measure_n; //s:stress, n:normal
  vector<double> K2460_I_s,K2460_I_n,K2470_I_s,K2470_I_n; //2470: LP, 2460:ADM

  for (int i = 0; i < size; i++)
  {
    A_LP_Vout[i]=LP_Vout.at(i);
    if(K2470_V.at(i)>9)
    {
      LP_Vout_s.emplace_back(LP_Vout.at(i));
      K2470_I_s.emplace_back(K2470_I.at(i));
      t_measure_s.emplace_back(i*10);
    }
    else
    {
      LP_Vout_n.emplace_back(LP_Vout.at(i));
      K2470_I_n.emplace_back(K2470_I.at(i));
      t_measure_n.emplace_back(i*10);
    }

    A_ADM_Vout[i]=ADM_Vout.at(i);
    if(K2460_V.at(i)>9)
    {
      ADM_Vout_s.emplace_back(ADM_Vout.at(i));
      K2460_I_s.emplace_back(K2460_I.at(i));
    }
    else
    {
      ADM_Vout_n.emplace_back(ADM_Vout.at(i));
      K2460_I_n.emplace_back(K2460_I.at(i));
    }

    x[i]=i*10;
    // cout << "nth: " << i << ", K2470_V: " << K2470_V.at(i) << endl;
  }

  // put into array
  int size_s = LP_Vout_s.size();
  int size_n = LP_Vout_n.size();
  // int size_s = 42376; // cut failed region
  // int size_n = 7200;
  double A_LP_Vout_S[size_s], A_LP_Vout_N[size_n];
  double A_K2470_I_S[size_s], A_K2470_I_N[size_n];
  double A_ADM_Vout_S[size_s], A_ADM_Vout_N[size_n];
  double A_K2460_I_S[size_s], A_K2460_I_N[size_n];
  double A_t_measure_S[size_s], A_t_measure_N[size_n];

  cout << "size_s: " << size_s << endl;
  cout << "size_n: " << size_n << endl;

  // stress
  for (int i = 0; i < size_s; i++)
  {
    A_LP_Vout_S[i]=LP_Vout_s.at(i);
    A_K2470_I_S[i]=K2470_I_s.at(i);
    A_ADM_Vout_S[i]=ADM_Vout_s.at(i);
    A_K2460_I_S[i]=K2460_I_s.at(i);
    A_t_measure_S[i]=i*10;
  }
  // normal
  for (int i = 0; i < size_n; i++)
  {
    A_LP_Vout_N[i]=LP_Vout_n.at(i);
    A_K2470_I_N[i]=K2470_I_n.at(i);
    A_ADM_Vout_N[i]=ADM_Vout_n.at(i);
    A_K2460_I_N[i]=K2460_I_n.at(i);
    A_t_measure_N[i]=i*10;
  }

  //
  TGraph *gr1  = new TGraph(size_s,A_t_measure_S,A_LP_Vout_S);
  gr1->SetMarkerColor(kRed);
  gr1->SetMarkerStyle(20);

  TGraph *gr2  = new TGraph(size_n,A_t_measure_N,A_LP_Vout_N);
  gr2->SetMarkerColor(kRed);
  gr2->SetMarkerStyle(21);

  TGraph *gr3  = new TGraph(size_s,A_t_measure_S,A_ADM_Vout_S);
  gr3->SetMarkerColor(kBlue);
  gr3->SetMarkerStyle(20);

  TGraph *gr4  = new TGraph(size_n,A_t_measure_N,A_ADM_Vout_N);
  gr4->SetMarkerColor(kBlue);
  gr4->SetMarkerStyle(21);

  TGraph *gr5  = new TGraph(size_s,A_t_measure_S,A_K2470_I_S);
  gr5->SetMarkerColor(kGreen);
  gr5->SetMarkerStyle(20);

  TGraph *gr6  = new TGraph(size_n,A_t_measure_N,A_K2470_I_N);
  gr6->SetMarkerColor(kGreen);
  gr6->SetMarkerStyle(21);

  TGraph *gr7  = new TGraph(size_s,A_t_measure_S,A_K2460_I_S);
  gr7->SetMarkerColor(kBlack);
  gr7->SetMarkerStyle(20);

  TGraph *gr8  = new TGraph(size_n,A_t_measure_N,A_K2460_I_N);
  gr8->SetMarkerColor(kBlack);
  gr8->SetMarkerStyle(21);



  // Draw TMultiGraph
  // // LDO_StressTest
  // TCanvas *c1 = new TCanvas("c","StessTest",2600,1600);
  // auto mg = new TMultiGraph();
  // mg->SetTitle("LP&ADM LDO stress test in LN2; Total measured stress time (s); LDO Vout (V)");
  // mg->Add(gr1);
  // mg->Add(gr3);
  // // mg->GetYaxis()->SetRangeUser(5.6,6.4);
  // // mg->GetXaxis()->SetRangeUser(0,1800);
  // mg->Draw("AP"); // deleta "Ap" if you want to draw lines
  //
  // TLegend *leg = new TLegend(0.1, 0.4, 0.3, 0.6);
  // leg->AddEntry(gr1, "LP#7, Vstress = 10V", "p");
  // leg->AddEntry(gr3, "ADM#6, Vstress = 21V", "p");
  // leg->Draw();
  //
  // // LDO_NormalTest
  //
  // TCanvas *c2 = new TCanvas("c2","NormalTest",2600,1600);
  // auto mg2 = new TMultiGraph();
  // mg2->SetTitle("LP&ADM LDO normal test in LN2; Total measured stress time (s); LDO Vout (V)");
  // mg2->Add(gr2);
  // mg2->Add(gr4);
  // // mg->GetYaxis()->SetRangeUser(5.6,6.4);
  // // mg->GetXaxis()->SetRangeUser(0,1800);
  // mg2->Draw("AP"); // deleta "Ap" if you want to draw lines
  //
  // TLegend *leg2 = new TLegend(0.1, 0.4, 0.3, 0.6);
  // leg2->AddEntry(gr2, "LP#7, Vnormal = 7V", "p");
  // leg2->AddEntry(gr4, "ADM#6, Vnormal = 7V", "p");
  // leg2->Draw();
  //
  // c1->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/LP&ADM_LDO_StressTest.png");
  // c2->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/LP&ADM_LDO_NormalTest.png");
  //
  //
  // TCanvas *c3 = new TCanvas("c3","LPNormalTest",2600,1600);
  // auto mg3 = new TMultiGraph();
  // mg3->SetTitle("LP#7 LDO normal test (Vin=7V) in LN2; Total measured time (s); LDO Vout (V)");
  // mg3->Add(gr2);
  // mg3->Draw("AP"); // deleta "Ap" if you want to draw lines
  // c3->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/LP7_LDO_NormalTest.png");
  //
  // TCanvas *c4 = new TCanvas("c4","ADMNormalTest",2600,1600);
  // auto mg4 = new TMultiGraph();
  // mg4->SetTitle("ADM#6 LDO normal test (Vin=7V) in LN2; Total measured time (s); LDO Vout (V)");
  // mg4->Add(gr4);
  // mg4->Draw("AP"); // deleta "Ap" if you want to draw lines
  // c4->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/ADM6_LDO_NormalTest.png");
  //
  // TCanvas *c5 = new TCanvas("c3","LPStressTest",2600,1600);
  // auto mg5 = new TMultiGraph();
  // mg5->SetTitle("LP#7 LDO stress test (Vin=10V) in LN2; Total measured time (s); LDO Vout (V)");
  // mg5->Add(gr1);
  // mg5->Draw("AP"); // deleta "Ap" if you want to draw lines
  // c5->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/LP7_LDO_StressTest.png");
  //
  // TCanvas *c6 = new TCanvas("c4","ADMStressTest",2600,1600);
  // auto mg6 = new TMultiGraph();
  // mg6->SetTitle("ADM#6 LDO stress test (Vin=21V) in LN2; Total measured time (s); LDO Vout (V)");
  // mg6->Add(gr3);
  // mg6->Draw("AP"); // deleta "Ap" if you want to draw lines
  // c6->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/ADM6_LDO_StressTest.png");

  // Current
  TCanvas *c6 = new TCanvas("c6","LPNormalTest",2600,1600);
  c6->SetLeftMargin(0.15);
  c6->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg6 = new TMultiGraph();
  mg6->SetTitle("LP#7 LDO normal test (Vin=7V) in LN2; Total measured stress time (s); Power Supply Iout (A)");
  mg6->Add(gr6);
  mg6->Draw("AP"); // deleta "Ap" if you want to draw lines
  c6->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/LP7_LDO_NormalTest_PS_Iout.png");

  TCanvas *c7 = new TCanvas("c7","LPStressTest",2600,1600);
  c7->SetLeftMargin(0.15);
  c7->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg7 = new TMultiGraph();
  mg7->SetTitle("LP#7 LDO stress test (Vin=10V) in LN2; Total measured stress time (s); Power Supply Iout (A)");
  mg7->Add(gr5);
  mg7->Draw("AP"); // deleta "Ap" if you want to draw lines
  c7->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/LP7_LDO_StressTest_PS_Iout.png");

  TCanvas *c8 = new TCanvas("c8","ADMNormalTest",2600,1600);
  c8->SetLeftMargin(0.15);
  c8->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg8 = new TMultiGraph();
  mg8->SetTitle("ADM#6 LDO normal test (Vin=7V) in LN2; Total measured stress time (s); Power Supply Iout (A)");
  mg8->Add(gr8);
  mg8->Draw("AP"); // deleta "Ap" if you want to draw lines
  c8->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/ADM6_LDO_NormalTest_PS_Iout.png");

  TCanvas *c9 = new TCanvas("c9","ADMStressTest",2600,1600);
  c9->SetLeftMargin(0.15);
  c9->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg9 = new TMultiGraph();
  mg9->SetTitle("ADM#6 LDO stress test (Vin=21V) in LN2; Total measured stress time (s); Power Supply Iout (A)");
  mg9->Add(gr7);
  mg9->Draw("AP"); // deleta "Ap" if you want to draw lines
  c9->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/ADM6_LDO_StressTest_PS_Iout.png");

}// end StitchData_CombineLP7ADM6

void StitchData_CombineLP3ADM5()
{
  // Read File1
  fstream dataset1("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Tester1_LP3_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July20/Tester1_LP3_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July20.csv",ios::in);
  // Get rid of the 1st line;
  string dummyLine1;
  getline(dataset1, dummyLine1);
  string oneline1;

  // Read File2
  fstream dataset2("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Tester1_LP3_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July20_continued/Tester1_LP3_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July20_continued.csv",ios::in);
  // Get rid of the 1st line;
  string dummyLine2;
  getline(dataset2, dummyLine2);
  string oneline2;

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

  int d1_size,d2_size; // size of dataset1&2
  d1_size = time_year.size();
  cout << "dataset1 size: " << d1_size << endl;

  while(dataset2)
  {
    getline(dataset2,oneline2);
    TString x = oneline2;
    if(dataset2.eof()) break;
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
  } // end read data from file 2

  d2_size = time_year.size() - d1_size;
  cout << "dataset2 size: " << d2_size<< endl;
  cout << "dataset1&2 size: " << time_year.size()<< endl;

  int size = time_year.size();
  double x[size],A_LP_Vout[size],A_ADM_Vout[size];


  // vector for stress and normal
  vector<double> LP_Vout_s,LP_Vout_n,ADM_Vout_s,ADM_Vout_n,t_measure_s,t_measure_n; //s:stress, n:normal
  vector<double> K2460_I_s,K2460_I_n,K2470_I_s,K2470_I_n; //2470: LP, 2460:ADM

  for (int i = 0; i < size; i++)
  {
    A_LP_Vout[i]=LP_Vout.at(i);
    if(K2470_V.at(i)>9)
    {
      LP_Vout_s.emplace_back(LP_Vout.at(i));
      K2470_I_s.emplace_back(K2470_I.at(i));
      t_measure_s.emplace_back(i*10);
    }
    else
    {
      LP_Vout_n.emplace_back(LP_Vout.at(i));
      K2470_I_n.emplace_back(K2470_I.at(i));
      t_measure_n.emplace_back(i*10);
    }

    A_ADM_Vout[i]=ADM_Vout.at(i);
    if(K2460_V.at(i)>9)
    {
      ADM_Vout_s.emplace_back(ADM_Vout.at(i));
      K2460_I_s.emplace_back(K2460_I.at(i));
    }
    else
    {
      ADM_Vout_n.emplace_back(ADM_Vout.at(i));
      K2460_I_n.emplace_back(K2460_I.at(i));
    }

    x[i]=i*10;
    // cout << "nth: " << i << ", K2470_V: " << K2470_V.at(i) << endl;
  }


  // put into array
  int size_s = LP_Vout_s.size();
  int size_n = LP_Vout_n.size();
  // int size_s = 42376; // cut failed region
  // int size_n = 7200;
  double A_LP_Vout_S[size_s], A_LP_Vout_N[size_n];
  double A_K2470_I_S[size_s], A_K2470_I_N[size_n];
  double A_ADM_Vout_S[size_s], A_ADM_Vout_N[size_n];
  double A_K2460_I_S[size_s], A_K2460_I_N[size_n];
  double A_t_measure_S[size_s], A_t_measure_N[size_n];

  cout << "size_s: " << size_s << endl;
  cout << "size_n: " << size_n << endl;

  // stress
  for (int i = 0; i < size_s; i++)
  {
    A_LP_Vout_S[i]=LP_Vout_s.at(i);
    A_K2470_I_S[i]=K2470_I_s.at(i);
    A_ADM_Vout_S[i]=ADM_Vout_s.at(i);
    A_K2460_I_S[i]=K2460_I_s.at(i);
    A_t_measure_S[i]=i*10;
  }
  // normal
  for (int i = 0; i < size_n; i++)
  {
    A_LP_Vout_N[i]=LP_Vout_n.at(i);
    A_K2470_I_N[i]=K2470_I_n.at(i);
    A_ADM_Vout_N[i]=ADM_Vout_n.at(i);
    A_K2460_I_N[i]=K2460_I_n.at(i);
    A_t_measure_N[i]=i*10;
  }

  //
  TGraph *gr1  = new TGraph(size_s,A_t_measure_S,A_LP_Vout_S);
  gr1->SetMarkerColor(kRed);
  gr1->SetMarkerStyle(20);

  TGraph *gr2  = new TGraph(size_n,A_t_measure_N,A_LP_Vout_N);
  gr2->SetMarkerColor(kRed);
  gr2->SetMarkerStyle(21);

  TGraph *gr3  = new TGraph(size_s,A_t_measure_S,A_ADM_Vout_S);
  gr3->SetMarkerColor(kBlue);
  gr3->SetMarkerStyle(20);

  TGraph *gr4  = new TGraph(size_n,A_t_measure_N,A_ADM_Vout_N);
  gr4->SetMarkerColor(kBlue);
  gr4->SetMarkerStyle(21);

  TGraph *gr5  = new TGraph(size_s,A_t_measure_S,A_K2470_I_S);
  gr5->SetMarkerColor(kGreen);
  gr5->SetMarkerStyle(20);

  TGraph *gr6  = new TGraph(size_n,A_t_measure_N,A_K2470_I_N);
  gr6->SetMarkerColor(kGreen);
  gr6->SetMarkerStyle(21);

  TGraph *gr7  = new TGraph(size_s,A_t_measure_S,A_K2460_I_S);
  gr7->SetMarkerColor(kBlack);
  gr7->SetMarkerStyle(20);

  TGraph *gr8  = new TGraph(size_n,A_t_measure_N,A_K2460_I_N);
  gr8->SetMarkerColor(kBlack);
  gr8->SetMarkerStyle(21);

  // Draw TMultiGraph

  // // Vout
  // TCanvas *c3 = new TCanvas("c3","LPNormalTest",2600,1600);
  // c3->SetLeftMargin(0.1);
  // c3->SetRightMargin(0.1);
  // gPad->Modified();
  // gPad->Update();
  // auto mg3 = new TMultiGraph();
  // mg3->SetTitle("LP#3 LDO normal test (Vin=7V) in LN2; Total measured stress time (s); LDO Vout (V)");
  // mg3->Add(gr2);
  // mg3->Draw("AP"); // deleta "Ap" if you want to draw lines
  // c3->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/LP3_LDO_NormalTest_nF.png");
  //
  // TCanvas *c5 = new TCanvas("c5","LPStressTest",2600,1600);
  // c5->SetLeftMargin(0.1);
  // c5->SetRightMargin(0.1);
  // gPad->Modified();
  // gPad->Update();
  // auto mg5 = new TMultiGraph();
  // mg5->SetTitle("LP#3 LDO stress test (Vin=11V) in LN2; Total measured stress time (s); LDO Vout (V)");
  // mg5->Add(gr1);
  // mg5->Draw("AP"); // deleta "Ap" if you want to draw lines
  // c5->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/LP3_LDO_StressTest_nF.png");

  // Current
  TCanvas *c6 = new TCanvas("c6","LPNormalTest",2600,1600);
  c6->SetLeftMargin(0.15);
  c6->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg6 = new TMultiGraph();
  mg6->SetTitle("LP#3 LDO normal test (Vin=7V) in LN2; Total measured stress time (s); Power Supply Iout (A)");
  mg6->Add(gr6);
  mg6->Draw("AP"); // deleta "Ap" if you want to draw lines
  c6->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/LP3_LDO_NormalTest_PS_Iout.png");

  TCanvas *c7 = new TCanvas("c7","LPStressTest",2600,1600);
  c7->SetLeftMargin(0.15);
  c7->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg7 = new TMultiGraph();
  mg7->SetTitle("LP#3 LDO stress test (Vin=11V) in LN2; Total measured stress time (s); Power Supply Iout (A)");
  mg7->Add(gr5);
  mg7->Draw("AP"); // deleta "Ap" if you want to draw lines
  c7->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/LP3_LDO_StressTest_PS_Iout.png");

  TCanvas *c8 = new TCanvas("c8","ADMNormalTest",2600,1600);
  c8->SetLeftMargin(0.15);
  c8->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg8 = new TMultiGraph();
  mg8->SetTitle("ADM#5 LDO normal test (Vin=7V) in LN2; Total measured stress time (s); Power Supply Iout (A)");
  mg8->Add(gr8);
  mg8->Draw("AP"); // deleta "Ap" if you want to draw lines
  c8->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/ADM5_LDO_NormalTest_PS_Iout.png");

  TCanvas *c9 = new TCanvas("c9","ADMStressTest",2600,1600);
  c9->SetLeftMargin(0.15);
  c9->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg9 = new TMultiGraph();
  mg9->SetTitle("ADM#5 LDO stress test (Vin=21V) in LN2; Total measured stress time (s); Power Supply Iout (A)");
  mg9->Add(gr7);
  mg9->Draw("AP"); // deleta "Ap" if you want to draw lines
  c9->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/ADM5_LDO_StressTest_PS_Iout.png");

}// end StitchData_CombineLP3ADM5

void StitchData_CombineLP5ADM5()
{
  // Read File1
  fstream dataset1("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Tester1_LP5_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July31/Tester1_LP5_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July31.csv",ios::in);
  // Get rid of the 1st line;
  string dummyLine1;
  getline(dataset1, dummyLine1);
  string oneline1;

  // Read File2
  fstream dataset2("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Tester1_LP5_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July31_RestartAug6MemoryExplode/Tester1_LP5_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July31_RestartAug6MemoryExplode.csv",ios::in);
  // Get rid of the 1st line;
  string dummyLine2;
  getline(dataset2, dummyLine2);
  string oneline2;

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

  int d1_size,d2_size; // size of dataset1&2
  d1_size = time_year.size();
  cout << "dataset1 size: " << d1_size << endl;

  while(dataset2)
  {
    getline(dataset2,oneline2);
    TString x = oneline2;
    if(dataset2.eof()) break;
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
  } // end read data from file 2

  d2_size = time_year.size() - d1_size;
  cout << "dataset2 size: " << d2_size<< endl;
  cout << "dataset1&2 size: " << time_year.size()<< endl;

  int size = time_year.size();
  double x[size],A_LP_Vout[size],A_ADM_Vout[size];


  // vector for stress and normal
  vector<double> LP_Vout_s,LP_Vout_n,ADM_Vout_s,ADM_Vout_n,t_measure_s,t_measure_n; //s:stress, n:normal
  vector<double> K2460_I_s,K2460_I_n,K2470_I_s,K2470_I_n; //2470: LP, 2460:ADM

  for (int i = 0; i < size; i++)
  {
    A_LP_Vout[i]=LP_Vout.at(i);
    if(K2470_V.at(i)>9)
    {
      LP_Vout_s.emplace_back(LP_Vout.at(i));
      K2470_I_s.emplace_back(K2470_I.at(i));
      t_measure_s.emplace_back(i*10);
    }
    else
    {
      LP_Vout_n.emplace_back(LP_Vout.at(i));
      K2470_I_n.emplace_back(K2470_I.at(i));
      t_measure_n.emplace_back(i*10);
    }

    A_ADM_Vout[i]=ADM_Vout.at(i);
    if(K2460_V.at(i)>9)
    {
      ADM_Vout_s.emplace_back(ADM_Vout.at(i));
      K2460_I_s.emplace_back(K2460_I.at(i));
    }
    else
    {
      ADM_Vout_n.emplace_back(ADM_Vout.at(i));
      K2460_I_n.emplace_back(K2460_I.at(i));
    }

    x[i]=i*10;
    // cout << "nth: " << i << ", K2470_V: " << K2470_V.at(i) << endl;
  }


  // put into array
  int size_s = LP_Vout_s.size();
  int size_n = LP_Vout_n.size();
  // int size_s = 41528;   //cut failed region
  // int size_n = 6500;
  double A_LP_Vout_S[size_s], A_LP_Vout_N[size_n];
  double A_K2470_I_S[size_s], A_K2470_I_N[size_n];
  double A_ADM_Vout_S[size_s], A_ADM_Vout_N[size_n];
  double A_K2460_I_S[size_s], A_K2460_I_N[size_n];
  double A_t_measure_S[size_s], A_t_measure_N[size_n];

  cout << "size_s: " << size_s << endl;
  cout << "size_n: " << size_n << endl;

  // stress
  for (int i = 0; i < size_s; i++)
  {
    A_LP_Vout_S[i]=LP_Vout_s.at(i);
    A_K2470_I_S[i]=K2470_I_s.at(i);
    A_ADM_Vout_S[i]=ADM_Vout_s.at(i);
    A_K2460_I_S[i]=K2460_I_s.at(i);
    A_t_measure_S[i]=i*10;
  }
  // normal
  for (int i = 0; i < size_n; i++)
  {
    A_LP_Vout_N[i]=LP_Vout_n.at(i);
    A_K2470_I_N[i]=K2470_I_n.at(i);
    A_ADM_Vout_N[i]=ADM_Vout_n.at(i);
    A_K2460_I_N[i]=K2460_I_n.at(i);
    A_t_measure_N[i]=i*10;
  }

  //
  TGraph *gr1  = new TGraph(size_s,A_t_measure_S,A_LP_Vout_S);
  gr1->SetMarkerColor(kRed);
  gr1->SetMarkerStyle(20);

  TGraph *gr2  = new TGraph(size_n,A_t_measure_N,A_LP_Vout_N);
  gr2->SetMarkerColor(kRed);
  gr2->SetMarkerStyle(21);

  TGraph *gr3  = new TGraph(size_s,A_t_measure_S,A_ADM_Vout_S);
  gr3->SetMarkerColor(kBlue);
  gr3->SetMarkerStyle(20);

  TGraph *gr4  = new TGraph(size_n,A_t_measure_N,A_ADM_Vout_N);
  gr4->SetMarkerColor(kBlue);
  gr4->SetMarkerStyle(21);

  TGraph *gr5  = new TGraph(size_s,A_t_measure_S,A_K2470_I_S);
  gr5->SetMarkerColor(kGreen);
  gr5->SetMarkerStyle(20);

  TGraph *gr6  = new TGraph(size_n,A_t_measure_N,A_K2470_I_N);
  gr6->SetMarkerColor(kGreen);
  gr6->SetMarkerStyle(21);

  TGraph *gr7  = new TGraph(size_s,A_t_measure_S,A_K2460_I_S);
  gr7->SetMarkerColor(kBlack);
  gr7->SetMarkerStyle(20);

  TGraph *gr8  = new TGraph(size_n,A_t_measure_N,A_K2460_I_N);
  gr8->SetMarkerColor(kBlack);
  gr8->SetMarkerStyle(21);



  // Draw TMultiGraph


  // TCanvas *c3 = new TCanvas("c3","LPNormalTest",2600,1600);
  // auto mg3 = new TMultiGraph();
  // c3->SetLeftMargin(0.15);
  // c3->SetRightMargin(0.15);
  // gPad->Modified();
  // gPad->Update();
  // mg3->SetTitle("LP#5 LDO normal test (Vin=7V) in LN2; Total measured stress time (s); LDO Vout (V)");
  // mg3->Add(gr2);
  // mg3->Draw("AP"); // deleta "Ap" if you want to draw lines
  // c3->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/LP5_LDO_NormalTest_nF.png");
  //
  // TCanvas *c5 = new TCanvas("c5","LPStressTest",2600,1600);
  // c5->SetLeftMargin(0.15);
  // c5->SetRightMargin(0.15);
  // gPad->Modified();
  // gPad->Update();
  // auto mg5 = new TMultiGraph();
  // mg5->SetTitle("LP#5 LDO stress test (Vin=11V) in LN2; Total measured stress time (s); LDO Vout (V)");
  // mg5->Add(gr1);
  // mg5->Draw("AP"); // deleta "Ap" if you want to draw lines
  //
  // c5->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/LP5_LDO_StressTest_nF.png");

  // Current
  TCanvas *c6 = new TCanvas("c6","LPNormalTest",2600,1600);
  c6->SetLeftMargin(0.15);
  c6->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg6 = new TMultiGraph();
  mg6->SetTitle("LP#5 LDO normal test (Vin=7V) in LN2; Total measured stress time (s); Power Supply Iout (A)");
  mg6->Add(gr6);
  mg6->Draw("AP"); // deleta "Ap" if you want to draw lines
  c6->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/LP5_LDO_NormalTest_PS_Iout.png");

  TCanvas *c7 = new TCanvas("c7","LPStressTest",2600,1600);
  c7->SetLeftMargin(0.15);
  c7->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg7 = new TMultiGraph();
  mg7->SetTitle("LP#5 LDO stress test (Vin=11V) in LN2; Total measured stress time (s); Power Supply Iout (A)");
  mg7->Add(gr5);
  mg7->Draw("AP"); // deleta "Ap" if you want to draw lines
  c7->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/LP5_LDO_StressTest_PS_Iout.png");

  TCanvas *c8 = new TCanvas("c8","ADMNormalTest",2600,1600);
  c8->SetLeftMargin(0.15);
  c8->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg8 = new TMultiGraph();
  mg8->SetTitle("ADM#5 LDO normal test (Vin=7V) in LN2; Total measured stress time (s); Power Supply Iout (A)");
  mg8->Add(gr8);
  mg8->Draw("AP"); // deleta "Ap" if you want to draw lines
  c8->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/ADM5_LDO_NormalTest_PS_Iout.png");

  TCanvas *c9 = new TCanvas("c9","ADMStressTest",2600,1600);
  c9->SetLeftMargin(0.15);
  c9->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg9 = new TMultiGraph();
  mg9->SetTitle("ADM#5 LDO stress test (Vin=21V) in LN2; Total measured stress time (s); Power Supply Iout (A)");
  mg9->Add(gr7);
  mg9->Draw("AP"); // deleta "Ap" if you want to draw lines
  c9->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/ADM5_LDO_StressTest_PS_Iout.png");

}// end StitchData_CombineLP5ADM5

void StitchData_Initial()
{
  // Read File1
  fstream dataset1("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Tester1_LP3_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July20/Tester1_LP3_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July20.csv",ios::in);
  // Get rid of the 1st line;
  string dummyLine1;
  getline(dataset1, dummyLine1);
  string oneline1;

  // Read File2
  fstream dataset2("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Tester1_LP5_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July31/Tester1_LP5_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July31.csv",ios::in);
  // Get rid of the 1st line;
  string dummyLine2;
  getline(dataset2, dummyLine2);
  string oneline2;

  // Read File3
  fstream dataset3("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Tester1_LP7_Vin7-10_ADM6_Vin7-21_Unstress5min_Stress30min_LN2_Aug9/Tester1_LP7_Vin7-10_ADM6_Vin7-21_Unstress5min_Stress30min_LN2_Aug9.csv",ios::in);
  // Get rid of the 1st line;
  string dummyLine3;
  getline(dataset3, dummyLine3);
  string oneline3;

  // Make vectors
  vector<double> time_year,time_hour,K2470_V,K2470_I,K2460_V,K2460_I,LP_Vout,ADM_Vout;
  vector<double> LP_Vout_s,LP_Vout_n,ADM_Vout_s,ADM_Vout_n; //s:stress, n:normal
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

  //choose stress data
  for (int i = 0; i < time_hour.size(); i++)
  {
    if(K2470_V.at(i)>9) LP_Vout_s.emplace_back(LP_Vout.at(i));// stress voltage
    if(K2460_V.at(i)>9) ADM_Vout_s.emplace_back(ADM_Vout.at(i));
  }
  // Read firt 180*10 data set for LP
  int size3 = time_hour.size();
  double x_LP3[size3],Vout_LP3[size3],Vout_ADM5_1[size3];
  for (int i = 0; i < 180; i++)
  {
    Vout_LP3[i]=LP_Vout_s.at(i);
    Vout_ADM5_1[i]=ADM_Vout_s.at(i);
    x_LP3[i]=i*10;
  }


  //----------------------------------------------------------------------------
  //****************************************************************************
  //----------------------------------------------------------------------------


  // Clear up vectors before reading the next dataset
  time_year.clear();
  time_hour.clear();
  K2470_V.clear();
  K2470_I.clear();
  K2460_V.clear();
  K2460_I.clear();
  LP_Vout.clear();
  ADM_Vout.clear();
  LP_Vout_s.clear();
  ADM_Vout_s.clear();


  while(dataset2)
  {
    getline(dataset2,oneline2);
    TString x = oneline2;
    if(dataset2.eof()) break;
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
  } // end read data from file 2


  //choose stress data
  for (int i = 0; i < time_hour.size(); i++)
  {
    if(K2470_V.at(i)>9) LP_Vout_s.emplace_back(LP_Vout.at(i));// stress voltage
    if(K2460_V.at(i)>9) ADM_Vout_s.emplace_back(ADM_Vout.at(i));
  }
  // Read firt 180*10 data set for LP
  int size5 = time_hour.size();
  double x_LP5[size5],Vout_LP5[size5],Vout_ADM5_2[size5];
  for (int i = 0; i < 180; i++)
  {
    Vout_LP5[i]=LP_Vout_s.at(i);
    Vout_ADM5_2[i]=ADM_Vout_s.at(i);
    x_LP5[i]=i*10;
  }
  //----------------------------------------------------------------------------
  //****************************************************************************
  //----------------------------------------------------------------------------


  // Clear up vectors before reading the next dataset
  time_year.clear();
  time_hour.clear();
  K2470_V.clear();
  K2470_I.clear();
  K2460_V.clear();
  K2460_I.clear();
  LP_Vout.clear();
  ADM_Vout.clear();
  LP_Vout_s.clear();
  ADM_Vout_s.clear();

  while(dataset3)
  {
    getline(dataset3,oneline3);
    TString x = oneline3;
    if(dataset3.eof()) break;
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
  } // end read data from file 3

  //choose stress data
  for (int i = 0; i < time_hour.size(); i++)
  {
    if(K2470_V.at(i)>9) LP_Vout_s.emplace_back(LP_Vout.at(i));// stress voltage
    if(K2460_V.at(i)>9) ADM_Vout_s.emplace_back(ADM_Vout.at(i));
  }
  // Read firt 180*10 data set for LP
  int size7 = time_hour.size();
  double x_LP7[size7],Vout_LP7[size7],Vout_ADM6[size7];
  for (int i = 0; i < 180; i++)
  {
    Vout_LP7[i]=LP_Vout_s.at(i);
    Vout_ADM6[i]=ADM_Vout_s.at(i);
    x_LP7[i]=i*10;
  }



  // LP_Vout
  TGraph *gr1  = new TGraph(180,x_LP3,Vout_LP3);
  gr1->SetMarkerColor(kRed);
  gr1->SetMarkerStyle(20);
  // gr1->SetMarkerSize(200);
  // gr1->SetTitle("LP#3");
  TGraph *gr2  = new TGraph(180,x_LP5,Vout_LP5);
  gr2->SetMarkerColor(kBlue);
  gr2->SetMarkerStyle(20);
  TGraph *gr3  = new TGraph(180,x_LP7,Vout_LP7);
  gr3->SetMarkerColor(kGreen);
  gr3->SetMarkerStyle(20);

  // LP_Vout
  TGraph *gr4  = new TGraph(180,x_LP3,Vout_ADM5_1);
  gr4->SetMarkerColor(kRed);
  gr4->SetMarkerStyle(20);
  TGraph *gr5  = new TGraph(180,x_LP5,Vout_ADM5_2);
  gr5->SetMarkerColor(kBlue);
  gr5->SetMarkerStyle(20);
  TGraph *gr6  = new TGraph(180,x_LP7,Vout_ADM6);
  gr6->SetMarkerColor(kGreen);
  gr6->SetMarkerStyle(20);

  // Draw TMultiGraph
  TCanvas *c1 = new TCanvas("c","LP_Vout",2600,1600);
  auto mg = new TMultiGraph();
  mg->SetTitle("LP LDO stress test in LN2; Total stress time (s); LDO Vout (V)");
  mg->Add(gr1);
  mg->Add(gr2);
  mg->Add(gr3);
  mg->GetYaxis()->SetRangeUser(5.6,6.4);
  mg->GetXaxis()->SetRangeUser(0,1800);
  mg->Draw("AP"); // deleta "Ap" if you want to draw lines

  TLegend *leg = new TLegend(0.1, 0.4, 0.3, 0.6);
  // leg->SetFillColor(0);
  leg->AddEntry(gr1, "LP#3, Vstress = 11V", "p");
  leg->AddEntry(gr2, "LP#5, Vstress = 11V", "p");
  leg->AddEntry(gr3, "LP#7, Vstress = 10V", "p");
  leg->Draw();

  gPad->Modified();
  gPad->Update();

  c1->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/LP_Vout_InitialTime.png");
  //
  //
  //---------------------------------
  // ADM6
  //---------------------------------
  TCanvas *c2 = new TCanvas("c2","ADM_Vout",2600,1600);
  auto mg2 = new TMultiGraph();
  mg2->SetTitle("ADM LDO stress test in LN2; Total stress time (s); LDO Vout (V)");
  mg2->Add(gr4);
  mg2->Add(gr5);
  mg2->Add(gr6);
  // mg2->GetYaxis()->SetRangeUser(5.6,6.4);
  mg2->GetXaxis()->SetRangeUser(0,1800);
  mg2->Draw("AP"); // deleta "Ap" if you want to draw lines

  TLegend *leg2 = new TLegend(0.7, 0.1, 0.9, 0.3);
  // leg->SetFillColor(0);
  leg2->AddEntry(gr4, "ADM#5_1st, Vstress = 21V", "p");
  leg2->AddEntry(gr5, "ADM#5_2nd, Vstress = 21V", "p");
  leg2->AddEntry(gr6, "ADM#6, Vstress = 21V", "p");
  leg2->Draw();

  gPad->Modified();
  gPad->Update();

  c2->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/ADM_Vout_InitialTime.png");

}// end StitchData_Initial

void ReadData()
{
  fstream dataset1("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Tester1_July20_both/Tester1_LP3_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July20_continued/Tester1_LP3_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July20_continued.csv",ios::in);
  // Get rid of the 1st line;
  string dummyLine1;
  getline(dataset1, dummyLine1);

  string oneline1;
  vector<double> time_year1,time_hour1,K2470_V1,K2470_I1,K2460_V1,K2460_I1,LP_Vout1,ADM_Vout1;

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
      if ( i == 0) {time_year1.emplace_back(b);}
      if ( i == 1) {time_hour1.emplace_back(b);}
      if ( i == 2) {K2470_V1.emplace_back(b);}
      if ( i == 3) {K2470_I1.emplace_back(b);}
      if ( i == 4) {K2460_V1.emplace_back(b);}
      if ( i == 5) {K2460_I1.emplace_back(b);}
      if ( i == 6) {LP_Vout1.emplace_back(b);}
      if ( i == 7) {ADM_Vout1.emplace_back(b);}
    }// end read data loop
  }

  // Check if data is read correctly
  cout << "size: " << time_year1.size()<< endl;
  for(int i=0;i<3;i++)
	{
    cout << "i: " << i << "\n";
		cout << "time_year1: " << time_year1.at(i) << "\n";
    cout << "time_hour1: " << time_hour1.at(i) << "\n";
    cout << "K2470_V1: " << LP_Vout1.at(i) << "\n";
    cout << "K2470_I1: " << ADM_Vout1.at(i) << "\n\n";
	}

}// end ReadData

void StitchData_LP7ADM6_ave()
{
  // Read File1
  fstream dataset1("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Tester1_LP7_Vin7-10_ADM6_Vin7-21_Unstress5min_Stress30min_LN2_Aug9/Tester1_LP7_Vin7-10_ADM6_Vin7-21_Unstress5min_Stress30min_LN2_Aug9.csv",ios::in);
  // Get rid of the 1st line;
  string dummyLine1;
  getline(dataset1, dummyLine1);
  string oneline1;

  // Read File2
  fstream dataset2("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Tester1_LP7_Vin7-10_ADM6_Vin7-21_Unstress5min_Stress30min_LN2_Aug9_continuedafterPCrebootAug17/Tester1_LP7_Vin7-10_ADM6_Vin7-21_Unstress5min_Stress30min_LN2_Aug9_continuedafterPCrebootAug17.csv",ios::in);
  // Get rid of the 1st line;
  string dummyLine2;
  getline(dataset2, dummyLine2);
  string oneline2;

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

  int d1_size,d2_size; // size of dataset1&2
  d1_size = time_year.size();
  cout << "dataset1 size: " << d1_size << endl;

  while(dataset2)
  {
    getline(dataset2,oneline2);
    TString x = oneline2;
    if(dataset2.eof()) break;
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
  } // end read data from file 2

  d2_size = time_year.size() - d1_size;
  cout << "dataset2 size: " << d2_size<< endl;
  cout << "dataset1&2 size: " << time_year.size()<< endl;

  // Find avarage_stress


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
    // stress
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


      cout << "stress_i: " << i << endl;

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
    // normal
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


      cout << "normal_i: " << i << endl;

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
  for (int i = 0; i < size_s; i++)
  {
    // cout<< "ADM_stress_ave_i: " << ADM_ave_s.at(i) << endl;
    // cout<< "LP_stress_ave_i: " << LP_ave_s.at(i) << endl;
    cout<< "K2470_ave_i: " << K2470_ave_s.at(i) << endl;
    cout<< "K2460_ave_i: " << K2460_ave_s.at(i) << endl;
  }

  cout << "ADM_ave_n size: " << size_n << endl;
  for (int i = 0; i < size_n; i++)
  {
    // cout<< "ADM_normal_ave_i: " << ADM_ave_n.at(i) << endl;
    // cout<< "LP_normal_ave_i: " << LP_ave_n.at(i) << endl;
    cout<< "K2470_ave_i: " << K2470_ave_n.at(i) << endl;
    cout<< "K2460_ave_i: " << K2460_ave_n.at(i) << endl;
  }

  double A_ADM_ave_s[size_s], A_ADM_ave_n[size_n];
  double A_LP_ave_s[size_s], A_LP_ave_n[size_n];
  double A_K2460_ave_s[size_s], A_K2460_ave_n[size_n];
  double A_K2470_ave_s[size_s], A_K2470_ave_n[size_n];
  double A_t_measure_S[size_s], A_t_measure_N[size_n];

  // stress
  for (int i = 0; i < size_s; i++)
  {
    A_ADM_ave_s[i]=ADM_ave_s.at(i);
    A_LP_ave_s[i]=LP_ave_s.at(i);
    A_K2460_ave_s[i]=K2460_ave_s.at(i);
    A_K2470_ave_s[i]=K2470_ave_s.at(i);
    A_t_measure_S[i]=(i+1)*30;
  }
  // normal
  for (int i = 0; i < size_n; i++)
  {
    A_ADM_ave_n[i]=ADM_ave_n.at(i);
    A_LP_ave_n[i]=LP_ave_n.at(i);
    A_K2460_ave_n[i]=K2460_ave_n.at(i);
    A_K2470_ave_n[i]=K2470_ave_n.at(i);
    A_t_measure_N[i]=(i+1)*5;
  }

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

  TGraph *gr5  = new TGraph(size_s,A_t_measure_S,A_K2470_ave_s);
  gr5->SetMarkerColor(kGreen);
  gr5->SetMarkerStyle(20);

  TGraph *gr6  = new TGraph(size_n,A_t_measure_N,A_K2470_ave_n);
  gr6->SetMarkerColor(kGreen);
  gr6->SetMarkerStyle(21);

  TGraph *gr7  = new TGraph(size_s,A_t_measure_S,A_K2460_ave_s);
  gr7->SetMarkerColor(kBlack);
  gr7->SetMarkerStyle(20);

  TGraph *gr8  = new TGraph(size_n,A_t_measure_N,A_K2460_ave_n);
  gr8->SetMarkerColor(kBlack);
  gr8->SetMarkerStyle(21);

  // TCanvas *c1 = new TCanvas("c1","LPNormalTest",2600,1600);
  // c1->SetLeftMargin(0.15);
  // c1->SetRightMargin(0.1);
  // gPad->Modified();
  // gPad->Update();
  // auto mg1 = new TMultiGraph();
  // mg1->SetTitle("LP#7 LDO normal test (Vin=7V) in LN2; Total measured time (min); LDO Vout (V)");
  // mg1->Add(gr4);
  // mg1->Draw("AP"); // deleta "Ap" if you want to draw lines
  // c1->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/LP7_LDO_NormalTest_ave.png");
  //
  // TCanvas *c2 = new TCanvas("c2","LPStressTest",2600,1600);
  // c2->SetLeftMargin(0.15);
  // c2->SetRightMargin(0.1);
  // gPad->Modified();
  // gPad->Update();
  // auto mg2 = new TMultiGraph();
  // mg2->SetTitle("LP#7 LDO stress test (Vin=10V) in LN2; Total measured time (min); LDO Vout (V)");
  // mg2->Add(gr3);
  // mg2->GetYaxis()->SetRangeUser(5.710,5.855);
  // mg2->Draw("AP"); // deleta "Ap" if you want to draw lines
  // c2->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/LP7_LDO_StressTest_ave_scale.png");
  //
  // TCanvas *c3 = new TCanvas("c3","ADMNormalTest",2600,1600);
  // c3->SetLeftMargin(0.15);
  // c3->SetRightMargin(0.1);
  // gPad->Modified();
  // gPad->Update();
  // auto mg3 = new TMultiGraph();
  // mg3->SetTitle("ADM#6 LDO normal test (Vin=7V) in LN2; Total measured time (min); LDO Vout (V)");
  // mg3->Add(gr2);
  // mg3->Draw("AP"); // deleta "Ap" if you want to draw lines
  // c3->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/ADM6_LDO_NormalTest_ave.png");
  //
  // TCanvas *c5 = new TCanvas("c5","ADMStressTest",2600,1600);
  // c5->SetLeftMargin(0.15);
  // c5->SetRightMargin(0.1);
  // gPad->Modified();
  // gPad->Update();
  // auto mg5 = new TMultiGraph();
  // mg5->SetTitle("ADM#6 LDO stress test (Vin=21V) in LN2; Total measured time (min); LDO Vout (V)");
  // mg5->Add(gr1);
  // mg5->Draw("AP"); // deleta "Ap" if you want to draw lines
  // c5->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/ADM6_LDO_StressTest_ave.png");

  TCanvas *c6 = new TCanvas("c6","LPNormalTest",2600,1600);
  c6->SetLeftMargin(0.15);
  c6->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg6 = new TMultiGraph();
  mg6->SetTitle("LP#7 LDO normal test (Vin=7V) in LN2; Total measured time (min); Power Supply Iout (A)");
  mg6->Add(gr6);
  mg6->Draw("AP"); // deleta "Ap" if you want to draw lines
  c6->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/LP7_LDO_NormalTest_PS_Iout_ave.png");

  TCanvas *c7 = new TCanvas("c7","LPStressTest",2600,1600);
  c7->SetLeftMargin(0.15);
  c7->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg7 = new TMultiGraph();
  mg7->SetTitle("LP#7 LDO stress test (Vin=10V) in LN2; Total measured time (min); Power Supply Iout (A)");
  mg7->Add(gr5);
  // mg2->GetYaxis()->SetRangeUser(5.710,5.855);
  mg7->Draw("AP"); // deleta "Ap" if you want to draw lines
  c7->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/LP7_LDO_StressTest_PS_Iout_ave.png");

  TCanvas *c8 = new TCanvas("c8","ADMNormalTest",2600,1600);
  c8->SetLeftMargin(0.15);
  c8->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg8 = new TMultiGraph();
  mg8->SetTitle("ADM#6 LDO normal test (Vin=7V) in LN2; Total measured time (min); Power Supply Iout (A)");
  mg8->Add(gr8);
  mg8->Draw("AP"); // deleta "Ap" if you want to draw lines
  c8->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/ADM6_LDO_NormalTest_PS_Iout_ave.png");

  TCanvas *c9 = new TCanvas("c9","LPStressTest",2600,1600);
  c9->SetLeftMargin(0.15);
  c9->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg9 = new TMultiGraph();
  mg9->SetTitle("ADM#6 LDO stress test (Vin=21V) in LN2; Total measured time (min); Power Supply Iout (A)");
  mg9->Add(gr7);
  // mg2->GetYaxis()->SetRangeUser(5.710,5.855);
  mg9->Draw("AP"); // deleta "Ap" if you want to draw lines
  c9->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/AMD6_LDO_StressTest_PS_Iout_ave.png");


}// end StitchData_LP7ADM6_ave

void StitchData_LP5ADM5_ave()
{
  // Read File1
  fstream dataset1("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Tester1_LP5_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July31/Tester1_LP5_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July31.csv",ios::in);
  // Get rid of the 1st line;
  string dummyLine1;
  getline(dataset1, dummyLine1);
  string oneline1;

  // Read File2
  fstream dataset2("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Tester1_LP5_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July31_RestartAug6MemoryExplode/Tester1_LP5_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July31_RestartAug6MemoryExplode.csv",ios::in);
  // Get rid of the 1st line;
  string dummyLine2;
  getline(dataset2, dummyLine2);
  string oneline2;

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

  int d1_size,d2_size; // size of dataset1&2
  d1_size = time_year.size();
  cout << "dataset1 size: " << d1_size << endl;

  while(dataset2)
  {
    getline(dataset2,oneline2);
    TString x = oneline2;
    if(dataset2.eof()) break;
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
  } // end read data from file 2

  d2_size = time_year.size() - d1_size;
  cout << "dataset2 size: " << d2_size<< endl;
  cout << "dataset1&2 size: " << time_year.size()<< endl;

  // Find avarage_stress


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
    // stress
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

      cout << "stress_i: " << i << endl;

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
    // normal
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


      cout << "normal_i: " << i << endl;

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
  // int size_s = 233; //without failed data
  // int size_n = 230; //without failed data
  cout << "ADM_ave_s size: " << size_s << endl;
  for (int i = 0; i < size_s; i++)
  {
    // cout<< "ADM_stress_ave_i: " << ADM_ave_s.at(i) << endl;
    // cout<< "LP_stress_ave_i: " << LP_ave_s.at(i) << endl;
    cout<< "K2470_ave_i: " << K2470_ave_s.at(i) << endl;
    cout<< "K2460_ave_i: " << K2460_ave_s.at(i) << endl;
  }

  cout << "ADM_ave_n size: " << size_n << endl;
  for (int i = 0; i < size_n; i++)
  {
    // cout<< "ADM_normal_ave_i: " << ADM_ave_n.at(i) << endl;
    // cout<< "LP_normal_ave_i: " << LP_ave_n.at(i) << endl;
    cout<< "K2470_ave_i: " << K2470_ave_n.at(i) << endl;
    cout<< "K2460_ave_i: " << K2460_ave_n.at(i) << endl;
  }

  double A_ADM_ave_s[size_s], A_ADM_ave_n[size_n];
  double A_LP_ave_s[size_s], A_LP_ave_n[size_n];
  double A_K2460_ave_s[size_s], A_K2460_ave_n[size_n];
  double A_K2470_ave_s[size_s], A_K2470_ave_n[size_n];
  double A_t_measure_S[size_s], A_t_measure_N[size_n];

  // stress
  for (int i = 0; i < size_s; i++)
  {
    A_ADM_ave_s[i]=ADM_ave_s.at(i);
    A_LP_ave_s[i]=LP_ave_s.at(i);
    A_K2460_ave_s[i]=K2460_ave_s.at(i);
    A_K2470_ave_s[i]=K2470_ave_s.at(i);
    A_t_measure_S[i]=(i+1)*30;
  }
  // normal
  for (int i = 0; i < size_n; i++)
  {
    A_ADM_ave_n[i]=ADM_ave_n.at(i);
    A_LP_ave_n[i]=LP_ave_n.at(i);
    A_K2460_ave_n[i]=K2460_ave_n.at(i);
    A_K2470_ave_n[i]=K2470_ave_n.at(i);
    A_t_measure_N[i]=(i+1)*5;
  }

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


  TGraph *gr5  = new TGraph(233,A_t_measure_S,A_K2470_ave_s);
  gr5->SetMarkerColor(kGreen);
  gr5->SetMarkerStyle(20);

  TGraph *gr6  = new TGraph(230,A_t_measure_N,A_K2470_ave_n);
  gr6->SetMarkerColor(kGreen);
  gr6->SetMarkerStyle(21);

  TGraph *gr7  = new TGraph(size_s,A_t_measure_S,A_K2460_ave_s);
  gr7->SetMarkerColor(kBlack);
  gr7->SetMarkerStyle(20);

  TGraph *gr8  = new TGraph(size_n,A_t_measure_N,A_K2460_ave_n);
  gr8->SetMarkerColor(kBlack);
  gr8->SetMarkerStyle(21);


  // TCanvas *c1 = new TCanvas("c1","LPNormalTest",2600,1600);
  // c1->SetLeftMargin(0.15);
  // c1->SetRightMargin(0.1);
  // gPad->Modified();
  // gPad->Update();
  // auto mg1 = new TMultiGraph();
  // mg1->SetTitle("LP#5 LDO normal test (Vin=7V) in LN2; Total measured time (min); LDO Vout (V)");
  // mg1->Add(gr4);
  // mg1->Draw("AP"); // deleta "Ap" if you want to draw lines
  // c1->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/LP5_LDO_NormalTest_ave.png");
  //
  // TCanvas *c2 = new TCanvas("c2","LPStressTest",2600,1600);
  // c2->SetLeftMargin(0.15);
  // c2->SetRightMargin(0.1);
  // gPad->Modified();
  // gPad->Update();
  // auto mg2 = new TMultiGraph();
  // mg2->SetTitle("LP#5 LDO stress test (Vin=11V) in LN2; Total measured time (min); LDO Vout (V)");
  // mg2->Add(gr3);
  // // mg2->GetYaxis()->SetRangeUser(5.710,5.855);
  // mg2->Draw("AP"); // deleta "Ap" if you want to draw lines
  // c2->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/LP5_LDO_StressTest_ave.png");
  //
  // TCanvas *c3 = new TCanvas("c3","ADMNormalTest",2600,1600);
  // c3->SetLeftMargin(0.15);
  // c3->SetRightMargin(0.1);
  // gPad->Modified();
  // gPad->Update();
  // auto mg3 = new TMultiGraph();
  // mg3->SetTitle("ADM#5 LDO normal test (Vin=7V) in LN2; Total measured time (min); LDO Vout (V)");
  // mg3->Add(gr2);
  // mg3->Draw("AP"); // deleta "Ap" if you want to draw lines
  // c3->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/ADM5_2ndpart_LDO_NormalTest_ave.png");
  //
  // TCanvas *c5 = new TCanvas("c5","ADMStressTest",2600,1600);
  // c5->SetLeftMargin(0.15);
  // c5->SetRightMargin(0.1);
  // gPad->Modified();
  // gPad->Update();
  // auto mg5 = new TMultiGraph();
  // mg5->SetTitle("ADM#5 LDO stress test (Vin=21V) in LN2; Total measured time (min); LDO Vout (V)");
  // mg5->Add(gr1);
  // mg5->Draw("AP"); // deleta "Ap" if you want to draw lines
  // c5->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/ADM5_2ndpart_LDO_StressTest_ave.png");
  //
  TCanvas *c6 = new TCanvas("c6","LPNormalTest",2600,1600);
  c6->SetLeftMargin(0.15);
  c6->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg6 = new TMultiGraph();
  mg6->SetTitle("LP#5 LDO normal test (Vin=7V) in LN2; Total measured time (min); Power Supply Iout (A)");
  mg6->Add(gr6);
  mg6->Draw("AP"); // deleta "Ap" if you want to draw lines
  c6->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/LP5_LDO_NormalTest_PS_Iout_ave_nF.png");

  TCanvas *c7 = new TCanvas("c7","LPStressTest",2600,1600);
  c7->SetLeftMargin(0.15);
  c7->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg7 = new TMultiGraph();
  mg7->SetTitle("LP#5 LDO stress test (Vin=11V) in LN2; Total measured time (min); Power Supply Iout (A)");
  mg7->Add(gr5);
  // mg2->GetYaxis()->SetRangeUser(5.710,5.855);
  mg7->Draw("AP"); // deleta "Ap" if you want to draw lines
  c7->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/LP5_LDO_StressTest_PS_Iout_ave_nF.png");

}// end StitchData_LP5ADM5_ave

void StitchData_LP3ADM5_ave()
{
  // Read File1
  fstream dataset1("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Tester1_LP3_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July20/Tester1_LP3_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July20.csv",ios::in);
  // Get rid of the 1st line;
  string dummyLine1;
  getline(dataset1, dummyLine1);
  string oneline1;

  // Read File2
  fstream dataset2("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Tester1_LP3_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July20_continued/Tester1_LP3_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July20_continued.csv",ios::in);
  // Get rid of the 1st line;
  string dummyLine2;
  getline(dataset2, dummyLine2);
  string oneline2;

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

  int d1_size,d2_size; // size of dataset1&2
  d1_size = time_year.size();
  cout << "dataset1 size: " << d1_size << endl;

  while(dataset2)
  {
    getline(dataset2,oneline2);
    TString x = oneline2;
    if(dataset2.eof()) break;
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
  } // end read data from file 2

  d2_size = time_year.size() - d1_size;
  cout << "dataset2 size: " << d2_size<< endl;
  cout << "dataset1&2 size: " << time_year.size()<< endl;

  // Find avarage_stress


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
    // stress
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


      cout << "stress_i: " << i << endl;

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
    // normal
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


      cout << "normal_i: " << i << endl;

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
  // int size_s = 233; //without failed data
  // int size_n = 230; //without failed data
  cout << "ADM_ave_s size: " << size_s << endl;
  for (int i = 0; i < size_s; i++)
  {
    // cout<< "ADM_stress_ave_i: " << ADM_ave_s.at(i) << endl;
    // cout<< "LP_stress_ave_i: " << LP_ave_s.at(i) << endl;
    cout<< "K2470_ave_i: " << K2470_ave_s.at(i) << endl;
    cout<< "K2460_ave_i: " << K2460_ave_s.at(i) << endl;
  }

  cout << "ADM_ave_n size: " << size_n << endl;
  for (int i = 0; i < size_n; i++)
  {
    // cout<< "ADM_normal_ave_i: " << ADM_ave_n.at(i) << endl;
    // cout<< "LP_normal_ave_i: " << LP_ave_n.at(i) << endl;
    cout<< "K2470_ave_i: " << K2470_ave_n.at(i) << endl;
    cout<< "K2460_ave_i: " << K2460_ave_n.at(i) << endl;
  }

  double A_ADM_ave_s[size_s], A_ADM_ave_n[size_n];
  double A_LP_ave_s[size_s], A_LP_ave_n[size_n];
  double A_K2460_ave_s[size_s], A_K2460_ave_n[size_n];
  double A_K2470_ave_s[size_s], A_K2470_ave_n[size_n];
  double A_t_measure_S[size_s], A_t_measure_N[size_n];

  // stress
  for (int i = 0; i < size_s; i++)
  {
    A_ADM_ave_s[i]=ADM_ave_s.at(i);
    A_LP_ave_s[i]=LP_ave_s.at(i);
    A_K2460_ave_s[i]=K2460_ave_s.at(i);
    A_K2470_ave_s[i]=K2470_ave_s.at(i);
    A_t_measure_S[i]=(i+1)*30;
  }
  // normal
  for (int i = 0; i < size_n; i++)
  {
    A_ADM_ave_n[i]=ADM_ave_n.at(i);
    A_LP_ave_n[i]=LP_ave_n.at(i);
    A_K2460_ave_n[i]=K2460_ave_n.at(i);
    A_K2470_ave_n[i]=K2470_ave_n.at(i);
    A_t_measure_N[i]=(i+1)*5;
  }

  //
  TGraph *gr1  = new TGraph(size_s,A_t_measure_S,A_ADM_ave_s);
  gr1->SetMarkerColor(kBlue);
  gr1->SetMarkerStyle(20);

  TGraph *gr2  = new TGraph(size_n,A_t_measure_N,A_ADM_ave_n);
  gr2->SetMarkerColor(kBlue);
  gr2->SetMarkerStyle(21);

  TGraph *gr3  = new TGraph(246,A_t_measure_S,A_LP_ave_s);
  gr3->SetMarkerColor(kRed);
  gr3->SetMarkerStyle(20);

  TGraph *gr4  = new TGraph(250,A_t_measure_N,A_LP_ave_n);
  gr4->SetMarkerColor(kRed);
  gr4->SetMarkerStyle(21);

  TGraph *gr5  = new TGraph(246,A_t_measure_S,A_K2470_ave_s);
  gr5->SetMarkerColor(kGreen);
  gr5->SetMarkerStyle(20);

  TGraph *gr6  = new TGraph(250,A_t_measure_N,A_K2470_ave_n);
  gr6->SetMarkerColor(kGreen);
  gr6->SetMarkerStyle(21);

  TGraph *gr7  = new TGraph(size_s,A_t_measure_S,A_K2460_ave_s);
  gr7->SetMarkerColor(kBlack);
  gr7->SetMarkerStyle(20);

  TGraph *gr8  = new TGraph(size_n,A_t_measure_N,A_K2460_ave_n);
  gr8->SetMarkerColor(kBlack);
  gr8->SetMarkerStyle(21);



  // TCanvas *c1 = new TCanvas("c1","LPNormalTest",2600,1600);
  // c1->SetLeftMargin(0.15);
  // c1->SetRightMargin(0.1);
  // gPad->Modified();
  // gPad->Update();
  // auto mg1 = new TMultiGraph();
  // mg1->SetTitle("LP#3 LDO normal test (Vin=7V) in LN2; Total measured time (min); LDO Vout (V)");
  // mg1->Add(gr4);
  // mg1->Draw("AP"); // deleta "Ap" if you want to draw lines
  // c1->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/LP3_LDO_NormalTest_ave_nF.png");
  //
  // TCanvas *c2 = new TCanvas("c2","LPStressTest",2600,1600);
  // c2->SetLeftMargin(0.15);
  // c2->SetRightMargin(0.1);
  // gPad->Modified();
  // gPad->Update();
  // auto mg2 = new TMultiGraph();
  // mg2->SetTitle("LP#3 LDO stress test (Vin=11V) in LN2; Total measured time (min); LDO Vout (V)");
  // mg2->Add(gr3);
  // // mg2->GetYaxis()->SetRangeUser(5.710,5.855);
  // mg2->Draw("AP"); // deleta "Ap" if you want to draw lines
  // c2->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/LP3_LDO_StressTest_ave_nF.png");

  TCanvas *c6 = new TCanvas("c6","LPNormalTest",2600,1600);
  c6->SetLeftMargin(0.15);
  c6->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg6 = new TMultiGraph();
  mg6->SetTitle("LP#3 LDO normal test (Vin=7V) in LN2; Total measured time (min); Power Supply Iout (A)");
  mg6->Add(gr6);
  mg6->Draw("AP"); // deleta "Ap" if you want to draw lines
  c6->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/LP3_LDO_NormalTest_PS_Iout_ave_nF.png");

  TCanvas *c7 = new TCanvas("c7","LPStressTest",2600,1600);
  c7->SetLeftMargin(0.15);
  c7->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg7 = new TMultiGraph();
  mg7->SetTitle("LP#3 LDO stress test (Vin=11V) in LN2; Total measured time (min); Power Supply Iout (A)");
  mg7->Add(gr5);
  // mg2->GetYaxis()->SetRangeUser(5.710,5.855);
  mg7->Draw("AP"); // deleta "Ap" if you want to draw lines
  c7->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/LP3_LDO_StressTest_PS_Iout_ave_nF.png");

  //
  // TCanvas *c3 = new TCanvas("c3","ADMNormalTest",2600,1600);
  // c3->SetLeftMargin(0.15);
  // c3->SetRightMargin(0.1);
  // gPad->Modified();
  // gPad->Update();
  // auto mg3 = new TMultiGraph();
  // mg3->SetTitle("ADM#5 LDO normal test (Vin=7V) in LN2; Total measured time (min); LDO Vout (V)");
  // mg3->Add(gr2);
  // mg3->Draw("AP"); // deleta "Ap" if you want to draw lines
  // c3->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/ADM5_1stpart_LDO_NormalTest_ave.png");
  //
  // TCanvas *c5 = new TCanvas("c5","ADMStressTest",2600,1600);
  // c5->SetLeftMargin(0.15);
  // c5->SetRightMargin(0.1);
  // gPad->Modified();
  // gPad->Update();
  // auto mg5 = new TMultiGraph();
  // mg5->SetTitle("ADM#5 LDO stress test (Vin=21V) in LN2; Total measured time (min); LDO Vout (V)");
  // mg5->Add(gr1);
  // mg5->Draw("AP"); // deleta "Ap" if you want to draw lines
  // c5->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/ADM5_1stpart_LDO_StressTest_ave.png");


}// end StitchData_LP3ADM5_ave

void StitchData_CombineADM5()
{
  // Read File1
  fstream dataset1("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Tester1_LP3_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July20/Tester1_LP3_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July20.csv",ios::in);
  // Get rid of the 1st line;
  string dummyLine1;
  getline(dataset1, dummyLine1);
  string oneline1;

  // Read File2
  fstream dataset2("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Tester1_LP3_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July20_continued/Tester1_LP3_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July20_continued.csv",ios::in);
  // Get rid of the 1st line;
  string dummyLine2;
  getline(dataset2, dummyLine2);
  string oneline2;

  // Read File1
  fstream dataset3("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Tester1_LP5_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July31/Tester1_LP5_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July31.csv",ios::in);
  // Get rid of the 1st line;
  string dummyLine3;
  getline(dataset3, dummyLine3);
  string oneline3;

  // Read File2
  fstream dataset4("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Tester1_LP5_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July31_RestartAug6MemoryExplode/Tester1_LP5_Vin7-11_ADM5_Vin7-21_Unstress5min_Stress30min_LN2_July31_RestartAug6MemoryExplode.csv",ios::in);
  // Get rid of the 1st line;
  string dummyLine4;
  getline(dataset4, dummyLine4);
  string oneline4;

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

  while(dataset2)
  {
    getline(dataset2,oneline2);
    TString x = oneline2;
    if(dataset2.eof()) break;
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
  } // end read data from file 2

  while(dataset3)
  {
    getline(dataset3,oneline3);
    TString x = oneline3;
    if(dataset3.eof()) break;
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
  } // end read data from file 3

  while(dataset4)
  {
    getline(dataset4,oneline4);
    TString x = oneline4;
    if(dataset4.eof()) break;
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
  } // end read data from file 4

  cout << "dataset size: " << time_year.size()<< endl;

  // Find avarage_stress


  double ADM_sum_s = 0, counter_s = 0, ADM_Average_s = 0;
  double ADM_sum_n = 0, counter_n = 0, ADM_Average_n = 0;
  vector<double> ADM_ave_s,ADM_ave_n;

  double K2460_sum_s = 0, Kcounter_s = 0, K2460_Average_s = 0;
  double K2460_sum_n = 0, Kcounter_n = 0, K2460_Average_n = 0;
  vector<double> K2460_ave_s,K2460_ave_n;

  for (int i = 0; i < time_year.size(); i++)
  {
    // stress
    while(K2460_V.at(i)>9)
    {
      ADM_sum_s += ADM_Vout.at(i);
      ++counter_s;
      ADM_Average_s =  ADM_sum_s / counter_s;

      K2460_sum_s += K2460_I.at(i);
      ++Kcounter_s;
      K2460_Average_s =  K2460_sum_s / Kcounter_s;

      cout << "stress_i: " << i << endl;

      if(i < time_year.size()-2 && K2460_V.at(i+1)<9)
      {
        ADM_ave_s.emplace_back(ADM_Average_s);
        ADM_sum_s = 0;
        counter_s = 0;
        ADM_Average_s = 0;

        K2460_ave_s.emplace_back(K2460_Average_s);
        K2460_sum_s = 0;
        Kcounter_s = 0;
        K2460_Average_s = 0;
      }
      break;
    }
    // normal
    while(K2460_V.at(i)<9)
    {
      ADM_sum_n += ADM_Vout.at(i);
      ++counter_n;
      ADM_Average_n =  ADM_sum_n / counter_n;

      K2460_sum_n += K2460_I.at(i);
      ++Kcounter_n;
      K2460_Average_n =  K2460_sum_n / Kcounter_n;


      cout << "normal_i: " << i << endl;

      if(i < time_year.size()-2 && K2460_V.at(i+1)>9)
      {
        ADM_ave_n.emplace_back(ADM_Average_n);
        ADM_sum_n = 0;
        counter_n = 0;
        ADM_Average_n = 0;

        K2460_ave_n.emplace_back(K2460_Average_n);
        K2460_sum_n = 0;
        Kcounter_n = 0;
        K2460_Average_n = 0;
      }
      break;
    }
  }

  // Draw plots
  int size_ave_s = ADM_ave_s.size();
  int size_ave_n = ADM_ave_n.size();
  cout << "ADM_ave_s size: " << size_ave_s << endl;
  for (int i = 0; i < size_ave_s; i++)
  {
    cout<< "ADM_stress_ave_i: " << ADM_ave_s.at(i) << endl;
  }

  cout << "ADM_ave_n size: " << size_ave_n << endl;
  for (int i = 0; i < size_ave_n; i++)
  {
    cout<< "ADM_normal_ave_i: " << ADM_ave_n.at(i) << endl;
  }

  double A_ADM_ave_s[size_ave_s], A_ADM_ave_n[size_ave_n];
  double A_K2460_ave_s[size_ave_s], A_K2460_ave_n[size_ave_n];
  double A_t_avg_measure_S[size_ave_s], A_t_avg_measure_N[size_ave_n];

  // stress
  for (int i = 0; i < size_ave_s; i++)
  {
    A_ADM_ave_s[i]=ADM_ave_s.at(i);
    A_K2460_ave_s[i]=K2460_ave_s.at(i);
    A_t_avg_measure_S[i]=(i+1)*30;
  }
  // normal
  for (int i = 0; i < size_ave_n; i++)
  {
    A_ADM_ave_n[i]=ADM_ave_n.at(i);
    A_K2460_ave_n[i]=K2460_ave_n.at(i);
    A_t_avg_measure_N[i]=(i+1)*5;
  }

  //
  TGraph *gr1  = new TGraph(size_ave_s,A_t_avg_measure_S,A_ADM_ave_s);
  gr1->SetMarkerColor(kBlue);
  gr1->SetMarkerStyle(20);

  TGraph *gr2  = new TGraph(size_ave_n,A_t_avg_measure_N,A_ADM_ave_n);
  gr2->SetMarkerColor(kBlue);
  gr2->SetMarkerStyle(21);


  TGraph *gr7  = new TGraph(size_ave_s,A_t_avg_measure_S,A_K2460_ave_s);
  gr7->SetMarkerColor(kBlack);
  gr7->SetMarkerStyle(20);

  TGraph *gr8  = new TGraph(size_ave_n,A_t_avg_measure_N,A_K2460_ave_n);
  gr8->SetMarkerColor(kBlack);
  gr8->SetMarkerStyle(21);

  TCanvas *c3 = new TCanvas("c3","ADMNormalTest",2600,1600);
  c3->SetLeftMargin(0.15);
  c3->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg3 = new TMultiGraph();
  mg3->SetTitle("ADM#5 LDO normal test (Vin=7V) in LN2; Total measured time (min); LDO Vout (V)");
  mg3->Add(gr2);
  mg3->Draw("AP"); // deleta "Ap" if you want to draw lines
  c3->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/ADM5_combine_LDO_NormalTest_ave.png");

  TCanvas *c5 = new TCanvas("c5","ADMStressTest",2600,1600);
  c5->SetLeftMargin(0.15);
  c5->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg5 = new TMultiGraph();
  mg5->SetTitle("ADM#5 LDO stress test (Vin=21V) in LN2; Total measured time (min); LDO Vout (V)");
  mg5->Add(gr1);
  // mg5->GetYaxis()->SetRangeUser(5.03,5.06);
  mg5->Draw("AP"); // deleta "Ap" if you want to draw lines
  c5->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/ADM5_combine_LDO_StressTest_ave.png");

  TCanvas *c8 = new TCanvas("c8","ADMNormalTest",2600,1600);
  c8->SetLeftMargin(0.15);
  c8->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg8 = new TMultiGraph();
  mg8->SetTitle("ADM#5 LDO normal test (Vin=7V) in LN2; Total measured time (s); Power Supply Iout (A)");
  mg8->Add(gr8);
  mg8->Draw("AP"); // deleta "Ap" if you want to draw lines
  c8->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/ADM5_combine_LDO_NormalTest_PS_Iout_ave.png");

  TCanvas *c9 = new TCanvas("c9","ADMStressTest",2600,1600);
  c9->SetLeftMargin(0.15);
  c9->SetRightMargin(0.1);
  gPad->Modified();
  gPad->Update();
  auto mg9 = new TMultiGraph();
  mg9->SetTitle("ADM#5 LDO stress test (Vin=21V) in LN2; Total measured time (s); Power Supply Iout (A)");
  mg9->Add(gr7);
  mg9->Draw("AP"); // deleta "Ap" if you want to draw lines
  c9->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/ADM5_combine_LDO_StressTest_PS_Iout_ave.png");

  //----------------------------------------------------------------------------
  //****************************************************************************
  //----------------------------------------------------------------------------
  // Use raw data instead of averaged data
  // int size = time_year.size();
  // double x[size],A_LP_Vout[size],A_ADM_Vout[size];
  //
  // // vector for stress and normal
  // vector<double> LP_Vout_s,LP_Vout_n,ADM_Vout_s,ADM_Vout_n,t_measure_s,t_measure_n; //s:stress, n:normal
  //
  // for (int i = 0; i < size; i++)
  // {
  //   A_ADM_Vout[i]=ADM_Vout.at(i);
  //   if(K2460_V.at(i)>9)
  //   {
  //     ADM_Vout_s.emplace_back(ADM_Vout.at(i));
  //   }
  //   else
  //   {
  //     ADM_Vout_n.emplace_back(ADM_Vout.at(i));
  //   }
  //
  //   x[i]=i*10;
  //   // cout << "nth: " << i << ", K2470_V: " << K2470_V.at(i) << endl;
  // }
  //
  // // put into array
  // int size_s = ADM_Vout_s.size();
  // int size_n = ADM_Vout_n.size();
  // // int size_s = 10000;
  // // int size_n = 10000;
  // double A_ADM_Vout_S[size_s], A_ADM_Vout_N[size_n];
  // double A_t_measure_S[size_s], A_t_measure_N[size_n];
  //
  // cout << "size_s: " << size_s << endl;
  // cout << "size_n: " << size_n << endl;
  //
  // // stress
  // for (int i = 0; i < size_s; i++)
  // {
  //   A_ADM_Vout_S[i]=ADM_Vout_s.at(i);
  //   A_t_measure_S[i]=i*10;
  // }
  // // normal
  // for (int i = 0; i < size_n; i++)
  // {
  //   A_ADM_Vout_N[i]=ADM_Vout_n.at(i);
  //   A_t_measure_N[i]=i*10;
  // }
  //
  // TGraph *gr3  = new TGraph(size_s,A_t_measure_S,A_ADM_Vout_S);
  // gr3->SetMarkerColor(kBlue);
  // gr3->SetMarkerStyle(20);
  //
  // TGraph *gr4  = new TGraph(size_n,A_t_measure_N,A_ADM_Vout_N);
  // gr4->SetMarkerColor(kBlue);
  // gr4->SetMarkerStyle(21);
  //
  //
  // TCanvas *c1 = new TCanvas("c1","ADMNormalTest",2600,1600);
  // c1->SetLeftMargin(0.15);
  // c1->SetRightMargin(0.1);
  // gPad->Modified();
  // gPad->Update();
  // auto mg1 = new TMultiGraph();
  // mg1->SetTitle("ADM#5 LDO normal test (Vin=7V) in LN2; Total measured time (s); LDO Vout (V)");
  // mg1->Add(gr4);
  // mg1->Draw("AP"); // deleta "Ap" if you want to draw lines
  // c1->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/ADM5_combine_LDO_NormalTest.png");
  //
  // TCanvas *c2 = new TCanvas("c2","ADMStressTest",2600,1600);
  // c2->SetLeftMargin(0.15);
  // c2->SetRightMargin(0.1);
  // gPad->Modified();
  // gPad->Update();
  // auto mg2 = new TMultiGraph();
  // mg2->SetTitle("ADM#5 LDO stress test (Vin=21V) in LN2; Total measured time (s); LDO Vout (V)");
  // mg2->Add(gr3);
  // mg2->Draw("AP"); // deleta "Ap" if you want to draw lines
  // c2->SaveAs("/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/Plots/23Aug9/ADM5_combine_LDO_StressTest.png");

}// end StitchData_CombineADM5
