
uvm_opts	= +incdir+$(UVM_HOME)/src/ -y $(UVM_HOME)/src/ $(UVM_HOME)/src/uvm.sv  +libext+.v+.sv+.vlib      
TOP_RTL      = main
TOP_RTL_FILE = $(patsubst %,%.sv,$(TOP_RTL))
RTL_PATH     = ../rtl
TB_PATH      = ../tb
UVM_PATH     = $(TB_PATH)/uvm

SV_FILES = -y $(RTL_PATH) \
	   -y $(UVM_PATH) \
	   +libext+.v+.sv+.vlib              

.PHONY: gen exe all clean 

TRACE = 1
SCENARIO = "add wave -r sim:main/*; run 5000ms"

ifeq ($(TRACE), 0)
    SCENARIO = "run 5000ms"
endif

all:
	make VLOG
	make VSIM

	
VLOG:
	vlog  $(uvm_opts) $(TB_PATH)/$(TOP_RTL_FILE)    $(SV_FILES)    -timescale "1ns/1ns"

VSIM:
	vsim  -sv_lib $(UVM_HOME)/linux/uvm_dpi   +UVM_NO_RELNOTES   work.main  -suppress 19 -do $(SCENARIO)

clean:
	rm -rf work
	rm  *.wlf	
	rm  localtime
	rm  transcript
