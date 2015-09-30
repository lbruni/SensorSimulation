

#include "digitizer.h"
#include "TMath.h"
#define nChannels_Analog 128
#define nChannels_Binary 2
#define Charge_min 0
#define Charge_max 1



void digitizer::set_intput_pointer(const std::vector<hit_with_charge>* input_pointer) {
  m_Input_hit = input_pointer;
}

void digitizer::set_digits(Double_t min_charge, Double_t max_charge, Int_t steps) {
  
  m_min = min_charge;
  m_max = max_charge;
  m_steps = (max_charge - min_charge)/(Double_t)steps;
}

void digitizer::set_preAmplifier(Double_t Amplification) {
  m_amplification = Amplification;
}

void digitizer::processEvent() {
  m_hit.clear();
  if (!m_Input_hit)
  {
    std::cout << "[digitizer::processEvent()]: input not set correctly " << std::endl;
    return;
  }



  for (size_t i = 0; i < m_Input_hit->size();++i)
  {
    auto charge_in_mv = amplify_signal(m_Input_hit->at(i).charge);
    hit_with_charge charge_digit ;
    if (charge_in_mv<m_min)
    {
      charge_digit.charge = 0;
    }else if (m_max<=charge_in_mv)
    {
      charge_digit.charge = m_max;
    } else {
     charge_digit.charge = TMath::Floor((charge_in_mv - m_min) / m_steps) * m_steps + m_min;
    }
    if (charge_digit.charge>0) {
      charge_digit.x = m_Input_hit->at(i).x;
      charge_digit.y = m_Input_hit->at(i).y;
      m_hit.push_back(charge_digit);
    }
  }

}

const std::vector<hit_with_charge>* digitizer::get_hit_ptr() const {
  return &m_hit;
}

Double_t digitizer::amplify_signal(Double_t charge_signal) const {
  return charge_signal*m_amplification;
}
