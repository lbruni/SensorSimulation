

#include "TSystem.h"
#include "TH1D.h"
#include "TProfile.h"
#include "run_simulation.h"

void run_simulation::Strips_under_study(Int_t min_strip, Int_t max_strip) {
    
    m_hitmaker.set_strips(min_strip, max_strip);
    m_sensor.strips(min_strip, max_strip);
    m_strip_min = min_strip;
    m_strip_max = max_strip;
    
}
void run_simulation::get_landau() {
    
    TFile *_file0 = TFile::Open("landau_400.root");
    f = (TF1*)_file0->Get("land");
   
    _file0->Close();
    
    
}

void run_simulation::get_clusterStrip_histo() {
    
    TFile *_file01 = TFile::Open("Histo_816.root");
    clus_data = (TH1D*)_file01->Get("cluster");
    
    
}
void run_simulation::openfiles(){
    run_simulation::get_landau();
    m_hitmaker.set_charge_distribution(f);
    run_simulation::get_clusterStrip_histo();
    m_chisquare.GetDataHisto(clus_data);
    
}
void run_simulation::init() {
    
    
    m_sensor.set_pitch_size(pitch_size);
    m_sensor.set_input(m_hitmaker.get_hit_ptr());
    run_simulation::Strips_under_study(0, 99);
    m_sensor.set_charge_sharing(sigma);
    m_sensor.init();
    
    
   
    m_analog.set_digits(0.01, 10, 128);
    m_analog.set_preAmplifier(95 , 0.03);
    m_analog.set_intput_pointer(m_sensor.get_hit_ptr());
    //threshold = 67.572;//109.8;//193.2;//151.636;//67.572;//////70;
    
    m_binary.set_digits(threshold, threshold, 2);
    m_binary.set_preAmplifier(95 , 0.00);
    
    m_cross.set_intput_pointer(m_sensor.get_hit_ptr());
    m_pedestal.set_pedestal_value(0.54);
    m_pedestal.set_intput_pointer(m_cross.get_hit_ptr());
    
    
    m_binary.set_intput_pointer(m_pedestal.get_hit_ptr());
    
    run_simulation::Gaussian_random();
    
    gSystem->MakeDirectory(folder_name);
    
    m_cluster.set_intput_pointer_digitizer(m_binary.digitizer::get_hit_ptr());
    
}

void run_simulation::loop(Int_t numberOfEvents) {
    
    //***Histograms below are done to check if the Hits and Charge are well generated
    //***See class HitAndChargeHist
    
    //*** Declaration of histos on cluster size vs strip number/charge ***
    clus_sim= new TH2D("clus_sim","Cluster size vs instrip position", 100, 0, 3 ,10 , -0.5, 9.5);
       Int_t nullclusters = 0;
    
    
    ofstream writefile;
    writefile.open("SigmaClusterSize.txt");
    
    for (Int_t i = 0; i < numberOfEvents; ++i) {
        
        
        m_hitmaker.ProcessEvent();
        m_sensor.ProcessEvent();
        m_cross.ProcessEvent();
        m_pedestal.ProcessEvent();
        // m_analog.processEvent();
        m_binary.processEvent();
        m_cluster.processEvent();
       
        
        x_res_eff =run_simulation::GaussRan(m_sensor.hit_position);

        
        
        inStrip = fmod( x_res_eff/pitch_size,3);
        clusterSize = m_cluster.get_cluster_ptr()->cluster_size;
        
       
        if ( clusterSize != 0 ){
            clus_sim->Fill(inStrip, clusterSize);
            writefile<<" "<<inStrip<<" "<<clusterSize<<" "<<std::endl;
        }

        else{
            nullclusters++; }
        if(numberOfEvents>1){
    
        }
       
    }

    
    
    
        Efficiency =  run_simulation::calculateEfficiency(numberOfEvents, nullclusters);
        Efficiency_err =  run_simulation::calculateErrorEfficiency(numberOfEvents, Efficiency);
       std::cout<<" Threshold: "<< threshold <<" Efficiency:  "<<Efficiency<<" Efficiency Error:  "<<Efficiency_err<<std::endl;
        
    
    
        tpf_sim = clus_sim->ProfileX("tpf_sim",0,3);
  
  //  TCanvas *c = new TCanvas("c","", 700,500);
    
//    TLegend* l = new TLegend(0.1,0.7,0.48,0.9);
//    tpf_sim->SetMaximum(5);
//    tpf_sim->SetMinimum(-1);
//    tpf_sim->Draw();
//    tpf_sim->GetYaxis()->SetTitle("Cluster size");
//    tpf_sim->GetXaxis()->SetTitle("Instrip position");
//    clus_data->SetLineColor(2);
    
    //clus_data->Draw("same");
       //     l->AddEntry(tpf_sim,"simulation","l");
            //l->AddEntry(clus_sim),"data run 816 - THL = 70 mV","l");
    //        l->Draw("same");
//
   ChiSquare = m_chisquare.getDistributions(tpf_sim,100);
//TFile *pluto = new TFile("Cluster_sim.root","RECREATE");
//    tpf_sim->Write();
//    pluto->Close();
        delete clus_sim;
//
    
}


