module controller(
input logic b1, b1, al,
output logic l, add, clr  
);

typedef enum logic {
    INI = 2'b00;
    W = 2'b01;
    I = 2'b10;
    E = 2'b11;
  } state;

state atual = INI;

always @(posedge clk)begin
    add = 0;
    l = 0;
    clr = 0;
    case (atual)
        INI :
                atual = W;
                clr = 1;
        W :
            if (al) begin
                atual = E;
                
            end
            if (b1) begin
                atual = I;
            end
            
        I :
                atual = W;
                load = 1;

        E :
            if (b1) begin
                atual = wt;
                en = 1;
                load = 0;
            end
    endcase

end

endmodule