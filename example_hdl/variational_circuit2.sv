`timescale 1ns/1ps
module variational_circuit2#(
    parameter N=16,
    parameter n_qb= 2
)
(
    input wire [N-1:0] v_matrix0 [0:7],
    input wire [N-1:0] v_matrix1 [0:7],
    output wire [N-1:0] psi_f [0:7]
);
reg [N-1:0] psi_0 [0:3];
reg [N-1:0] psi_1 [0:3];

 // generating vector_products, tensor_products, and matmul

reg [N-1:0] hadamard [0:7];
wire [N-1:0] psi_2 [0:3];
matmul_1qb mm0 (
    .matrix(hadamard),
    .i_vector(psi_0),
    .o_vector(psi_2)
);

wire [N-1:0] psi_3 [0:3];
matmul_1qb mm1 (
    .matrix(v_matrix0),
    .i_vector(psi_1),
    .o_vector(psi_3)
);

reg [N-1:0] cx01 [0:31];
wire [N-1:0] psi_4 [0:7];
vectorproduct_11qb vp2(
    .vec_1(psi_2),
    .vec_2(psi_3),
    .o_vec(psi_4)
);

wire [N-1:0] psi_5 [0:7];
matmul_2qb mm3 (
    .matrix(cx01),
    .i_vector(psi_4),
    .o_vector(psi_5)
);

reg [N-1:0] identity [0:7];
wire [N-1:0] o_mat6 [0:31];
tensorproduct_11qb tp4(
    .mat_1(identity),
    .mat_2(v_matrix1),
    .o_mat(o_mat6)
);

wire [N-1:0] psi_7 [0:7];
matmul_2qb mm5 (
    .matrix(o_mat6),
    .i_vector(psi_5),
    .o_vector(psi_7)
);

wire [N-1:0] psi_8 [0:7];
matmul_2qb mm6 (
    .matrix(cx01),
    .i_vector(psi_7),
    .o_vector(psi_8)
);

wire [N-1:0] o_mat9 [0:31];
tensorproduct_11qb tp7(
    .mat_1(hadamard),
    .mat_2(identity),
    .o_mat(o_mat9)
);

wire [N-1:0] psi_10 [0:7];
matmul_2qb mm8 (
    .matrix(o_mat9),
    .i_vector(psi_8),
    .o_vector(psi_10)
);


initial begin
   $readmemb("vector_qb.dat", psi_0);
   $readmemb("vector_qb.dat", psi_1);
   $readmemb("hadamard.dat", hadamard);
   $readmemb("cx01.dat", cx01);
   $readmemb("identity.dat", identity);
end

assign psi_f[0:7] = psi_10[0:7];

endmodule