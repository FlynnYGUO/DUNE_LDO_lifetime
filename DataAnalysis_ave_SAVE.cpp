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
#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TColor.h>

using namespace std;

void DataAnalysis_ave_SAVE(string fileName, string date, int batchNumber, float LP_NominalV, float LP_StressV, float ADM_NominalV, float ADM_StressV)
{

  string basePath = "/Users/flynnguo/Documents/SBU/NN/DUNE/FD_PDS/LDO_Lifetime/";
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
      cout << "Abnormal voltage which is smaller than 6V" << endl;
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
  // cout << "ADM_ave_s size: " << size_s << endl;
  // cout << "ADM_ave_n size: " << size_n << endl;

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

  // size_s = 67; // zoom in the first 2000 min of Stress test 67=2000/30
  // size_s = 140; // zoom in the first 6000 min of Stress test300=6000/30  ;  140 for LP8, LP18, lp13, lp21
  // size_n = 80; //zoom in the first 500 min of Nominal test 100=500/5
  // Save files
  // Open a new ROOT file
  TFile *file = new TFile(Form("%sLP%d_%.2fto%.2f_ADM%d_%.2fto%.2f.root",basePlotPath.Data(),batchNumber, LP_NominalV,LP_StressV,batchNumber,ADM_NominalV,ADM_StressV), "RECREATE");
  TTree *tree_s = new TTree("tree_s", "stress test values");
  double V_ADM_ave_s, V_LP_ave_s, V_t_measure_s;
  TTree *tree_n = new TTree("tree_n", "nominal test values");
  double V_ADM_ave_n, V_LP_ave_n, V_t_measure_n;
  tree_s->Branch("ADM_ave_s",  &V_ADM_ave_s,  "V_ADM_ave_s/D");
  tree_s->Branch("LP_ave_s",  &V_LP_ave_s,  "V_LP_ave_s/D");
  tree_s->Branch("t_measure_s",  &V_t_measure_s,  "V_t_measure_s/D");

  tree_n->Branch("ADM_ave_n",  &V_ADM_ave_n,  "V_ADM_ave_n/D");
  tree_n->Branch("LP_ave_n",  &V_LP_ave_n,  "V_LP_ave_n/D");
  tree_n->Branch("t_measure_n",  &V_t_measure_n,  "V_t_measure_n/D");

  tree_s->Branch("batchNumber",  &batchNumber,  "batchNumber/I");
  tree_n->Branch("batchNumber",  &batchNumber,  "batchNumber/I");



  // Stress
  for (int i = 0; i < size_s; i++)
  {

    A_ADM_ave_s[i]=ADM_ave_s.at(i);
    V_ADM_ave_s = ADM_ave_s.at(i);
    if ( A_ADM_ave_s[i] < A_ADM_ave_s_min ) A_ADM_ave_s_min = A_ADM_ave_s[i];
    if ( A_ADM_ave_s[i] > A_ADM_ave_s_max ) A_ADM_ave_s_max = A_ADM_ave_s[i];

    A_LP_ave_s[i]=LP_ave_s.at(i);
    V_LP_ave_s = LP_ave_s.at(i);
    if ( A_LP_ave_s[i] < A_LP_ave_s_min ) A_LP_ave_s_min = A_LP_ave_s[i];
    if ( A_LP_ave_s[i] > A_LP_ave_s_max ) A_LP_ave_s_max = A_LP_ave_s[i];

    A_K2460_ave_s[i]=K2460_ave_s.at(i);
    if ( A_K2460_ave_s[i] < A_K2460_ave_s_min ) A_K2460_ave_s_min = A_K2460_ave_s[i];
    if ( A_K2460_ave_s[i] > A_K2460_ave_s_max ) A_K2460_ave_s_max = A_K2460_ave_s[i];

    A_K2470_ave_s[i]=K2470_ave_s.at(i);
    if ( A_K2470_ave_s[i] < A_K2470_ave_s_min ) A_K2470_ave_s_min = A_K2470_ave_s[i];
    if ( A_K2470_ave_s[i] > A_K2470_ave_s_max ) A_K2470_ave_s_max = A_K2470_ave_s[i];

    A_t_measure_S[i]=(i+1)*30;
    V_t_measure_s = (i+1)*30;
    cout << "i: " << i <<", V_t_measure_s: " << V_t_measure_s << ", LP_ave_s: " << V_LP_ave_s << endl;
    tree_s->Fill();
  }

  for (int i = 0; i < size_n; i++)
  {

    A_ADM_ave_n[i]=ADM_ave_n.at(i);
    V_ADM_ave_n = ADM_ave_n.at(i);
    if ( A_ADM_ave_n[i] < A_ADM_ave_n_min ) A_ADM_ave_n_min = A_ADM_ave_n[i];
    if ( A_ADM_ave_n[i] > A_ADM_ave_n_max ) A_ADM_ave_n_max = A_ADM_ave_n[i];

    A_LP_ave_n[i]=LP_ave_n.at(i);
    V_LP_ave_n = LP_ave_n.at(i);
    if ( A_LP_ave_n[i] <= A_LP_ave_n_min ) A_LP_ave_n_min = A_LP_ave_n[i];
    if ( A_LP_ave_n[i] >= A_LP_ave_n_max ) A_LP_ave_n_max = A_LP_ave_n[i];

    A_K2460_ave_n[i]=K2460_ave_n.at(i);
    if ( A_K2460_ave_n[i] < A_K2460_ave_n_min ) A_K2460_ave_n_min = A_K2460_ave_n[i];
    if ( A_K2460_ave_n[i] > A_K2460_ave_n_max ) A_K2460_ave_n_max = A_K2460_ave_n[i];

    A_K2470_ave_n[i]=K2470_ave_n.at(i);
    if ( A_K2470_ave_n[i] < A_K2470_ave_n_min ) A_K2470_ave_n_min = A_K2470_ave_n[i];
    if ( A_K2470_ave_n[i] > A_K2470_ave_n_max ) A_K2470_ave_n_max = A_K2470_ave_n[i];

    A_t_measure_N[i]=(i+1)*5;
    V_t_measure_n = (i+1)*5;
    tree_n->Fill();
  }

  tree_s->Branch("LP_ave_s_ini",  &A_LP_ave_s_ini,  "A_LP_ave_s_ini/D");
  tree_s->Branch("LP_ave_s_min",  &A_LP_ave_s_min,  "A_LP_ave_s_min/D");
  tree_s->Branch("LP_ave_s_max",  &A_LP_ave_s_max,  "A_LP_ave_s_max/D");
  tree_s->Branch("ADM_ave_s_ini",  &A_ADM_ave_s_ini,  "A_ADM_ave_s_ini/D");
  tree_s->Branch("ADM_ave_s_min",  &A_ADM_ave_s_min,  "A_ADM_ave_s_min/D");
  tree_s->Branch("ADM_ave_s_max",  &A_ADM_ave_s_max,  "A_ADM_ave_s_max/D");

  tree_n->Branch("LP_ave_n_ini",  &A_LP_ave_n_ini,  "A_LP_ave_n_ini/D");
  tree_n->Branch("LP_ave_n_min",  &A_LP_ave_n_min,  "A_LP_ave_n_min/D");
  tree_n->Branch("LP_ave_n_max",  &A_LP_ave_n_max,  "A_LP_ave_n_max/D");
  tree_n->Branch("ADM_ave_n_ini",  &A_ADM_ave_n_ini,  "A_ADM_ave_n_ini/D");
  tree_n->Branch("ADM_ave_n_min",  &A_ADM_ave_n_min,  "A_ADM_ave_n_min/D");
  tree_n->Branch("ADM_ave_n_max",  &A_ADM_ave_n_max,  "A_ADM_ave_n_max/D");

  tree_s->Fill();
  tree_n->Fill();


  tree_s->Write();
  tree_n->Write();
  file->Close();

  delete file;

}// end DataAnalysis_ave
