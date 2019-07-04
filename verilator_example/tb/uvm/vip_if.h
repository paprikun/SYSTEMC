#ifndef VIP_IF_H_
#define VIP_IF_H_

#include <systemc>
#include <uvm>

class vip_if
{
    public:
        
    

    
    sc_signal<unsigned int>    in;
    sc_signal<unsigned int>    in_last;
    
    sc_signal<bool>            rst;
    sc_signal<bool>            out;
    vip_if() {}

};
#endif
