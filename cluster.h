
#ifndef ____cluster__
#define ____cluster__

#include <stdio.h>
#include "cluster_struct.h"
class cluster {
public:
    
    void  set_intput_pointer_digitizer(const std::vector<hit_with_charge>* input_pointer);

    void processEvent();
    
    const cluster_struct* get_cluster_ptr() const;
    size_t find_first_cluster(size_t start);
    double get_cluster_size() const;
private:
  

    const std::vector<hit_with_charge>*  m_digitized_hit;
    cluster_struct m_cluster;
#endif /* defined(____cluster__) */
    
    
};