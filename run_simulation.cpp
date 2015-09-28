
#include "run_simulation.h"

void run_simulation::Strips_under_study(Int_t min_strip, Int_t max_strip){
    
    
    m_hitmaker.set_strips(min_strip, max_strip);
    m_sensor.strips(min_strip, max_strip);
    m_strip_min = min_strip;
    m_strip_max = max_strip;
    
}
void run_simulation::init() {
    
    m_sensor.set_pitch_size(pitch_size);
    m_sensor.set_input(m_hitmaker.get_hit_ptr());
    run_simulation::Strips_under_study(0 ,99);
    m_hitmaker.set_charge(3.6, 1.5);
    m_sensor.set_charge_sharing(sigma);//???<--- now sets the sigma for the gaussian distr of the charge
    
    m_sensor.init();
    gSystem->MakeDirectory(folder_name);
}

void run_simulation::loop(Int_t numberOfEvents) {
    
    //***Histograms below are done to check if the Hits and Charge are well generated
    //***See class HitAndChargeHist
  //  hitDist = m_HitAndChargeHist.histHitDist();
   // ChargeDist = m_HitAndChargeHist.histChargeDist();
    
    for (Int_t i = 0; i < numberOfEvents; ++i) {
        
        m_hitmaker.ProcessEvent();
        m_sensor.ProcessEvent();
        
      hist = m_hist2DMaker.histMake(m_strip_min, m_strip_max, pitch_size, m_sensor.m_strip_position);
       m_hist2DMaker.histDrawAndSave(hist, i, pitch_size);

       // m_HitAndChargeHist.FillHisto(hitDist,m_sensor.hit_position);
       // m_HitAndChargeHist.FillHisto(ChargeDist,m_sensor.generated_charge);
        
        
    }
  //  m_HitAndChargeHist.histDrawAndSave(hitDist,ChargeDist);
}


const hitGenerator* run_simulation::get_hitmaker(){
    return &m_hitmaker;
}
const sensor_response* run_simulation::get_sensor(){
    return &m_sensor;
}
const hist2DMaker* run_simulation::get_hist2DMaker(){
    return &m_hist2DMaker;
}
const HitAndChargeHist* run_simulation::get_HitAndChargeHist(){
    return &m_HitAndChargeHist;
}
