module blink(
	input logic clk,
	output logic led
);
	logic clk_out; // fio para o clk out

	div_clock div(.clk(clk), .clk_out(clk_out)); // instância do módulo div_clock
	
	/*
	initial begin
		led = 0;
	end
	*/
	
	
	always @(posedge clk_out) begin // Alterna o estado do led
		led <= ~led;
	
	end
	

endmodule
