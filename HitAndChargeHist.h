

#ifndef ____HitAndChargeHist__
#define ____HitAndChargeHist__

#include <stdio.h>


class HitAndChargeHist{
public:
    TH1D *histChargeDist();
    TH1D *histHitDist();
    TH1D *FillHisto(TH1D*h, Double_t var);
    void histDrawAndSave (TH1D* hist0, TH1D* hist1);
    
private:
    
    TH1D *hist0;
    TH1D *hist1;
    TCanvas *c1;
    
    
    
    
    
};

#endif /* defined(____HitAndChargeHist__) */
