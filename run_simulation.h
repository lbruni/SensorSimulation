

#ifndef ____run_simulation__
#define ____run_simulation__

#include "sensor_response.cpp"
#include "hist2DMaker.cpp"
#include "HitAndChargeHist.cpp"
#include "cluster.cpp"
#include "TGraphErrors.h"
#include "CreateChiSquare.cpp"
#include "TAttMarker.h"
#include "TAttLine.h"
#include "THistPainter.h"
#include "crosstalk.cpp"
#include "addPedestal.cpp"

#define pitch_size  0.074

class run_simulation {
    
public:
    void Strips_under_study(Int_t min_strip, Int_t max_strip);
    void get_landau();
    void get_clusterStrip_histo();
    void init();
    void openfiles();

    void loop(Int_t numberOfEvents);
    void LoopOnSigma();
    void LoopOnSigmaChiSquare();
    Double_t calculateEfficiency(Double_t n_events, Double_t n_null_clusters);
    Double_t calculateErrorEfficiency(Double_t n_events, Double_t eff);
    Double_t sigma = 0.011;
    Double_t threshold;
    void  Gaussian_random();
    Double_t GaussRan(Double_t hit);
    void run_efficiency();
    Double_t x_res_eff;
    
protected:
//private:
   //virtual  void processEvent()=0;
    hitGenerator m_hitmaker;
    sensor_response m_sensor;
    hist2DMaker m_hist2DMaker;
    HitAndChargeHist m_HitAndChargeHist;
    digitizer m_analog,m_binary;
    cluster m_cluster;
    crosstalk m_cross;
    addPedestal m_pedestal;
    
    CreateChiSquare m_chisquare;
    Int_t m_strip_min;
    Int_t m_strip_max;
    TF1* f;
    Double_t inStrip, clusterSize;
    Int_t ClusterZero;
    Int_t xROI;
    Double_t Efficiency,Efficiency_err;
    TH2D * m_sigma_cluster = nullptr;
    TH2D * m_sigma_chi = nullptr;
    TGraphErrors * m_scan = nullptr;
    TCanvas *scan;
    TH2D * hist = nullptr;
    TCanvas *cluster_canvas;
    TH2D *clus_sim  = nullptr;
    TH1D *clus_data = nullptr;
    TH1D *clus_proj= nullptr;
    TProfile *tpf_data, *tpf_sim, *m_sigma_chi_pfx;
    Double_t ChiSquare;
    TGraph *g;
    Double_t npoints;
    TRandom *rgauss;
};

//
//class run_cluster_size_simulation:public run_simulation {
//  virtual  void processEvent() override;
//};



#endif /* defined(____run_simulation__) */
