module projeto(
    input logic c, clk,
    output logic d);
    
    wire c_out;
    wire [7:0] s_val, a_val;
    assign s_val = 8'd3;
    assign a_val = 8'd1;

    deboucing btt(.pb(c), .clk(clk), .pb_out(c_out));
    maquina_refrigerante mq1(.s(s_val), .a(a_val), .c(c_out), .clk(clk), .d(d));
endmodule