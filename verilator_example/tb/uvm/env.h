

#ifndef ENV_H_
#define ENV_H_

#include <systemc>
#include <uvm>

#include "sequence_a.h"
#include "bus_trans.h"
#include "driver.h"
#include "monitor.h"
#include "sequencer.h"

#define NUM_SEQS 1

class env: public uvm::uvm_env
{
 public:
  // instances
  sequencer<bus_trans, bus_trans>* sqr;
  driver<bus_trans, bus_trans>*    drv;  
  monitor*    mon;
  // sequence
  sequence_a<bus_trans, bus_trans>* sequence_[NUM_SEQS];

  UVM_COMPONENT_UTILS(env);

  env( uvm::uvm_component_name name ) : uvm::uvm_env( name ), sqr(0), drv(0) {}

  void build_phase(uvm::uvm_phase& phase)
  {
    uvm::uvm_env::build_phase(phase);

    sqr = sequencer<bus_trans, bus_trans>::type_id::create("sequence_controller", this);
    drv = driver<bus_trans, bus_trans>::type_id::create("driver", this);
   mon = monitor::type_id::create("monior", this);
   

    for (int i = 0; i < NUM_SEQS; i++)
    {
      std::ostringstream str;
      str << "sequence_" << i;
      sequence_[i] = new sequence_a<bus_trans, bus_trans>(str.str());
    }
  }

  void connect_phase(uvm::uvm_phase& phase)
  {
    drv->seq_item_port(sqr->seq_item_export);
  }

  void run_phase(uvm::uvm_phase& phase)
  {
    phase.raise_objection(this);
    SC_FORK
      sc_core::sc_spawn(sc_bind(&env::start_sequence, this, 0)),
    SC_JOIN
    phase.drop_objection(this);
  }

  void start_sequence(int n)
  {
    sequence_[n]->start(sqr, NULL);
  }

};

#endif /* ENV_H_ */
