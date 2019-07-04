export SYSTEMC=/usr/local/uvm_systemc_aliance/
export SYSTEMC_ARCH=linux64

TOP_RTL      = top
TOP_RTL_FILE = $(patsubst %,%.v,$(TOP_RTL))
RTL_PATH     = ../rtl
SC_TB_FILE   = ../tb/main.cpp
OBJ_DIR      = obj_dir
EXE          = simu

LDFLAGS = " -Wl,-rpath,$(SYSTEMC)/lib-linux64  -luvm-systemc  "

TRACE = 1
.PHONY: gen exe all clean sim

all:
	make gen
	make exe

	
gen:
	verilator     $(SC_TB_FILE) -sc  --trace   -y   $(RTL_PATH) $(TOP_RTL_FILE)    -exe -o ../$(EXE) -LDFLAGS $(LDFLAGS) -CFLAGS -O3       

exe:
	make -C $(OBJ_DIR) -f $(patsubst %,V%.mk, $(TOP_RTL)) 

sim:
	./simu $(TRACE)

clean:
	rm -rf obj_dir
	rm *.vcd
	rm local_time
	rm simu
