//
//  crosstalk.h
//  
//
//  Created by Lucrezia Stella Bruni on 09/12/15.
//
//

#ifndef ____crosstalk__
#define ____crosstalk__

#include <stdio.h>
class crosstalk{
public:
    void set_intput_pointer(const std::vector<hit_with_charge>* input_pointer);
    void ProcessEvent();
    const std::vector<hit_with_charge>* get_hit_ptr();
   
private:
   const std::vector<hit_with_charge>* m_strip;
    std::vector<hit_with_charge> m_strip_position_crosstalk;
};

#endif /* defined(____crosstalk__) */
