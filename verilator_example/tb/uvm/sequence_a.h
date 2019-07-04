

#ifndef SEQUENCEA_H_
#define SEQUENCEA_H_

#include <systemc>
#include <tlm.h>
#include <uvm>
#include "bus_trans.h"

#include <iomanip>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;


#define NUM_LOOPS 1
#define TR_INIT         REQ* req = new REQ(); \
                        RSP* rsp = new RSP();
                        
 #define TR_RELEASE     this->wait_for_grant();  \
                        this->send_request(req); \
                        this->get_response(rsp);  
                        
template <typename REQ = uvm::uvm_sequence_item, typename RSP = REQ>
class sequence_a : public uvm::uvm_sequence<REQ,RSP>
{
protected:
 
 public:

  sequence_a( const std::string& name_ ) : uvm::uvm_sequence<REQ,RSP>( name_ )
  {
  }
  UVM_OBJECT_PARAM_UTILS(sequence_a<REQ,RSP>);
 private:
// TODO: check types with UVM/SV original
  static unsigned int g_my_id;
  unsigned int my_id;

  int local_time, local_time_buf;  

       
  void body()
  { 
        get_local_time();
        local_time_buf = local_time; 

        send_update();
        wait( 10, SC_PS);
        for (int i=0;i<120000;i++)
        send_data(rand());
        wait(100, SC_NS); 

        get_local_time();
        printf("simulation real time = %d sec\n",local_time - local_time_buf );
    

  }
  void send_update(){
      TR_INIT
       req->update = 1;
       TR_RELEASE 
  }
   void send_data(int data){
      TR_INIT
       req->data = data;
       TR_RELEASE 
  } 
  
   void get_local_time()    
    {
        int fd;
        int res;
        res = system("date +%s > local_time");
        FILE* iFile;
        iFile = fopen ("local_time","rb");
        res = fscanf(iFile, "%d", &local_time);      
    }
    
    
};
// TODO: check types with UVM/SV original
template <typename REQ, typename RSP>
unsigned int sequence_a<REQ,RSP>::g_my_id = 1;
#endif /* SEQUENCEA_H_ */
