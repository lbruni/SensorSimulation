
#include "cluster.h"


void  cluster::set_intput_pointer_digitizer(const std::vector<hit_with_charge>* input_pointer) {
    m_digitized_hit = input_pointer;
}

void cluster::FindClusterNumber(){
    
    cont = 0;
    for(int j = 0; j < m_digitized_hit->size(); j++){
        if(m_digitized_hit->at(j).charge > 0) {
            cont ++;
        }
    }
    
}
}
void cluster::processEvent() {
}
