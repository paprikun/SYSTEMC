
#ifndef MONITOR_H_
#define MONITOR_H_

#include <systemc>
#include <tlm.h>
#include <uvm>
#include "vip_if.h"

class monitor : public uvm::uvm_monitor
{
 public:
  vip_if* dut_vif ;
  monitor(uvm::uvm_component_name name)
  : uvm_monitor(name)
  {}

  UVM_COMPONENT_UTILS(monitor);

  void build_phase(uvm::uvm_phase& phase)
  {
    uvm::uvm_monitor::build_phase(phase);
    dut_vif = new vip_if();
    uvm::uvm_config_db<vip_if*>::get(0, "", "vif1", dut_vif);
  }

  int timer_start;
  int timer_start_last;
  int timer_finish;
  
  void run_phase( uvm::uvm_phase& phase )
  {    
    for (;;){
        sc_core::wait( dut_vif->out.posedge_event());
        timer_start = sc_time_stamp().value() / 10 / 1000;
        if ( ( timer_start - timer_start_last % 256 == 0 && timer_start_last != 0)){
            UVM_ERROR("", "period");
            printf ("expected value: %d and received value %d\n", 256   , timer_start - timer_start_last   );
            wait(100,SC_NS);
            //sc_stop();
        }
        timer_start_last = timer_start;
        sc_core::wait( dut_vif->out.negedge_event());
        timer_finish = sc_time_stamp().value() / 10 / 1000;
        
        if  ( dut_vif->in_last % 256 != timer_finish - timer_start){
            UVM_ERROR("", "duty cycle");
            printf ("expected value: %d and received value %d\n", dut_vif->in_last %  256   , (timer_finish - timer_start )   );
            wait(100,SC_NS);
           // sc_stop();
        }
    }
  }
  
  
  
};

#endif /* _MONITOR_H_ */
