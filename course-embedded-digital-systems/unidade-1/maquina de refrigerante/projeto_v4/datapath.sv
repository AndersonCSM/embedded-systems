module datapath(
    input logic [7:0] s, a,
    input logic tw, tc, clk,
    output logic tm
);
    reg [7:0] tot;
    
    always_ff @(posedge clk) begin
        if (tc) begin
            tot <= 8'b0; // clear
        end
        else if (tw) begin
            tot <= tot + a; // soma 
        end
    end

    logic eq, gt, lt;
    comparator comp(.a(tot), .b(s), .eq(eq), .gt(gt), .lt(lt)); // comparador

    assign tm = gt | eq; // tm será 1 quando tot > = s
endmodule
