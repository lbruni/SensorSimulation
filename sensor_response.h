
#ifndef ____sensor_response__
#define ____sensor_response__

#include <stdio.h>
#include "hitGenerator.cpp"
#include "digitizer.cpp"

class sensor_response {
public:
    //Stage area
    sensor_response();
    ~sensor_response();
    void set_input(const hit_with_charge* inputHits);
    void set_pitch_size(Double_t pitch_size);
    void set_charge_sharing(Double_t sigma);
    const std::vector<hit_with_charge>* get_hit_ptr();
    void strips(Int_t min_strip, Int_t max_strip);
    void init();
    void ProcessEvent();
    Double_t hit_position;
    Double_t strip_int;
    Double_t generated_charge;
    Double_t pos_x;
     
    Double_t charge_computation(Double_t strip_number);

    
private:
    std::vector<hit_with_charge> m_strip_position;
    
    Int_t m_max_strip;
    Int_t m_min_strip;
    
    Double_t m_pitch_size;
    Double_t m_sigma;
    
    
    
    digitizer m_digitizer;
    
    
    std::vector<hit_with_charge> m_hit;
    const hit_with_charge* m_input_hit =nullptr;
   
    const digitizer* get_digitizer();
};

#endif /* defined(____sensor_response__) */
