

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
    threshold = 207.055;
  m_binary.set_digits(threshold, threshold, 2);
  m_binary.set_preAmplifier(95);
  m_binary.set_intput_pointer(m_sensor.get_hit_ptr());

  gSystem->MakeDirectory(folder_name);

  m_cluster.set_intput_pointer_digitizer(m_binary.digitizer::get_hit_ptr());
}

void run_simulation::loop(Int_t numberOfEvents) {

  //*** Histograms below are done to check if hits and Charge are well generated***
//  hitDist = m_HitAndChargeHist.histHitDist();
//  ChargeDist = m_HitAndChargeHist.histChargeDist();

  //*** Declaration of histos on cluster size vs strip number/charge ***
 clus= new TH2D("clus","h2", 120, 0, 3 ,10 , 0, 10);
//   clus2= new TH2D("clus2","h22", 7, 0,7, 5, 0, 5);
//   
    Int_t nullclusters = 0;
    
    
  for (Int_t i = 0; i < numberOfEvents; ++i) {


    m_hitmaker.ProcessEvent();
    m_sensor.ProcessEvent();
   // m_analog.processEvent();
    m_binary.processEvent();
     
      
     
    //*** hit and cloud charge histograms ***
    // hist = m_hist2DMaker.histMake(m_strip_min, m_strip_max, pitch_size, m_sensor.get_hit_ptr());
    // m_hist2DMaker.histDrawAndSave(hist, i, pitch_size);
   // new TCanvas;
   // hist->ProjectionX()->Draw();
     
      
      //**Histogram of the generated hit position and charge
//     m_HitAndChargeHist.FillHisto(hitDist,m_sensor.hit_position);
//      m_HitAndChargeHist.FillHisto(ChargeDist,m_sensor.generated_charge);

    //**cluster studies
    m_cluster.processEvent();

    std::cout<<" get Cluster size:  "<<m_cluster.get_cluster_size()<<"  sigma:  "<<sigma<<std::endl;
      
      
      if(m_cluster.get_cluster_size() == 0){
          nullclusters++;
      }
    
        clus->Fill(fmod( (m_sensor.hit_position)/pitch_size,3), m_cluster.get_cluster_ptr()->cluster_size);
      
    
      //*** Fill of histos on cluster size vs strip number/charge ***
      //clus2->Fill(m_sensor.strip_int, m_cluster.get_cluster_ptr()->cluster_size);
      // processEvent();
      
    
  }


    
    Efficiency =  run_simulation::calculateEfficiency(numberOfEvents, nullclusters);
    Efficiency_err =  run_simulation::calculateErrorEfficiency(numberOfEvents, Efficiency);
    std::cout<<" Threshold: "<< threshold <<" Efficiency:  "<<Efficiency<<" Efficiency Error:  "<<Efficiency_err<<std::endl;
    //std::cout<<"Efficiency:   "<<Efficiency<<" Cluster zero: "<<nullclusters<<std::endl;
    

  //*** Draw histos on cluster size vs strip number/charge ***
          cluster_canvas = new TCanvas("cluster_canvas","cluster",3000, 500);
          cluster_canvas->Divide(2,1);
//          cluster_canvas->cd(1);
          clus->GetXaxis()->SetTitle("strip position");
          clus->GetYaxis()->SetTitle("cluster size");
          clus->Draw("colz");
          clus->ProfileX()->Draw("same");
//          cluster_canvas->cd(2);
//          clus2->GetXaxis()->SetTitle("Charge (fC)");
//          clus2->GetYaxis()->SetTitle("cluster size");
//          clus2->Draw("colz");
//          clus2->ProfileX()->Draw("same");
  
  //
  //*** Draw hit and cloud charge histograms ***
  // m_HitAndChargeHist.histDrawAndSave(hitDist,ChargeDist);
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


Double_t run_simulation::calculateEfficiency(Double_t n_events, Double_t n_null_clusters){
    Double_t eff;
    eff = 1-(n_null_clusters / n_events);

   // std::cout<<" null clusters:  "<<n_null_clusters<<" n_events  "<<n_events<<" eff:  "<<eff<< std::endl;
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
        run_simulation::loop(2000);
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
//void run_cluster_size_simulation::processEvent() {
//      m_sigma_cluster->Fill(sigma, m_cluster.get_cluster_size());
//}
