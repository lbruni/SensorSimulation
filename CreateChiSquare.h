//
//  CreateChiSquare.h
//
//
//  Created by Lucrezia Stella Bruni on 20/10/15.
//
//

#ifndef ____CreateChiSquare__
#define ____CreateChiSquare__

#include <stdio.h>


class CreateChiSquare{
    
public:
    Double_t getDistributions(TProfile * sim, TProfile *data, Int_t nbin);
    Double_t getChiSquare(Double_t x, Double_t y);
    Double_t get_chisquare() const;
    
    
private:
    Double_t m_chi, diff;
    Double_t sum;
    Double_t x,y;
    
};
#endif /* defined(____CreateChiSquare__) */
