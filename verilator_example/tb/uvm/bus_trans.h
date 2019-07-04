

#ifndef BUS_TRANS_H_
#define BUS_TRANS_H_

#include <systemc>
#include <uvm>

class bus_trans : public uvm::uvm_sequence_item
{
 public:
  signed int data;
  bool         update;
  
  bus_trans( const std::string& name = "bus_trans_seq_item" ) : uvm::uvm_sequence_item(name)
  {
    data = 0;
    update = 0;
  }
  UVM_OBJECT_UTILS(bus_trans);
};

#endif /* BUS_TRANS_H_ */
