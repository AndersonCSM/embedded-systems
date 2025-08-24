module deboucing(
    input logic pb, clk,
    output logic pb_out
);
    // O objetivo é esperar um tempo suficiente para que a trepidação mecânica
    // do botão (ruído) desapareça.
    // Isso garante que o sinal do botão esteja estável por T segundos.
    // f = 1 / T  -> T = 1 / f 
    //
    // para 50Mhz -> T = 1 / 50.000.000 = 2E-8s
    // para 10ms -> 10ms = N * T
    // N = 0.01 / 50.000.000 -> N = 500.000 ciclos
    //
    // para 100Hz -> T = 1 / 100 = 0.01s = 10ms
    // para 20ms -> 20ms = N * T
    // N = 20ms / 10ms = 2 ciclos
    //
    localparam int DEBOUNCE_CYCLES = 2;

    // Registradores internos para o processo de debouncing
    logic [1:0] counter;    // Contador para medir o tempo de estabilidade (2 bits são suficientes para contar até 2)
    logic debounced_state; // Armazena o estado "limpo" e confirmado do botão, após o filtro de debounce.
    // Armazena o estado 'debounced_state' do ciclo de clock anterior.
    // É a chave para detectar a transição (borda) do sinal.
    logic last_debounced_state;

    // Lógica principal do debouncer
    always_ff @(posedge clk) begin
    // Primeiro, guarda o estado anterior para a detecção de borda na saída
    last_debounced_state <= debounced_state;

    // Compara a entrada do botão com o estado estável atual
    if (pb == debounced_state) begin
        // Se o botão e o estado estável são iguais, não há mudança.
        // Reinicia o contador de estabilidade.
        counter <= 0;
    end
    else begin
        // Se são diferentes, uma mudança está ocorrendo.
        // Incrementa o contador.
        counter <= counter + 1;
        
        // Verifica se o contador atingiu o tempo necessário para debounce
        if (counter >= DEBOUNCE_CYCLES) begin
            // Se sim, a mudança é considerada estável.
            // Atualiza o estado estável e reinicia o contador.
            debounced_state <= pb;
            counter <= 0;
        end
    end
end

    // --- Lógica de Saída

    // 'assign' descreve uma lógica combinacional contínua. A saída 'pb_out'
    // é recalculada instantaneamente sempre que 'debounced_state' ou
    // 'last_debounced_state' mudam.
    //
    // Esta é a lógica de DETECÇÃO DE BORDA DE SUBIDA.
    // A saída 'pb_out' será '1' somente no único ciclo de clock em que:
    //   - 'debounced_state'      é '1' (o botão está pressionado e estável)
    //   - E ('&')
    //   - 'last_debounced_state' é '0' (no ciclo anterior, ele estava solto)
    //
    // Isso gera um pulso limpo de um ciclo de clock para o controlador.
    assign pb_out = debounced_state & ~last_debounced_state;
    // assign pb_out = debounced_state;
endmodule