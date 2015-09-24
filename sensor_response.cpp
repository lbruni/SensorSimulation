//
//  sensor_response.cpp
//
//
//  Created by Lucrezia Stella Bruni on 21/09/15.
//
//

#include "sensor_response.h"
#include "Rtypes.h"


void sensor_response::set_input(const hit_with_charge* inputHits){
    m_input_hit = inputHits;
}
void sensor_response::set_pitch_size(Double_t pitch_size){
    m_pitch_size = pitch_size;
}
void sensor_response::set_charge_sharing(Double_t sigma){
    m_sigma = sigma;
}
void sensor_response::strips(Int_t min_strip, Int_t max_strip) {
    
       number_of_strips = (max_strip - min_strip);
    m_strip_position.resize(number_of_strips);
    
    for (int i = min_strip; i <= max_strip; ++i) {
        strip_position = i*m_pitch_size;
        m_strip_position[i].x = strip_position;
        m_strip_position[i].y = 1;
    }
}
TF1* sensor_response::GenChargeDistX(Double_t strips_pos) {
    TF1 *fGauss = new TF1("fgauss","gausn",0,strips_pos);
    return fGauss;
}
Double_t sensor_response::charge_computation(Double_t strip_number, Double_t pitch, TF1 *fgauss){
    Double_t strip_int = fgauss->Integral(strip_number*pitch,(strip_number+1)*pitch);
    return strip_int;
}
void sensor_response::ProcessEvent() {
    
    hit_position = (m_input_hit->x) * m_pitch_size;
    generated_charge = m_input_hit->charge;
    
    for(int i=0; i <=m_strip_position.size(); i++) {
        
        
        fgauss = sensor_response::GenChargeDistX(number_of_strips*m_pitch_size);
        fgauss->SetParameters(1, hit_position,m_sigma);
        
        m_strip_position[i].charge = sensor_response::charge_computation(i, m_pitch_size, fgauss) ;
        strip_int = m_strip_position[i].charge;
        
      // std::cout<<"  strip:  "<<i<<"   x: "<<m_strip_position[i].x<<" hit position "<<hit_position<<"   charge:   "<<strip_int<<std::endl;
    }
}
