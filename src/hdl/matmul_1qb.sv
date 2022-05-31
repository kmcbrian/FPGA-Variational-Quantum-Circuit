// matmul module generated using c++
// multiplies a matrix and a vector to
// output a  vector
module matmul_1qb #(
parameter N = 16,
parameter D = 2
)
(
input [N-1:0] matrix [0:D**2 *2 -1],
input [N-1:0] i_vector [0:D*2 -1],
output [N-1:0] o_vector [0:D*2 -1]
);
wire [N-1:0] re_toadd[0:D**2-1];
wire [N-1:0] im_toadd[0:D**2-1];
wire ovr[0:D**2-1];

// Multiply corresponding complex numbers

complex_mult #(N) ele_0(
.a(matrix[0]),
.b(matrix[1]),
.c(i_vector[0]),
.d(i_vector[1]),
.re(re_toadd[0]),
.im(im_toadd[0]),
.ovr(ovr[0])
);

complex_mult #(N) ele_1(
.a(matrix[2]),
.b(matrix[3]),
.c(i_vector[2]),
.d(i_vector[3]),
.re(re_toadd[1]),
.im(im_toadd[1]),
.ovr(ovr[1])
);

complex_mult #(N) ele_2(
.a(matrix[4]),
.b(matrix[5]),
.c(i_vector[0]),
.d(i_vector[1]),
.re(re_toadd[2]),
.im(im_toadd[2]),
.ovr(ovr[2])
);

complex_mult #(N) ele_3(
.a(matrix[6]),
.b(matrix[7]),
.c(i_vector[2]),
.d(i_vector[3]),
.re(re_toadd[3]),
.im(im_toadd[3]),
.ovr(ovr[3])
);

// Add complex products to find output vector
qadd #(N-1,N) re_sum_v0 (
.a(re_toadd[0]),
.b(re_toadd[1]),
.c(o_vector[0])
);
qadd #(N-1,N) im_sum_v0 (
.a(im_toadd[0]),
.b(im_toadd[1]),
.c(o_vector[1])
);
qadd #(N-1,N) re_sum_v1 (
.a(re_toadd[2]),
.b(re_toadd[3]),
.c(o_vector[2])
);
qadd #(N-1,N) im_sum_v1 (
.a(im_toadd[2]),
.b(im_toadd[3]),
.c(o_vector[3])
);

endmodule