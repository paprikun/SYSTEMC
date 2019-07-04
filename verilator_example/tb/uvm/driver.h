

#ifndef MY_DRIVER_H_
#define MY_DRIVER_H_

#include <systemc>
#include <tlm.h>
#include <uvm>
#include "vip_if.h"

extern  VerilatedVcdSc* tfp;
template <typename REQ = uvm::uvm_sequence_item, typename RSP = REQ>

class driver : public uvm::uvm_driver<REQ,RSP>
{
 public:
     
  vip_if* dut_vif ; 
  driver( uvm::uvm_component_name name ) : uvm::uvm_driver<REQ,RSP>( name ) {}
  UVM_COMPONENT_PARAM_UTILS(driver<REQ,RSP>);
  
  void build_phase(uvm::uvm_phase& phase){
      dut_vif = new vip_if();
      uvm::uvm_config_db<vip_if*>::get(0, "", "vif1", dut_vif);
  }
  void run_phase(uvm::uvm_phase& phase)
  {
    
    REQ req;
    RSP rsp;
    dut_vif -> rst = 0;
    
    for(;;){
    this->seq_item_port->get(req);
        rsp.set_id_info(req);    
        
        if (req.update){
            dut_vif -> rst = 1;
        }
        else {
            dut_vif -> in = req.data;
            wait( rand()%3000, SC_NS);
            
            
            
            
        }
    this->seq_item_port->put(rsp);       
    
        
    
    }
  }
};
#endif 
