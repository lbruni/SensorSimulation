

#include "hitGenerator.h"
#include "hit_with_charge.h"
#include "TRandom2.h"



void hitGenerator::set_strips (Int_t a, Int_t b) {
    
    if ( (a < b) && ( a >=0 && a< 100) && (b >= 0 && b < 100) ){
        start = a;
        end = b;
        rLinear = new TRandom2();
        rLinear->SetSeed(0); //initialize the seed (0 sets it differently every time)
    }
    else{std::cout<<"Error! Invalid strip number"<<std::endl;}
}


void hitGenerator::set_charge_distribution(TF1 *f) {
  gRandom->SetSeed(0);
  m_charge_dist = f;
}



void hitGenerator::ProcessEvent() {
    
    m_hit.charge = m_charge_dist->GetRandom();
       
    m_hit.x= rLinear->Uniform(start, end);
    
}


const hit_with_charge* hitGenerator::get_hit_ptr() {
    return &m_hit;
}


