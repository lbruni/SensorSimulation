

#ifndef ____digitizer__
#define ____digitizer__
#include "TCanvas.h"
#include "Rtypes.h"
#include <vector>
#include "hit_with_charge.h"

class digitizer {
public:
  digitizer() {}
    
  void set_intput_pointer(const std::vector<hit_with_charge>* input_pointer);
  void set_digits(Double_t min_charge, Double_t max_charge, Int_t steps);
  void set_preAmplifier(Double_t Amplification);
    hit_with_charge charge_digit ;
  void processEvent();
  const std::vector<hit_with_charge>* get_hit_ptr() const;
    std::vector<hit_with_charge> m_charge_digitized;
private:
  
  std::vector<hit_with_charge> m_hit;
  const std::vector<hit_with_charge>* m_Input_hit;
  Double_t m_min, m_max, m_amplification,m_steps;
  
  Double_t amplify_signal(Double_t charge_signal) const;
};

#endif /* defined(____digitizer__) */
