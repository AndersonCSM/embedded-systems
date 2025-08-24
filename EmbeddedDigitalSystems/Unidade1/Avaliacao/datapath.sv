module datapath(
input logic add, clr, clk,
output logic al);

wire logic eq_out, lt, gt;
reg [1:0] c = 0;

comparator comp(.a(c),.b(2'b10), .eq(eq_out), .lt(lt), .gt(gt));

always @(posedge clk)begin
    if (add) begin
        c <= c + 1;
    end
    if (clr) begin
        c <= 0;
    end
end

assign al = eq_out;

endmodule