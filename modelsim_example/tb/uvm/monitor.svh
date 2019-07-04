`timescale 1ns / 1ns
  
  
  
class monitor extends uvm_monitor;
  `uvm_component_utils(monitor)

  virtual dut_if dut_vif;

 
//      
  function new(string name, uvm_component parent);
    super.new(name, parent);
  endfunction
  function void build_phase(uvm_phase phase);
    // Get interface reference from config database
    if(!uvm_config_db#(virtual dut_if)::get(this, "", "name_vif", dut_vif)) begin
      `uvm_error("", "uvm_config_db::get failed")
    end

endfunction

  int timer_start;
  int timer_start_last;
  int timer_finish;


  task run_phase(uvm_phase phase);
        @(posedge dut_vif.rst);
        forever begin
            @(posedge dut_vif.out);
            timer_start = $time / 10;
              if ( ( timer_start - timer_start_last % 256 == 0 && timer_start_last != 0))begin
               `uvm_error("", "period");
                $display ("expected value: %d and received value %d\n", 256   , timer_start - timer_start_last   );
                #100ns;
                $finish;
              end

              timer_start_last = timer_start;
              @(negedge dut_vif.out);
              timer_finish = $time / 10;
              if  ( dut_vif.in_last % 256 != timer_finish - timer_start)begin
                    `uvm_error("", "duty cycle");
                    $display ("expected value: %d and received value %d\n", dut_vif.in_last %  256   , (timer_finish - timer_start )   );
                    #100ns;
                   $finish;
              end
        end
  endtask: run_phase
endclass: monitor

  
