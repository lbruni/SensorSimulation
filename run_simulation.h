

#ifndef ____run_simulation__
#define ____run_simulation__

#include "sensor_response.cpp"
#include "hist2DMaker.cpp"
#include "HitAndChargeHist.cpp"
#include "cluster.cpp"


#define pitch_size  0.074
class run_simulation {
    
public:
    void Strips_under_study(Int_t min_strip, Int_t max_strip);
    void get_landau();
    void init();
    void loop(Int_t numberOfEvents);
    void LoopOnSigma() ;
    Double_t sigma = 0.05;
protected:
    virtual  void processEvent()=0; 
    hitGenerator m_hitmaker;
    sensor_response m_sensor;
    hist2DMaker m_hist2DMaker;
    HitAndChargeHist m_HitAndChargeHist;
    digitizer m_analog,m_binary;
    cluster m_cluster;
    Int_t m_strip_min;
    Int_t m_strip_max;
    TF1* f;


    TH2D * m_sigma_cluster = nullptr;
};


class run_cluster_size_simulation:public run_simulation {
  virtual  void processEvent() override;
};



#endif /* defined(____run_simulation__) */
