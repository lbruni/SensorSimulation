
#include "run_simulation.h"
#include "TSystem.h"
#include "TH1D.h"
#include "TProfile.h"

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
  //f->SetParameters(0.224,3.543,240.635,0.462);
  // f->Draw();

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


  Double_t threshold = 1;
  m_binary.set_digits(threshold, threshold, 2);
  m_binary.set_preAmplifier(95);
  m_binary.set_intput_pointer(m_sensor.get_hit_ptr());

  gSystem->MakeDirectory(folder_name);

  m_cluster.set_intput_pointer_digitizer(m_binary.digitizer::get_hit_ptr());
}

void run_simulation::loop(Int_t numberOfEvents) {

  //*** Histograms below are done to check if hits and Charge are well generated***
  //hitDist = m_HitAndChargeHist.histHitDist();
  //ChargeDist = m_HitAndChargeHist.histChargeDist();

  //*** Declaration of histos on cluster size vs strip number/charge ***
  // clus= new TH2D("clus","h2", 120, 0,3, 20, 0, 20);
  // clus2= new TH2D("clus2","h22", 120, 0,0, 10, 0, 0);



  for (Int_t i = 0; i < numberOfEvents; ++i) {


    m_hitmaker.ProcessEvent();
    m_sensor.ProcessEvent();
    // m_analog.processEvent();
    m_binary.processEvent();

    //*** hit and cloud charge histograms ***
    // hist = m_hist2DMaker.histMake(m_strip_min, m_strip_max, pitch_size, m_sensor.m_strip_position);
    // m_hist2DMaker.histDrawAndSave(hist, i, pitch_size);
    //new TCanvas;
    //hist->ProjectionX()->Draw();
    // m_sensor.get_fit()->Draw("same");

    //**Histogram of the generated hit position and charge
    // m_HitAndChargeHist.FillHisto(hitDist,m_sensor.hit_position);
    //  m_HitAndChargeHist.FillHisto(ChargeDist,m_sensor.generated_charge);

    //**cluster studies

    m_cluster.processEvent();

    //*** Fill of histos on cluster size vs strip number/charge ***
    //clus->Fill(fmod((m_cluster.m_hit_position)/pitch_size,3), m_cluster.cont);
    //clus2->Fill(m_sensor.strip_int, m_cluster.cont);
    processEvent();

  }
  //*** Draw histos on cluster size vs strip number/charge ***
  //        cluster_canvas = new TCanvas("cluster_canvas","cluster",3000, 500);
  //        cluster_canvas->Divide(2,1);
  //        cluster_canvas->cd(1);
  //        clus->GetXaxis()->SetTitle("strip position");
  //        clus->GetYaxis()->SetTitle("cluster size");
  //        clus->Draw("colz");
  //        clus->ProfileX()->Draw("same");
  //        cluster_canvas->cd(2);
  //        clus2->GetXaxis()->SetTitle("Charge (fC)");
  //        clus2->GetYaxis()->SetTitle("cluster size");
  //        clus2->Draw("colz");
  //        clus2->ProfileX()->Draw("same");
  //
  //
  //*** Draw hit and cloud charge histograms ***
  // m_HitAndChargeHist.histDrawAndSave(hitDist,ChargeDist);
}

//*** Loop on sigma-- Fills an histo of cluster size vs sigma***
void run_simulation::LoopOnSigma() {

  const double min_sigma = 0.0001,max_sigma =0.1;

  sigma = min_sigma; 

  m_sigma_cluster = new TH2D("sigma_cluster", "", 40, min_sigma, max_sigma, 10, 0.0, 9);
  for (; sigma <= 0.1; sigma += min_sigma) {

    
<<<<<<< HEAD
    TH2D * sigma_cluster = new TH2D("sigma_cluster","",52, 0.0 , 0.1 , 10, 0.0, 10);
    for(int ev =0 ; ev< 1000; ev++){
        Int_t ipri = (Int_t)(1000 / 10);
        if (ev % ipri == 0) std::cout << "INFO ::    >>  " << ev  << "/" << 1000 << "..." << std::endl;
        for (int k=1; k<=52; k++) {
            
            sigma = pitch_size * (0.025*k);
            
            run_simulation::init();
            run_simulation::loop(1);
                //std::cout<<"Event number:  "<<ev<<" Sigma: "<<sigma<<" Cluster size: "<<m_cluster.cont<<std::endl;
            
            sigma_cluster->Fill(sigma, m_cluster.cont);
            
        }
    }
    sigma_cluster->GetXaxis()->SetTitle("sigma [mm]");
    sigma_cluster->GetYaxis()->SetTitle("cluster size");
    sigma_cluster->Draw("colz");
    sigma_cluster->SaveAs("Sigma_cluster.root");
}
=======
    std::cout<<" Sigma: "<<sigma<<std::endl;
>>>>>>> 2304e45d7dec486207930e011c2bb7e83a793bc8

    run_simulation::init();
    run_simulation::loop(1000);



  }
  m_sigma_cluster->GetXaxis()->SetTitle("sigma [mm]");
  m_sigma_cluster->GetYaxis()->SetTitle("cluster size");
  m_sigma_cluster->Draw("colz");
  auto pro= m_sigma_cluster->ProfileX();
  pro->Draw("same");
}



void run_cluster_size_simulation::processEvent() {
  m_sigma_cluster->Fill(sigma, m_cluster.get_cluster_size());
}
