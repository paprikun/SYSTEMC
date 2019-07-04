`timescale 1ns / 1ns
`include "uvm_macros.svh"
`include "../tb/uvm/vip_if.sv"
`include "../tb/uvm/env.svh"

module main;
import uvm_pkg::*;
import test_pkg::*;





dut_if dut_if1();


 top  dut(
        .clk                  (dut_if1.clk),
        .in                 (dut_if1.in),
        .rst                (dut_if1.rst),
        .out                  (dut_if1.out),
        .in_last            (dut_if1.in_last)
);


// real timer;
initial begin
 dut_if1.rst = 0;
 #100ns;
 dut_if1.rst = 1;
end

initial begin


 dut_if1.clk = 1;

  forever dut_if1.clk = #5ns ~dut_if1.clk;
  end
  



initial begin 
    
    run_test("env");

end
initial uvm_config_db#(virtual dut_if)::set(null, "*", "name_vif", dut_if1); 



endmodule
