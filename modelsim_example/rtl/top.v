module top(in,clk,rst,out,in_last);
input [7:0] in;
input clk;
input rst;
output out;
output [7:0] in_last;
reg[7:0] counter;
reg [7:0] in_last_ ;


assign in_last = in_last_;
assign out = (in_last_ > (counter - 1)) & rst;

always @(posedge clk)
begin
    if (~rst)begin
        counter <= 0;        
    end
    else begin
        if (counter == 0)begin
            in_last_ <= in;
            
        end    
        counter <= counter + 1;
    end
end

endmodule
