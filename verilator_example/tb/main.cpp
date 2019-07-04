#include <systemc>
#include <uvm>
using namespace uvm;

#include "verilated_vcd_sc.h"
#include "uvm/vip_if.h"
#include "uvm/env.h"
#include "Vtop.h"
#define TRACE


int sc_main(int argc, char * argv[])
{
#ifdef TRACE
   // Verilator trace file
   Verilated::traceEverOn(true);
   VerilatedVcdSc* tfp = new VerilatedVcdSc;
#endif
    
    
   sc_time T(10,SC_NS);
   sc_clock clk("clk",T);
   
   vip_if* dut_vif_1 =new vip_if();
   uvm::uvm_config_db<vip_if*>::set(0, "", "vif1", dut_vif_1);


   Vtop dut("top_verilog");
   dut.clk (clk);
   dut.rst( dut_vif_1 -> rst);
   dut.in(dut_vif_1-> in);
   dut.in_last(dut_vif_1-> in_last);
   
   dut.out(dut_vif_1->out);
   
   driver<bus_trans, bus_trans>*    drv;  
   
   env e1("vif1");   
   
#ifdef TRACE
   // Verilator trace file, depth
   dut.trace(tfp, 0);
   tfp->open("simu.vcd");
#endif


    uvm::run_test();
  

#ifdef TRACE
   tfp->close();
#endif
   return 0;
}
