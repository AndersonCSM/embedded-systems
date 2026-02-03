module controller(
    input logic c, tm, clk, // clk aqui é o clk_op (lento)
    output logic d, tw, tc
);

typedef enum logic [1:0] {
        INICIAL = 2'b00,
        WAIT    = 2'b01,
        COUNT   = 2'b10,
        DISP    = 2'b11
    } state_t;

    state_t estado_atual = INICIAL;
    state_t estado_proximo;

    // PRECISO DE AJUDA PARA EXPLICAR MELHOR
    // Sincronizadores para 'c' (cruza do domínio de clk para clk_op)
    logic c_sync1, c_sync2;
    always_ff @(posedge clk) begin 
        c_sync1 <= c;
        c_sync2 <= c_sync1;
    end

    // Detecção de borda de subida para 'c_sync2'
    logic c_sync2_prev;
    logic c_posedge;

    always_ff @(posedge clk) begin // clk é clk_op
        c_sync2_prev <= c_sync2;
    end
    assign c_posedge = c_sync2 & ~c_sync2_prev; // Detecta borda de subida de c_sync2

    // Lógica de transição de estados
    always_comb begin
        estado_proximo = estado_atual;
        case (estado_atual)
            INICIAL:  estado_proximo = WAIT;
            WAIT:     if (tm) estado_proximo = DISP;
                      else if (c_posedge) estado_proximo = COUNT; // USA A BORDA DETECTADA
                      else estado_proximo = WAIT;
            COUNT:    estado_proximo = WAIT;
            DISP:     estado_proximo = DISP;
        endcase
    end

    // Lógica de saída
    always_comb begin
        d  = 1'b0; // Default assignments
        tw = 1'b0;
        tc = 1'b0;
        case (estado_atual)
            INICIAL: begin
                tc = 1'b1; 
            end
            WAIT: begin
                // Mantém saídas em default
            end
            COUNT: begin
                tw = 1'b1; 
            end
            DISP: begin
                d = 1'b1; 
            end
        endcase
    end

    always_ff @(posedge clk) begin // clk é clk_op
        estado_atual <= estado_proximo;
    end

endmodule