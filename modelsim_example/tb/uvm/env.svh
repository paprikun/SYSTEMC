
package test_pkg;
  import uvm_pkg::*;

 `include "bus_trans.svh"

 `include "driver.svh"

 `include "sequence_a.svh"

 `include "monitor.svh"

  class env extends uvm_env;

    `uvm_component_utils(env)


    
    uvm_sequencer#(bus_trans) sqr;
    driver drv;
    monitor mon;

     function new(string name, uvm_component parent);
      super.new(name, parent);
    endfunction
    
    function void build_phase(uvm_phase phase);
      drv = driver ::type_id::create("driver", this);
      mon = monitor ::type_id::create("monitor", this);
      sqr = uvm_sequencer#(bus_trans)::type_id::create("sequencer", this);
    endfunction    

    function void connect_phase(uvm_phase phase);
     drv.seq_item_port.connect(sqr.seq_item_export);
    endfunction

    task run_phase(uvm_phase phase);
      // We raise objection to keep the test from completing
      phase.raise_objection(this);
      begin
        sequence_a seq;
        seq = sequence_a::type_id::create("seq");
        seq.start(sqr);
      end
      // We drop objection to allow the test to complete
      phase.drop_objection(this);
    endtask

  endclass

endpackage


