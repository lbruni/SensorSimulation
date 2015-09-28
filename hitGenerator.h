

#ifndef ____hitGenerator__
#define ____hitGenerator__

#include "hit_with_charge.h"
#include <stdio.h>
#include "TCanvas.h"
#include <iostream>
#include "TGraph.h"
#include "TStyle.h"
#include "TH3.h"
#include "TH2.h"
#include "TH1.h"
#include "TGaxis.h"
#include "THistPainter.h"
#include "TLegend.h"
#include "TGraph.h"
#include "TFile.h"
#include "TAttMarker.h"
#include "TAttFill.h"
#include "TAttLine.h"
#include "TTree.h"
#include "TBranch.h"
#include "TMath.h"
#include "TAxis.h"
#include "TApplication.h"
#include <string>
#include <cmath>
#include <TGraph2D.h>
#include <TMultiGraph.h>
#include "TRandom2.h"


class hitGenerator {
public:
   
    void set_strips(Int_t a, Int_t b);
    void set_charge(Double_t mpv, Double_t st_dev);
    const hit_with_charge* get_hit_ptr();

    void ProcessEvent();
    
    TH1* get_position_distribution();
    TH1* get_charge_distribution();
    TH1D *hist;
    TCanvas *c1;
    Double_t x_position;
    Double_t generated_charge;

private:
    
    hit_with_charge m_hit;
    TRandom2 *rLinear;
    TRandom2 *rGauss;
    Double_t start;
    Double_t end;
    Double_t mu;
    Double_t sigma;
    
    
};



#endif
