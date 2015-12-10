//
//  crosstalk.cpp
//  
//
//  Created by Lucrezia Stella Bruni on 09/12/15.
//
//

#include "crosstalk.h"




void crosstalk::set_intput_pointer(const std::vector<hit_with_charge>* input_pointer) {
    m_strip = input_pointer;
}

void crosstalk::ProcessEvent(){
    Double_t max =0 ;
    Int_t count = 0;
    max = m_strip->at(0).charge;
    m_strip_position_crosstalk.resize(m_strip->size());
    Double_t sum =0 ;
    Double_t sum_real = 0;
    Double_t scale_factor;
   
    for(int k=0; k <m_strip->size(); k++) {
        if ( m_strip->at(k).charge > 0){
           count++;
        }
        
        m_strip_position_crosstalk[k].x = m_strip->at(k).x  ;
        m_strip_position_crosstalk[k].y  = m_strip->at(k).y  ;
        
        
        if ( m_strip->at(k).charge > max){
            max =  m_strip->at(k).charge;
        }
        
        scale_factor =(max*0.01);
    
    }
    
    
     for(int i=0; i <m_strip->size(); i++) {
         
         if (m_strip->at(i).charge == max){
        m_strip_position_crosstalk[i].charge = max -(scale_factor) ;
        
        
        }
        else if ( m_strip->at(i).charge == 0){
            m_strip_position_crosstalk[i].charge = m_strip->at(i).charge ;
        }
        else {
            m_strip_position_crosstalk[i].charge = m_strip->at(i).charge+(scale_factor/(count -1 ));
        }

        sum += m_strip_position_crosstalk[i].charge;
        sum_real += m_strip->at(i).charge;
         std::cout<<"count  "<<count<<" sum  :"<<sum<<"  sum real "<<sum_real<<" cross talk: "<<m_strip_position_crosstalk[i].charge<<" real "<< m_strip->at(i).charge<<std::endl;
    }
}
const std::vector<hit_with_charge>* crosstalk::get_hit_ptr() {
    return &m_strip_position_crosstalk;
}
