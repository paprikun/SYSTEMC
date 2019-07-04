#include <systemc>
#include <uvm>
using namespace uvm;

#include "verilated_vcd_sc.h"
#include "uvm/vip_if.h"
#include "uvm/env.h"
#include "Vtop.h"


int sc_main(int argc, char * argv[])
{

   int TRACE = 1;
TRACE = 1;
 if (argc == 2)
        TRACE  = atoi ( argv[1]);

 VerilatedVcdSc* tfp;


if (TRACE){
   // Verilator trace file
   Verilated::traceEverOn(true);
  
}
   tfp = new VerilatedVcdSc;
    
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
 
if (TRACE){
   // Verilator trace file, depth
   dut.trace(tfp, 0);
   tfp->open("simu.vcd");
}


    uvm::run_test();
  

if (TRACE){
   tfp->close();
}

   return 0;
}
