
#include "hist2DMaker.h"
#include "TSystem.h"

TH2D *hist2DMaker::histMake (Int_t strip_min, Int_t strip_max, Double_t pitch_size, std::vector<hit_with_charge> m_strip_position) {
    
    hist = new TH2D("hist", "Charge density ", m_strip_position.size(), (strip_min*pitch_size), (strip_max*pitch_size), 1, 0, 1);
    hist->GetXaxis()->SetTitle("position [mm]");
    hist->GetYaxis()->SetTitle("Charge density / strip");
    
    
    
    for(int j = 0; j<m_strip_position.size(); j++){
        
        hist->Fill(m_strip_position[j].x+pitch_size*0.5,0.5,m_strip_position[j].charge);
    }
    return hist;
    
}



void hist2DMaker::histDrawAndSave (TH2D* hist0, Int_t i, Double_t pitch_size) {
    
    gSystem->MakeDirectory(Form("%s/hit%d",folder_name,i));
    
    
    if (c1)
    {
        delete c1;
    }
    c1= new TCanvas("c1", "hit",1200,600);
    c1 -> Divide(1,2);
    
    c1->cd(1);
    
    TLine l;
    hist0->Draw("colz P");
    gStyle->SetOptStat(0);
    c1->Update();
    l.SetLineStyle(1);
    int nbins=hist0->GetNbinsX();
    for( int bin = 1; bin<=nbins ;bin++){l.DrawLine((bin*pitch_size) ,0, (bin*pitch_size),1);}
    
    c1->cd(2);
    
    TH1D *hist0_ProjX = hist0->ProjectionX();
    hist0_ProjX->SetTitle(Form("Charge density (1D)"));
    hist0_ProjX->GetXaxis()->SetTitle("position [mm]");
    hist0_ProjX->GetYaxis()->SetTitle("Charge density / strip");
    hist0_ProjX->Draw("hist"); //what should the errors be?
    //fgauss->Draw("same");
    
    c1->SaveAs(Form("%s/hit%d/vary.pdf",folder_name,i));
    c1->SaveAs(Form("%s/hit%d/vary.C",folder_name,i));
}
