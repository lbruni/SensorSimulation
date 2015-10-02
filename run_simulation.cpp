
#include "run_simulation.h"
#include "TSystem.h"
#include "TH1D.h"

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
    
    
    m_analog.set_digits(0.01, 10, 128);
    m_analog.set_preAmplifier(95);
    m_analog.set_intput_pointer(m_sensor.get_hit_ptr());
    
    Double_t threshold = 1;
    m_binary.set_digits(threshold, threshold, 2);
    m_binary.set_preAmplifier(95);
    m_binary.set_intput_pointer(m_sensor.get_hit_ptr());
    gSystem->MakeDirectory(folder_name);
    
    m_cluster.set_intput_pointer_digitizer(m_binary.digitizer::get_hit_ptr());
}

void run_simulation::loop(Int_t numberOfEvents) {
    
    //***Histograms below are done to check if the Hits and Charge are well generated
    //***See class HitAndChargeHist
    //  hitDist = m_HitAndChargeHist.histHitDist();
    // ChargeDist = m_HitAndChargeHist.histChargeDist();
    
    clus= new TH2D("clus","h2", 120, 0,3, 20, 0, 20);
    
    for (Int_t i = 0; i < numberOfEvents; ++i) {
        
        m_hitmaker.ProcessEvent();
        m_sensor.ProcessEvent();
        // m_analog.processEvent();
        m_binary.processEvent();
       // hist = m_hist2DMaker.histMake(m_strip_min, m_strip_max, pitch_size, m_sensor.m_strip_position);
      //  m_hist2DMaker.histDrawAndSave(hist, i, pitch_size);
        //new TCanvas;
        //hist->ProjectionX()->Draw();
        // m_sensor.get_fit()->Draw("same");
        // m_HitAndChargeHist.FillHisto(hitDist,m_sensor.hit_position);
        // m_HitAndChargeHist.FillHisto(ChargeDist,m_sensor.generated_charge);
        
        m_cluster.getHitPosition(m_sensor.hit_position);
        m_cluster.FindClusterNumber();
      
        clus->Fill(fmod((m_cluster.m_hit_position)/pitch_size,3), m_cluster.cont);
    }
    cluster_canvas = new TCanvas("cluster_canvas","cluster",2500, 500);
    clus->Draw("colz");
    clus->ProfileX()->Draw("same");
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
const cluster* run_simulation::get_cluster(){
    return &m_cluster;
}

