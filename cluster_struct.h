#ifndef cluster_struct_h__
#define cluster_struct_h__
#include "hit_with_charge.h"
class cluster_struct :public hit_with_charge {
public:
  

  cluster_struct() :cluster_size(0){}
  
  double cluster_size;
  

};

#endif // cluster_struct_h__
