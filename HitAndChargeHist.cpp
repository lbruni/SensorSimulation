

#include "HitAndChargeHist.h"

TH1D* HitAndChargeHist::histHitDist () {
    
    hist0 = new TH1D("hist0", "Hit ", 100,0,10);
    hist0->GetXaxis()->SetTitle("position [mm]");
    
    return hist0;
}

TH1D* HitAndChargeHist::histChargeDist () {
    
    hist0 = new TH1D("hist0", "Generated Charge ", 100,0,10);
    hist0->GetXaxis()->SetTitle("charge");
    
    
    return hist0;
}

TH1D* HitAndChargeHist::FillHisto(TH1D*h, Double_t var){
    h->Fill(var);
    return h;
}

void HitAndChargeHist::histDrawAndSave (TH1D* hist0, TH1D* hist1) {
    
    
    c1= new TCanvas("c1", "hit",1200,600);
    c1 -> Divide(1,2);
    
    c1->cd(1);
    hist0->Draw("");
    // gStyle->SetOptStat(0);
    
    c1->cd(2);
    
    hist1->Draw("");
    
    c1->SaveAs("dist.pdf");
    
}