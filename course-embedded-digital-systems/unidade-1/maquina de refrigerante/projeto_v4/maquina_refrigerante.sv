module maquina_refrigerante(
    input logic [7:0] s, a, // Entradas de 8 bits
    input logic c, clk, // Entradas de controle e clk
    output logic d // Saidas de controle  
);
    wire logic clk_op;
    wire logic tm;
    wire logic tw;
    wire logic tc;

    // SEMPRE usar clock direto no testbench para evitar problemas
    //assign clk_op = clk; // Clock direto sempre
    div_clock div_inst(.clk(clk), .clk_out(clk_op));

    datapath dp(.s(s), .a(a), .tw(tw), .tc(tc), .clk(clk_op), .tm(tm));
    controller ctrl(.c(c), .tm(tm), .clk(clk_op), .d(d), .tw(tw), .tc(tc));

endmodule