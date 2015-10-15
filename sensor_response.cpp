
#include "sensor_response.h"
#include "Rtypes.h"


sensor_response::sensor_response() :fgauss(NULL) {
    
}

sensor_response::~sensor_response() {
    if (fgauss) {
        delete fgauss;
    }
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
        m_strip_position[i].x = i*m_pitch_size +m_min_strip*m_pitch_size;
        m_strip_position[i].y = 1;
    }
    
}

void sensor_response::init() {
    if (fgauss)
    {
        delete fgauss;
    }
    fgauss = new TF1("fgauss", "gaus", m_min_strip*m_pitch_size, m_max_strip*m_pitch_size);
}


Double_t sensor_response::charge_computation(Double_t strip_number, Double_t pitch){
    Double_t strip_int = fgauss->Integral(strip_number*pitch,(strip_number+1)*pitch);
    return strip_int;
}

TF1* sensor_response::get_fit() {
    return fgauss;
}

void sensor_response::ProcessEvent() {
    
    auto hit_position = (m_input_hit->x) * m_pitch_size;
    
    for(int i=0; i <m_strip_position.size(); i++) {
        
        
        fgauss->SetParameters(m_input_hit->charge, hit_position, m_sigma);
        m_strip_position[i].charge = charge_computation(i, m_pitch_size) ;
    }
    
    
}

const digitizer* sensor_response::get_digitizer() {
    return &m_digitizer;
}
