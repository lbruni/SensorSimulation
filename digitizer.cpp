

#include "digitizer.h"
#define nChannels_Analog 128
#define nChannels_Binary 2
#define Charge_min 0
#define Charge_max 1

Double_t digitizer::preAmplifier(Double_t chargefC){
    Double_t chargemV;
    chargemV = 95.0 * chargefC;
    std::cout<< " charge [fC]:  "<<chargefC<<" charge [mV]:  "<<chargemV<<std::endl;
    return chargemV;
}

void digitizer::AnalogReadout( std::vector<hit_with_charge> m_strip_position){
   
    canvas = new TCanvas("canvas","canvas",500,500);
    analog = new TH2D("analog","analog", 100 ,0, 7.32600 , 128 ,0, 1);
    
    for(int i=0; i <m_strip_position.size(); i++){
        
        if (m_strip_position[i].charge > 0.00005 && m_strip_position[i].charge< 1 ) {
            
            analog->Fill(m_strip_position[i].x,m_strip_position[i].charge);
        }
    }
    TH1D *hist0_ProjX = analog->ProjectionY();
    analog->Draw("colz");
}

void digitizer::BinaryReadout(std::vector<hit_with_charge> m_strip_position){
    
    canvas1 = new TCanvas("canvas1","canvas1",500,500);
    binary = new TH2D("binary","binary",100,0,7.32600, 2,0,1);
    
    for(int i=0; i <m_strip_position.size(); i++){
        
        if (m_strip_position[i].charge > 0.00005 && m_strip_position[i].charge< 1 ) {
            
            binary->Fill(m_strip_position[i].x,m_strip_position[i].charge);
        }
        binary->Draw("colz ");
    }
}
