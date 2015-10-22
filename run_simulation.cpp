

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
    
    TFile *_file0 = TFile::Open("landau.root");
    f = (TF1*)_file0->Get("land");
    _file0->Close();
    
    
}

void run_simulation::get_clusterStrip_histo() {
    
    TFile *_file1 = TFile::Open("FakeData.root");
    clus_data = (TH2D*)_file1->Get("clus");
    
}
void run_simulation::init() {
    
    run_simulation::get_landau();
    
    m_hitmaker.set_charge_distribution(f);
    
    m_sensor.set_pitch_size(pitch_size);
    m_sensor.set_input(m_hitmaker.get_hit_ptr());
    run_simulation::Strips_under_study(0, 99);
    m_sensor.set_charge_sharing(sigma);
    m_sensor.init();
    
    
    m_analog.set_digits(0.01, 10, 128);
    m_analog.set_preAmplifier(95);
    m_analog.set_intput_pointer(m_sensor.get_hit_ptr());
    threshold = 70;
    m_binary.set_digits(threshold, threshold, 2);
    m_binary.set_preAmplifier(95);
    m_binary.set_intput_pointer(m_sensor.get_hit_ptr());
    
    gSystem->MakeDirectory(folder_name);
    
    m_cluster.set_intput_pointer_digitizer(m_binary.digitizer::get_hit_ptr());
}

void run_simulation::loop(Int_t numberOfEvents) {
    
    //*** Declaration of histos on cluster size vs strip number/charge ***
    clus_sim= new TH2D("clus_sim","Cluster size vs instrip position", 120, 0, 3 ,10 , -0.5, 9.5);
    
    Int_t nullclusters = 0;
    
    for (Int_t i = 0; i < numberOfEvents; ++i) {
        
        
        m_hitmaker.ProcessEvent();
        m_sensor.ProcessEvent();
        // m_analog.processEvent();
        m_binary.processEvent();
        m_cluster.processEvent();
        
        
        inStrip = fmod( (m_sensor.hit_position)/pitch_size,3);
        clusterSize = m_cluster.get_cluster_ptr()->cluster_size;
        
        
        if ( m_cluster.get_cluster_ptr()->cluster_size != 0){
            clus_sim->Fill(inStrip, clusterSize);
        }
        
        processEvent();
        
        if(m_cluster.get_cluster_size() == 0){
            nullclusters++;
        }
    }
    
    
    
    Efficiency =  run_simulation::calculateEfficiency(numberOfEvents, nullclusters);
    Efficiency_err =  run_simulation::calculateErrorEfficiency(numberOfEvents, Efficiency);
    std::cout<<" Threshold: "<< threshold <<" Efficiency:  "<<Efficiency<<" Efficiency Error:  "<<Efficiency_err<<std::endl;
    
    
    run_simulation::get_clusterStrip_histo();
    
    
    tpf_sim = clus_sim->ProfileX("tpf_sim",0,3);
    tpf_data =clus_data->ProfileX("tpf_data",0,3);
    
    ChiSquare = m_chisquare.getDistributions(tpf_sim,tpf_data,120);
    
    std::cout<<"chi square: "<<ChiSquare<<std::endl;
    
    
}


//*** Loop on sigma-- Fills an histo of cluster size vs sigma***
void run_simulation::LoopOnSigma() {
    
    const double min_sigma = 0.0001,max_sigma = 0.1;
    
    sigma = min_sigma;
    
    m_sigma_cluster = new TH2D("sigma_cluster", "", 40, min_sigma, max_sigma, 10, 0.0, 9);
    for (; sigma <= 0.1; sigma += min_sigma) {
        
        
        std::cout<<" Sigma: "<<sigma<<std::endl;
        
        run_simulation::init();
        run_simulation::loop(1000);
        
        
        
    }
    m_sigma_cluster->GetXaxis()->SetTitle("sigma [mm]");
    m_sigma_cluster->GetYaxis()->SetTitle("cluster size");
    m_sigma_cluster->Draw("colz");
    auto pro= m_sigma_cluster->ProfileX();
    pro->Draw("same");
}


void run_simulation::LoopOnSigmaChiSquare() {
    
    const double min_sigma = 0.001,max_sigma = 0.1;
    
    sigma = min_sigma;
    
    m_sigma_chi = new TH2D("m_sigma_chi", "", 100, min_sigma, max_sigma, 100, 0.0, 400.0);
    
    
    for (; sigma <= 0.1; sigma += min_sigma) {
        
        
        run_simulation::init();
        run_simulation::loop(10000);
    }
    
    m_sigma_chi->GetXaxis()->SetTitle("sigma [mm]");
    m_sigma_chi->GetYaxis()->SetTitle("#chi^{2}");
    m_sigma_chi_pfx = m_sigma_chi->ProfileX("m_sigma_chi_pfx",0,400);
    TCanvas *c3 = new TCanvas("c3","",500,500);
    m_sigma_chi->Draw("colz");
    m_sigma_chi_pfx->Draw("same");
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
    m_scan =  new TGraphErrors(16);
    
    Double_t thres[16] = {   67.6,
        109.8,
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
        555.9,
        572.4,
        584.6};
    
    for (int i = 0 ; i<16; i++){
        threshold = thres[i];
        run_simulation::init();
        run_simulation::loop(1);
        m_scan->SetPoint(i, thres[i], Efficiency);
        m_scan->SetPointError(i,0,Efficiency_err);
    }
    
    scan = new TCanvas("scan", "",500,500);
    m_scan->GetXaxis()->SetTitle("Threshold [mV]");
    m_scan->GetYaxis()->SetTitle("Efficiency");
    m_scan->SetTitle("Efficiency vs Threshold");
    
    TF1 *sCurve = new TF1("sCurve", "([0]/2)*(1-TMath::Erf([1]*(x-[2])/TMath::Sqrt2()))",0, 600);
    sCurve->SetParameter(0, 1);
    //sCurve->Draw();
    
    m_scan->Draw("AP");
    m_scan->Write();
    m_scan->Fit("sCurve","WW");
    scan->SaveAs("Scurve.pdf");
    
    TFile *_file1 = TFile::Open("Scurve_Save.root","RECREATE");
    m_scan->Write();
    //_file1->Close();
}

void run_cluster_size_simulation::processEvent() {
    //      m_sigma_cluster->Fill(sigma, m_cluster.get_cluster_size());
    std::cout<<" sigma:   :"<<sigma<<" chi:  "<<ChiSquare<<std::endl;
    m_sigma_chi->Fill(sigma, ChiSquare );
}