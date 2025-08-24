module QuadroAlerta(
    input logic b1, b2, clk,
    output logic l, l_n1, l_n2, l_n3, l_n4
);
wire logic clk_slow, add, clr, al, b1_out, b2_out;

div_clock clk_low(.clk(clk), .clk_out(clk_slow));

deboucing dbc1(.pb(b1), .clk(clk_slow), .pb_out(b1_out));
deboucing dbc2(.pb(b2), .clk(clk_slow), .pb_out(b2_out));

datapath dt(.add(add), .clr(clr), .clk(clk_slow), .al(al));
controller ctrl(.b1(b1_out), .b2(b2_out), .al(al), .clk(clk_slow), .l(l), .add(add), .clr(clr), .l_n1(l_n1), .l_n2(l_n2), .l_n3(l_n3), .l_n4(l_n4));

endmodule
