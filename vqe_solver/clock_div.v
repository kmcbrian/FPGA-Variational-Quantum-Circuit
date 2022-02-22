module clock_divider(input wire fast_clock, output wire slow_clock);

parameter COUNTER_SIZE  = 27  ; // 27 -> 2.684s
parameter COUNTER_MAX_COUNT = (2 ** COUNTER_SIZE) - 1;

reg [COUNTER_SIZE -1:0] count;

always @ (posedge fast_clock)
begin
	if(count == COUNTER_MAX_COUNT)
			count <= 0;
	else
			count <= count + 1'b1;
end

assign slow_clock = count[COUNTER_SIZE-1];

endmodule