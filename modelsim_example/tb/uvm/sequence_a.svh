

class sequence_a extends uvm_sequence#(bus_trans);

  `uvm_object_utils(sequence_a)

  
  function new (string name = "");
    super.new(name);

  endfunction

 real timer;
    task body;
        timer = get_localtime();        
        send_update();
        #1ns;
    for (int i=0;i<120000;i++)
        send_data( $urandom());
       
    $display("simulation real time = %d sec", get_localtime() - timer);
    endtask

    task send_update;
        req = bus_trans::type_id::create("update");
        start_item(req);
        req.update = 1;
        finish_item(req);
    endtask
    task send_data(bit [7:0] data);
        req = bus_trans::type_id::create("data");
        start_item(req);
        req.data = data;
        finish_item(req);
    endtask


  function real get_localtime();    
    int fd;
    real localtime;
    $system("date +%s > localtime"); // temp file
    fd = $fopen("localtime", "r");
    $fscanf(fd,"%d",localtime);
    $fclose(fd);
  //  void'($system("rm localtime")); // delete file
    return localtime;
  endfunction



endclass: sequence_a
