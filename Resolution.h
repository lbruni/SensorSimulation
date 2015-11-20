
#ifndef ____Resolution__
#define ____Resolution__

#include <stdio.h>


class Resolution{
public:
    
    void set_intput_pointer(const std::vector<hit_with_charge>* input_pointer);
    void processEvent();
    Double_t Gaussian_random(Double_t x);
    const std::vector<hit_with_charge>* get_hit_ptr() const;
    
    std::vector<hit_with_charge> m_charge_resolution;
    hit_with_charge charge_res ;


private:
    std::vector<hit_with_charge> m_hit;
     const std::vector<hit_with_charge>* m_Input_hit;

};

#endif /* defined(____Resolution__) */
