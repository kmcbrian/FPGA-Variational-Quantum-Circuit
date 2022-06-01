// tensor product module generated using c++
// takes kronecker product of 2 matrices of arbitrary size to
// output a  matrix
module tensorproduct_11qb #(
parameter N = 16,
parameter D1 = 2,
parameter D2 = 2
)
(

input [N-1:0] mat_1 [0:D1**2 *2 -1],
input [N-1:0] mat_2 [0:D2**2 *2 -1],
output [N-1:0] o_mat [0:2*(D1**2)*(D2**2) -1]
);

wire ovr[0:(D1**2 * D2**2) -1];

// complex multiplication indexed as mat1_row, mat1_col, mat2_row, mat2_col

complex_mult #(N) ele_0000(
.a(mat_1[0]),
.b(mat_1[1]),
.c(mat_2[0]),
.d(mat_2[1]),
.re(o_mat[0]),
.im(o_mat[1]),
.ovr(ovr[0])
);

complex_mult #(N) ele_0001(
.a(mat_1[0]),
.b(mat_1[1]),
.c(mat_2[2]),
.d(mat_2[3]),
.re(o_mat[2]),
.im(o_mat[3]),
.ovr(ovr[1])
);

complex_mult #(N) ele_0100(
.a(mat_1[2]),
.b(mat_1[3]),
.c(mat_2[0]),
.d(mat_2[1]),
.re(o_mat[4]),
.im(o_mat[5]),
.ovr(ovr[2])
);

complex_mult #(N) ele_0101(
.a(mat_1[2]),
.b(mat_1[3]),
.c(mat_2[2]),
.d(mat_2[3]),
.re(o_mat[6]),
.im(o_mat[7]),
.ovr(ovr[3])
);

complex_mult #(N) ele_0010(
.a(mat_1[0]),
.b(mat_1[1]),
.c(mat_2[4]),
.d(mat_2[5]),
.re(o_mat[8]),
.im(o_mat[9]),
.ovr(ovr[4])
);

complex_mult #(N) ele_0011(
.a(mat_1[0]),
.b(mat_1[1]),
.c(mat_2[6]),
.d(mat_2[7]),
.re(o_mat[10]),
.im(o_mat[11]),
.ovr(ovr[5])
);

complex_mult #(N) ele_0110(
.a(mat_1[2]),
.b(mat_1[3]),
.c(mat_2[4]),
.d(mat_2[5]),
.re(o_mat[12]),
.im(o_mat[13]),
.ovr(ovr[6])
);

complex_mult #(N) ele_0111(
.a(mat_1[2]),
.b(mat_1[3]),
.c(mat_2[6]),
.d(mat_2[7]),
.re(o_mat[14]),
.im(o_mat[15]),
.ovr(ovr[7])
);

complex_mult #(N) ele_1000(
.a(mat_1[4]),
.b(mat_1[5]),
.c(mat_2[0]),
.d(mat_2[1]),
.re(o_mat[16]),
.im(o_mat[17]),
.ovr(ovr[8])
);

complex_mult #(N) ele_1001(
.a(mat_1[4]),
.b(mat_1[5]),
.c(mat_2[2]),
.d(mat_2[3]),
.re(o_mat[18]),
.im(o_mat[19]),
.ovr(ovr[9])
);

complex_mult #(N) ele_1100(
.a(mat_1[6]),
.b(mat_1[7]),
.c(mat_2[0]),
.d(mat_2[1]),
.re(o_mat[20]),
.im(o_mat[21]),
.ovr(ovr[10])
);

complex_mult #(N) ele_1101(
.a(mat_1[6]),
.b(mat_1[7]),
.c(mat_2[2]),
.d(mat_2[3]),
.re(o_mat[22]),
.im(o_mat[23]),
.ovr(ovr[11])
);

complex_mult #(N) ele_1010(
.a(mat_1[4]),
.b(mat_1[5]),
.c(mat_2[4]),
.d(mat_2[5]),
.re(o_mat[24]),
.im(o_mat[25]),
.ovr(ovr[12])
);

complex_mult #(N) ele_1011(
.a(mat_1[4]),
.b(mat_1[5]),
.c(mat_2[6]),
.d(mat_2[7]),
.re(o_mat[26]),
.im(o_mat[27]),
.ovr(ovr[13])
);

complex_mult #(N) ele_1110(
.a(mat_1[6]),
.b(mat_1[7]),
.c(mat_2[4]),
.d(mat_2[5]),
.re(o_mat[28]),
.im(o_mat[29]),
.ovr(ovr[14])
);

complex_mult #(N) ele_1111(
.a(mat_1[6]),
.b(mat_1[7]),
.c(mat_2[6]),
.d(mat_2[7]),
.re(o_mat[30]),
.im(o_mat[31]),
.ovr(ovr[15])
);

endmodule