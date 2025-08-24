module deboucing(
 input logic pb, clk,
 output logic pb_out
);
wire slow_clk;
wire q0, q1, q2; // q2_neg não é mais necessária para esta lógica de saída

div_clock div_inst(.clk(clk), .clk_out(slow_clk));

dff_d d0(.d(pb), .clk(clk), .clk_slow(slow_clk), .q(q0));
dff_d d1(.d(q0), .clk(clk), .clk_slow(slow_clk), .q(q1));
dff_d d2(.d(q1), .clk(clk), .clk_slow(slow_clk), .q(q2));

//assign q2_neg = ~q2;
//assign pb_out = q2_neg & q1; // Lógica de pulso anterior
assign pb_out = q2;

endmodule