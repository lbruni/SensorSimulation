
#include "sensor_response.h"
#include "Rtypes.h"



Double_t errf(Double_t x, Double_t mean__, Double_t sigma__) {

  return  0.5*(1 + TMath::Erf((x - mean__) / (sigma__*TMath::Sqrt(2))));
}


sensor_response::sensor_response()  {
    
}

sensor_response::~sensor_response() {

}

void sensor_response::set_input(const hit_with_charge* inputHits) {
    m_input_hit = inputHits;
}
void sensor_response::set_pitch_size(Double_t pitch_size){
    m_pitch_size = pitch_size;
}
void sensor_response::set_charge_sharing(Double_t sigma){
    m_sigma = sigma;
}

const std::vector<hit_with_charge>* sensor_response::get_hit_ptr() {
    return &m_strip_position;
}

void sensor_response::strips(Int_t min_strip, Int_t max_strip) {
    m_max_strip = max_strip;
    m_min_strip = min_strip;
    auto number_of_strips = (max_strip - min_strip);
    m_strip_position.resize(number_of_strips);
    
    for (int i = 0; i <number_of_strips; ++i) {
        m_strip_position[i].x = i +m_min_strip;
        m_strip_position[i].y = 1;
    }

}

void sensor_response::init() {

}


Double_t sensor_response::charge_computation(Double_t strip_number){
  Double_t strip_int = errf(strip_number+1, m_input_hit->x, m_sigma) - errf(strip_number, m_input_hit->x, m_sigma) ;
    return strip_int;
}



void sensor_response::ProcessEvent() {
    
    auto hit_position = (m_input_hit->x);

    
    for(int i=0; i <m_strip_position.size(); i++) {
      
      m_strip_position[i].charge = m_input_hit->charge*charge_computation(i);
    }
   
}

const digitizer* sensor_response::get_digitizer() {
    return &m_digitizer;
}
