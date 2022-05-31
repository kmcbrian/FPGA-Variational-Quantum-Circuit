`timescale 1ns/1ps
module variational_circuit1#(
    parameter N=16,
    parameter n_qb= 1
)
(
    input wire [N-1:0] v_matrix0 [0:7],
    output wire [N-1:0] psi_f [0:3]
);
reg [N-1:0] psi_0 [0:3];

 // generating vector_products, tensor_products, and matmul

wire [N-1:0] psi_1 [0:3];
matmul_1qb mm0 (
    .matrix(v_matrix0),
    .i_vector(psi_0),
    .o_vector(psi_1)
);


initial begin
   $readmemb("vector_qb.dat", psi_0);
end

assign psi_f[0:3] = psi_1[0:3];

endmodule