// tensor product module generated using c++
// takes tensor product of 2 vectors of arbitrary size to
// output a vector of size D1*D2
module vectorproduct_11qb #(
parameter N = 16,
parameter D1 = 2,
parameter D2 = 2
)
(

input [N-1:0] vec_1 [0:D1*2 -1],
input [N-1:0] vec_2 [0:D2*2 -1],
output [N-1:0] o_vec [0:2*D1*D2 -1]
);

wire ovr[0:(D1**2 * D2**2) -1];

// complex multiplication indexed as mat1_row, mat1_col, mat2_row, mat2_col

complex_mult #(N) ele_00(
.a(vec_1[0]),
.b(vec_1[1]),
.c(vec_2[0]),
.d(vec_2[1]),
.re(o_vec[0]),
.im(o_vec[1]),
.ovr(ovr[0])
);

complex_mult #(N) ele_01(
.a(vec_1[0]),
.b(vec_1[1]),
.c(vec_2[2]),
.d(vec_2[3]),
.re(o_vec[2]),
.im(o_vec[3]),
.ovr(ovr[1])
);

complex_mult #(N) ele_10(
.a(vec_1[2]),
.b(vec_1[3]),
.c(vec_2[0]),
.d(vec_2[1]),
.re(o_vec[4]),
.im(o_vec[5]),
.ovr(ovr[2])
);

complex_mult #(N) ele_11(
.a(vec_1[2]),
.b(vec_1[3]),
.c(vec_2[2]),
.d(vec_2[3]),
.re(o_vec[6]),
.im(o_vec[7]),
.ovr(ovr[3])
);

endmodule