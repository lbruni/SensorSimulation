

#ifndef ____run_simulation__
#define ____run_simulation__

#include "sensor_response.cpp"
#include "hist2DMaker.cpp"
#include "HitAndChargeHist.cpp"

#define pitch_size  0.074
#define sigma  pitch_size*5
class run_simulation {

public:
    TH2D *hist = NULL;
    TH1D *hitDist = NULL;
    TH1D *ChargeDist = NULL;
    
    void Strips_under_study(Int_t min_strip, Int_t max_strip);
    void init();
    void loop(Int_t numberOfEvents);

private:
    hitGenerator m_hitmaker;
    sensor_response m_sensor;
    hist2DMaker m_hist2DMaker;
    HitAndChargeHist m_HitAndChargeHist;
    digitizer m_analog,m_binary;
    Int_t m_strip_min;
    Int_t m_strip_max;
    const hitGenerator* get_hitmaker();
    const sensor_response* get_sensor();
    const hist2DMaker* get_hist2DMaker();
    const HitAndChargeHist* get_HitAndChargeHist();
    
};




#endif /* defined(____run_simulation__) */
