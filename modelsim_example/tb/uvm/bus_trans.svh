class bus_trans extends uvm_sequence_item;

  `uvm_object_utils(bus_trans)

  bit [7:0]data;
  bit      update;

  function new (string name = "");
    super.new(name);
  endfunction
 
endclass: bus_trans
