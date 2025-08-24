module dff_d(
    input logic d, clk, clk_slow,
    output logic q
);

always_ff @(posedge clk) begin
    if (clk_slow == 1'b1) begin
        q <= d;
    end
end
 
endmodule