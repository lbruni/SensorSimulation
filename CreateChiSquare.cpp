

#include "CreateChiSquare.h"


Double_t CreateChiSquare::getDistributions(TProfile * sim, TProfile *data, Int_t nbin){
    m_chi = 0;
    for(Int_t j= 1 ; j<=nbin; j++){
        y = sim->GetBinContent(j);
        x = data->GetBinContent(j);
        diff = CreateChiSquare::getChiSquare(x,y);
        m_chi +=diff;
    std::cout<<"bin:  "<<j<<" sim:  "<<y<<"  data:  "<<x<<"  diff inside loop: "<<diff<<" m_chi inside loop:  "<<m_chi<<std::endl;
    }
    std::cout<<" m chi inside chisquare: "<<m_chi<<std::endl;
    return m_chi;
    
}

Double_t CreateChiSquare::getChiSquare(Double_t x, Double_t y){
    Double_t chisquare;
    chisquare = TMath::Power( (x - y), 2);
    return chisquare;
}

Double_t CreateChiSquare::get_chisquare() const {
    return m_chi;
}
