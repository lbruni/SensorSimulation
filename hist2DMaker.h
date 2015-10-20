

#ifndef ____hist2DMaker__
#define ____hist2DMaker__

#include <stdio.h>

#define folder_name "plot"

class hist2DMaker {
public:
    hist2DMaker() :hist(NULL), c1(NULL) {}
    TH2D *histMake(Int_t strip_min, Int_t strip_max, Double_t pitch_size, const std::vector<hit_with_charge>* m_strip_position);
    
    void histDrawAndSave (TH2D* hist0, Int_t i, Double_t pitch_size);
private:
    
    TH2D *hist;
    TCanvas *c1;
    
    
    
    
    
};



#endif /* defined(____hist2DMaker__) */
