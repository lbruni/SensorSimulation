
#include "cluster.h"


void  cluster::set_intput_pointer_digitizer(const std::vector<hit_with_charge>* input_pointer) {
    m_digitized_hit = input_pointer;
}



const cluster_struct* cluster::get_cluster_ptr() const {
  return &m_cluster;
}


double cluster::get_cluster_size() const {

return m_cluster.cluster_size;
}

void cluster::processEvent() {

 m_cluster= cluster_struct();
  for (int j =0; j < m_digitized_hit->size(); j++) {
      
      
      
      
    if (m_digitized_hit->at(j).charge > 0) {

      ++m_cluster.cluster_size;
      m_cluster.charge += m_digitized_hit->at(j).charge;
      m_cluster.x += m_digitized_hit->at(j).x*m_digitized_hit->at(j).charge;
      m_cluster.y += m_digitized_hit->at(j).y*m_digitized_hit->at(j).charge;
        
            }
  }
  if (m_cluster.cluster_size>0)
  {
    m_cluster.x /= m_cluster.charge;
    m_cluster.y /= m_cluster.charge;
        }

  

}
