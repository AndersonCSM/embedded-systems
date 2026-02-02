module InterfaceBarramentoSimples (
    input logic rd, clk,
    input logic [3:0] a, adr,
    input logic [31:0] q,
    output logic [31:0] d
);

wire logic clk_slow, en, load, eq;

div_clock div(.clk(clk), .clk_out(clk_slow));
controller c1(.rd(rd), .clk(clk_slow), .eq(eq), .load(load), .en(en));
datapath dt(.load(load), .en(en), .clk(clk_slow), .a(a), .adr(adr), .q(q), .d(d), .eq(eq));



endmodule