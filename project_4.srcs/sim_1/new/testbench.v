`timescale 1ns / 1ps

module testbench;
	reg clk=0;
	reg [11:0] eight_bit_value=0;
	wire [3:0] ones;
	wire [3:0] tens ; //output values
	wire [3:0] hundreds;
	wire [3:0] thousands;

BCD UUT (clk, eight_bit_value, ones, tens, hundreds, thousands);
integer i;
always #2 clk = ~clk;
initial begin
  eight_bit_value = 0;
  //for(i=0;i<10;i=i+1)begin
  //50 eight_bit_value<=i;
  //end
  #1 eight_bit_value = 10;
  #1 eight_bit_value = 248;
  #1 eight_bit_value = 1234;
end

endmodule