//*** Loop on sigma-- Fills an histo of cluster size vs sigma***
void run_simulation::LoopOnSigma() {
    
    const double min_sigma = 0.0001,max_sigma = 0.1;
    
    sigma = min_sigma;
    
    m_sigma_cluster = new TH2D("sigma_cluster", "", 40, min_sigma, max_sigma, 10, 0.0, 9);
    for (; sigma <= 0.1; sigma += min_sigma) {
        
        
        std::cout<<" Sigma: "<<sigma<<std::endl;
        
        run_simulation::init();
        run_simulation::loop(1);
        
        
        
    }
    m_sigma_cluster->GetXaxis()->SetTitle("sigma [mm]");
    m_sigma_cluster->GetYaxis()->SetTitle("cluster size");
    m_sigma_cluster->Draw("colz");
    auto pro= m_sigma_cluster->ProfileX();
    pro->Draw("same");
}


void run_simulation::LoopOnSigmaChiSquare() {
    
    m_sigma_chi = new TH2D("m_sigma_chi", "",100,0,0.037, 100,0,15);
    run_simulation::openfiles();
    
    for (int k=0; k<200; k++) {
        sigma = pitch_size * (0.0025*k);
        
        //for (int k=0; k<600; k++) {
        
        //  sigma = pitch_size * (0.005*k);
        
        run_simulation::init();
        run_simulation::loop(60000);
        
        m_sigma_chi->Fill(sigma, ChiSquare );
        std::cout<<"sigma:   "<<sigma<<"chi:  "<<ChiSquare<<std::endl;
    }
    m_sigma_chi->GetXaxis()->SetTitle("#sigma [mm]");
    m_sigma_chi->GetYaxis()->SetTitle("#chi^{2}");
    m_sigma_chi_pfx = m_sigma_chi->ProfileX("m_sigma_chi_pfx",15);
    
    TPaveText *pt2 = new TPaveText(0.04,9.2,0.07,30);
    TText *t2;
    
    TCanvas *c4 = new TCanvas("c4","",800,500);
    m_sigma_chi->Draw("colz");
    m_sigma_chi_pfx->Draw("same");
    
    TF1 *f = new TF1("f","pol4",0,0.037);
    m_sigma_chi_pfx->Fit("f");
    char tmp1[50];
    sprintf(tmp1,"Run 00816: #chi^{2} min for #sigma = %f",f->GetX(f->GetMinimum()));
    t2 = pt2->AddText(tmp1);
    pt2->SetFillColor(0);
    pt2->Draw();
    std::cout<<"minimo:   "<< f->GetX(f->GetMinimum())<<std::endl;
    m_sigma_chi->SetStats(0);
    c4->SaveAs("ChiSquare_sigma816.root");
    c4->SaveAs("ChiSquare_sigma816.pdf");
}


Double_t run_simulation::calculateEfficiency(Double_t n_events, Double_t n_null_clusters){
    Double_t eff;
    eff = 1-(n_null_clusters / n_events);
    return eff;
}
Double_t run_simulation::calculateErrorEfficiency(Double_t n_events, Double_t eff){
    Double_t eff_err;
    eff_err = sqrt(eff*(1-eff)*(1/n_events));
    
    return eff_err;
}


void run_simulation::run_efficiency(){
    m_scan =  new TGraphErrors(17);
    
    Double_t thres[17] = { 44.0,
        67.6,
        90.0,
        109.8,
        130.0,
        151.7,
        193.2,
        234.6,
        275.9,
        289.6,
        357.8,
        397.8,
        435.8,
        471.2,
        504.0,
        533.1,
        549.0,
        };
    
    for (int i = 0 ; i<17; i++){
        threshold = thres[i];
        run_simulation::openfiles();
        run_simulation::init();
        run_simulation::loop(50000);
        m_scan->SetPoint(i, thres[i], Efficiency);
        m_scan->SetPointError(i,0,Efficiency_err);
    }
    
    scan = new TCanvas("scan", "",500,500);
    m_scan->GetXaxis()->SetTitle("Threshold [mV]");
    m_scan->GetYaxis()->SetTitle("Efficiency");
    m_scan->SetTitle("Efficiency vs Threshold");
//    
//    TF1 *sCurve = new TF1("sCurve", "([0]/2)*(1+TMath::Erf([1]*(x-[2])/TMath::Sqrt2()))",0, 650);
//    sCurve->SetParameter(0, 1);
//    sCurve->Draw();
    
    m_scan->Draw("AP");
    m_scan->Write();
    //m_scan->Fit("sCurve","");
    scan->SaveAs("Scurve.pdf");
    
    TFile *_file1 = TFile::Open("Scurve_Save.root","RECREATE");
    m_scan->Write();
    _file1->Close();
}

//void run_cluster_size_simulation::processEvent() {
//    //      m_sigma_cluster->Fill(sigma, m_cluster.get_cluster_size());
//    std::cout<<" sigma:   :"<<sigma<<" chi:  "<<ChiSquare<<std::endl;
//    m_sigma_chi->Fill(sigma, ChiSquare );
//}



void run_simulation::Gaussian_random(){
    
    rgauss = new TRandom2();
    rgauss->SetSeed(0);
    
}
Double_t run_simulation::GaussRan(Double_t hit){
    Double_t hit_newfT;
    
    hit_new =  rgauss->Gaus(hit, 0.012);
    return hit_new;
}
