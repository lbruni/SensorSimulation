//
//  hitGenerator.cpp
//  
//
//  Created by Lucrezia Stella Bruni on 18/09/15.
//
//

#include "hitGenerator.h"
#include "hit_with_charge.h"



void hitGenerator::set_strips (Int_t a, Int_t b) {
    
    if ( (a < b) && ( a >=0 && a< 100) && (b >= 0 && b < 100) ){
        start = a;
        end = b;
        rLinear = new TRandom2();
        rLinear->SetSeed(0); //initialize the seed (0 sets it differently every time)
    }
    else{std::cout<<"Error! Invalid strip number"<<std::endl;}
}


void hitGenerator::set_charge (Double_t mpv, Double_t st_dev) {
    if( mpv > 0 && st_dev > 0){
        mu = mpv;
        sigma = st_dev;
        rGauss = new TRandom2();
        rGauss->SetSeed(0); //initialize the seed (0 sets it differently every time)
    }
    else{std::cout<<"Error! Invalid mpv/st_dev"<<std::endl;}
}


void hitGenerator::ProcessEvent() {
    
    m_hit.charge = rGauss->Gaus(mu, sigma);
    generated_charge = m_hit.charge;
    
    m_hit.x= rLinear->Uniform(start, end);
    x_position  = m_hit.x ;
    
}


const hit_with_charge* hitGenerator::get_hit_ptr() {
    return &m_hit;
}


