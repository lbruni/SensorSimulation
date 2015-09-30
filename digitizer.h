
//
//  digitizer.h
//  
//
//  Created by Lucrezia Stella Bruni on 28/09/15.
//
//

#ifndef ____digitizer__
#define ____digitizer__
#include "TCanvas.h"
#include "Rtypes.h"
#include <vector>
#include "hit_with_charge.h"

class digitizer {
public:
    TCanvas *canvas;
    TCanvas *canvas1;
    Double_t matrix_analog[100][128];
    Double_t matrix_binary[100][2];
    TH2D *binary = NULL;
    TH2D *analog = NULL;
    Double_t preAmplifier(Double_t chargefC);
    Double_t chargemV;
    void BinaryReadout(std::vector<hit_with_charge> m_strip_position);
    void AnalogReadout( std::vector<hit_with_charge> m_strip_position);
    
    Int_t hit_binary;
    
};

#endif /* defined(____digitizer__) */
