//
//  langaus.h
//  
//
//  Created by Lucrezia Stella Bruni on 06/10/15.
//
//

#ifndef ____langaus__
#define ____langaus__

#include <stdio.h>

class langaus{
    
public:
    langaus();
    ~langaus();
Double_t langaufun(Double_t *x, Double_t *par);
Double_t langaufunNeg(Double_t *x, Double_t *par);
TF1 *langaufit(TH1F *his, Double_t *fitrange, Double_t *startvalues, Double_t *parlimitslo, Double_t *parlimitshi, Double_t *fitparams, Double_t *fiterrors, Double_t *ChiSqr, Int_t *NDF);

Int_t langaupro(Double_t *params, Double_t &maxx, Double_t &FWHM);
    
private:
};
#endif /* defined(____lanngaus__) */
