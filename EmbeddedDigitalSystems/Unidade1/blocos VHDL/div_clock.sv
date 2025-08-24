module div_clock(
input logic clk,
output logic clk_out);

logic [25:0] counter = 26'b0; // Inicializar contador
//logic [25:0] counter; // 2^26 para representar até 50M

/*
 um ciclo completo de um sinal de clock (um pulso "on" e "off") exige duas mudanças de estado:
de 0 para 1
de 1 para 0
por isso N = Fclk_in / (2 * Fclk_out)
F = 1 / T
F = frequência do clock
T = período do clock (2x o tempo de meio ciclo)

F_in  ------ N
F_out ------ X


1hz
N = 50_000_000 / (2 * 1)
N = 25_000_000

10hz
N = Fclk_in / (2 * Fclk_out)
N = 50_000_000 / (2 * 10)
N = 2_500_000

// 100hz
N = 50_000_000 / (2 * 100)
N = 250_000

*/
// 10hz
    always_ff @(posedge clk) begin
        if (counter == 250_000) begin // para gerar 100Hz 
            counter <= 0;
            clk_out <= ~clk_out;
        end else
            counter <= counter + 1;
    end
/*
1. always_comb:
    Usado para lógica combinacional.
    Substitui o uso de always @(*) no Verilog.

2. always_ff:
    Usado para lógica sequencial (FFs).
    Substitui o uso de always @(posedge clk) no Verilog.
    
3. always_latch:
    Usado para lógica de latch.
    Substitui o uso de always @(*) com condições if/else no Verilog.

Usamos o operador de atribuição não-bloqueante (<=) em vez do operador de 
atribuição bloqueante (=) por estas razões:
    1. Sincronização: O operador não-bloqueante permite que várias atribuições ocorram
    em paralelo dentro de um bloco sempre. Isso é importante em circuitos digitais, 
    onde várias operações podem ocorrer simultaneamente.

    2. Evitar condições de corrida: O uso de <= ajuda a evitar condições de corrida,
    onde o resultado de uma operação pode depender da ordem em que as atribuições são 
    feitas. Isso é especialmente importante em circuitos sequenciais, onde a ordem 
    das operações pode afetar o comportamento do circuito.

    3.Modelagem de Flip-Flops: O operador <= é usado para modelar flip-flops corretamente, pois ele reflete o comportamento
    de armazenamento de valores em bordas de clock.
*/
endmodule