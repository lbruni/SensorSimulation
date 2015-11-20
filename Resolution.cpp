
#include "Resolution.h"
void Resolution::set_intput_pointer(const std::vector<hit_with_charge>* input_pointer) {
    m_Input_hit = input_pointer;
}
void Resolution::Gaussian_random(){
    
    rGauss = new TRandom2();
    rGauss->SetSeed(0);
    
}
void Resolution::processEvent(){
    
    m_hit.clear();
    
    m_charge_resolution.resize( m_Input_hit->size());
   
    
    for (size_t i = 0; i < m_Input_hit->size();++i){
                
        charge_res.x = rGauss->Gaus(m_Input_hit->at(i).x, 0.01);
        charge_res.y = m_Input_hit->at(i).y;
        charge_res.charge= m_Input_hit->at(i).charge;
        
        m_hit.push_back(charge_res);
        
        m_charge_resolution[i].x = charge_res.x;
        m_charge_resolution[i].charge = charge_res.charge;
        
        
        //std::cout<<"Charge: "<<m_Input_hit->at(i).charge<<"   x:  "<<m_Input_hit->at(i).x<<"   x_new :  "<<m_charge_resolution[i].x<<" Diff: "<< m_Input_hit->at(i).x - m_charge_resolution[i].x<<std::endl;
        
    }
    
}

const std::vector<hit_with_charge>* Resolution::get_hit_ptr() const {
    return &m_hit;
}
