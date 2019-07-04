
class driver extends uvm_driver #(bus_trans);

  `uvm_component_utils(driver)


  virtual dut_if dut_vif;

  function new(string name, uvm_component parent);
    super.new(name, parent);
  endfunction

  function void build_phase(uvm_phase phase);
    // Get interface reference from config database
    if(!uvm_config_db#(virtual dut_if)::get(this, "", "name_vif", dut_vif)) begin
      `uvm_error("", "uvm_config_db::get failed")
    end
  endfunction 

  task run_phase(uvm_phase phase);

        forever begin
        seq_item_port.get_next_item(req);    
         if (req.update)
            dut_vif.rst = 1;
        
        else begin
            dut_vif.in = req.data;
            #($urandom()%3000);
        end
        seq_item_port.item_done();
        end

  endtask

endclass: driver
