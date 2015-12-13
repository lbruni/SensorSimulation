//
//  addPedestal.cpp
//  
//
//  Created by Lucrezia Stella Bruni on 13/12/15.
//
//

#include "addPedestal.h"
void addPedestal::set_intput_pointer(const std::vector<hit_with_charge>* input_pointer) {
    m_strip = input_pointer;
}
void addPedestal::set_pedestal_value(Double_t pedestal){
    
    m_pedestal = pedestal;
}
void addPedestal::ProcessEvent(){
    
    m_strip_position_with_pedestal.resize(m_strip->size());
    
    for(int k=0; k <m_strip->size(); k++) {
        
        m_strip_position_with_pedestal[k].x = m_strip->at(k).x  ;
        m_strip_position_with_pedestal[k].y  = m_strip->at(k).y  ;
        m_strip_position_with_pedestal[k].charge =m_strip->at(k).charge+m_pedestal;
   
        //std::cout<<" input :"<<m_strip->at(k).charge<<" ouput:  "<<m_strip_position_with_pedestal[k].charge<<" diff =  "<<m_strip_position_with_pedestal[k].charge - m_strip->at(k).charge<<std::endl;
    
    }
}
const std::vector<hit_with_charge>* addPedestal::get_hit_ptr() {
    return &m_strip_position_with_pedestal;
}
