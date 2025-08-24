module comparator(
    input logic [7:0] a, b, // Entradas de 8 bits
    output logic eq,        // Igualdade
    output logic gt,        // Maior que
    output logic lt         // Menor que
);
    always_comb begin // always para bloco combinacional
        eq = (a == b); // Igualdade
        gt = (a > b);  // Maior que
        lt = (a < b);  // Menor que
    end

endmodule
