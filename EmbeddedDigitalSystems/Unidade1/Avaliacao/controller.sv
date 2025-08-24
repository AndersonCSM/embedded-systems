module controller(
input logic b1, b2, al, clk,
output logic l, add, clr, l_n1, l_n2, l_n3, l_n4
);

typedef enum logic [1:0]{
    INI = 2'b00,
    W = 2'b01,
    I = 2'b10,
    E = 2'b11
  } state;

state atual = INI;
state proximo_estado;

// Bloco 1: Lógica Sequencial (atualização de estado)
// Este bloco SÓ atualiza o estado na borda do clock.
always_ff @(posedge clk) begin
    atual <= proximo_estado;
end

// Bloco 2: Lógica Combinacional (cálculo do próximo estado e saídas)
// Este bloco descreve o que DEVE acontecer em cada estado.
always_comb begin
    // Valores padrão para todas as saídas para evitar latches
    add = 1'b0;
    clr = 1'b0;
    l   = 1'b0;

    l_n1 = 1'b0;
    l_n2 = 1'b0;
    l_n3 = 1'b0;
    l_n4 = 1'b0;

    proximo_estado = atual; // Por padrão, permanece no mesmo estado

    case (atual)
        INI :
        begin
            l_n1 = 1'b1;
            clr  = 1'b1;
            proximo_estado = W;
        end
                
        W :
        begin
            l_n2 = 1'b1;
            if (al) begin
                proximo_estado = E;         
            end
            else if (b1) begin
                proximo_estado = I;
            end
        end 

        I :
        begin
            l_n3 = 1'b1;
            add  = 1'b1;
            proximo_estado = W;
        end    

        E :
        begin
            l_n4 = 1'b1;
            l    = 1'b1;
            if (b2) begin
                proximo_estado = INI;
            end
        end  
    endcase
end

endmodule