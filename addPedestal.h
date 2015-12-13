//
//  addPedestal.h
//  
//
//  Created by Lucrezia Stella Bruni on 13/12/15.
//
//

#ifndef ____addPedestal__
#define ____addPedestal__

#include <stdio.h>
class addPedestal{
public:
    void set_intput_pointer(const std::vector<hit_with_charge>* input_pointer);
    void set_pedestal_value(Double_t pedestal);
    void ProcessEvent();
    const std::vector<hit_with_charge>* get_hit_ptr();
    
private:
    Double_t m_pedestal;
    const std::vector<hit_with_charge>* m_strip;
    std::vector<hit_with_charge> m_strip_position_with_pedestal;
};
#endif /* defined(____addPedestal__) */
