// matmul module generated using c++
// multiplies a matrix and a vector to
// output a  vector
module matmul_2qb #(
parameter N = 16,
parameter D = 4
)
(
input [N-1:0] matrix [0:D**2 *2 -1],
input [N-1:0] i_vector [0:D*2 -1],
output [N-1:0] o_vector [0:D*2 -1]
);
wire [N-1:0] re_toadd[0:D**2-1];
wire [N-1:0] im_toadd[0:D**2-1];
wire ovr[0:D**2-1];
wire [N-1:0] re_sums[0:D**2-D];
wire [N-1:0] im_sums[0:D**2-D];

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
.c(i_vector[4]),
.d(i_vector[5]),
.re(re_toadd[2]),
.im(im_toadd[2]),
.ovr(ovr[2])
);

complex_mult #(N) ele_3(
.a(matrix[6]),
.b(matrix[7]),
.c(i_vector[6]),
.d(i_vector[7]),
.re(re_toadd[3]),
.im(im_toadd[3]),
.ovr(ovr[3])
);

complex_mult #(N) ele_4(
.a(matrix[8]),
.b(matrix[9]),
.c(i_vector[0]),
.d(i_vector[1]),
.re(re_toadd[4]),
.im(im_toadd[4]),
.ovr(ovr[4])
);

complex_mult #(N) ele_5(
.a(matrix[10]),
.b(matrix[11]),
.c(i_vector[2]),
.d(i_vector[3]),
.re(re_toadd[5]),
.im(im_toadd[5]),
.ovr(ovr[5])
);

complex_mult #(N) ele_6(
.a(matrix[12]),
.b(matrix[13]),
.c(i_vector[4]),
.d(i_vector[5]),
.re(re_toadd[6]),
.im(im_toadd[6]),
.ovr(ovr[6])
);

complex_mult #(N) ele_7(
.a(matrix[14]),
.b(matrix[15]),
.c(i_vector[6]),
.d(i_vector[7]),
.re(re_toadd[7]),
.im(im_toadd[7]),
.ovr(ovr[7])
);

complex_mult #(N) ele_8(
.a(matrix[16]),
.b(matrix[17]),
.c(i_vector[0]),
.d(i_vector[1]),
.re(re_toadd[8]),
.im(im_toadd[8]),
.ovr(ovr[8])
);

complex_mult #(N) ele_9(
.a(matrix[18]),
.b(matrix[19]),
.c(i_vector[2]),
.d(i_vector[3]),
.re(re_toadd[9]),
.im(im_toadd[9]),
.ovr(ovr[9])
);

complex_mult #(N) ele_10(
.a(matrix[20]),
.b(matrix[21]),
.c(i_vector[4]),
.d(i_vector[5]),
.re(re_toadd[10]),
.im(im_toadd[10]),
.ovr(ovr[10])
);

complex_mult #(N) ele_11(
.a(matrix[22]),
.b(matrix[23]),
.c(i_vector[6]),
.d(i_vector[7]),
.re(re_toadd[11]),
.im(im_toadd[11]),
.ovr(ovr[11])
);

complex_mult #(N) ele_12(
.a(matrix[24]),
.b(matrix[25]),
.c(i_vector[0]),
.d(i_vector[1]),
.re(re_toadd[12]),
.im(im_toadd[12]),
.ovr(ovr[12])
);

complex_mult #(N) ele_13(
.a(matrix[26]),
.b(matrix[27]),
.c(i_vector[2]),
.d(i_vector[3]),
.re(re_toadd[13]),
.im(im_toadd[13]),
.ovr(ovr[13])
);

complex_mult #(N) ele_14(
.a(matrix[28]),
.b(matrix[29]),
.c(i_vector[4]),
.d(i_vector[5]),
.re(re_toadd[14]),
.im(im_toadd[14]),
.ovr(ovr[14])
);

complex_mult #(N) ele_15(
.a(matrix[30]),
.b(matrix[31]),
.c(i_vector[6]),
.d(i_vector[7]),
.re(re_toadd[15]),
.im(im_toadd[15]),
.ovr(ovr[15])
);

// Add complex products to find output vector
qadd #(N-1,N) re_sum_newrow_0 (
.a(re_toadd[0]),
.b(re_toadd[1]),
.c(re_sums[0])
);
qadd #(N-1,N) im_sum_newrow_0 (
.a(im_toadd[0]),
.b(im_toadd[1]),
.c(im_sums[0])
);
qadd #(N-1,N) re_sum_00 (
.a(re_toadd[2]),
.b(re_sums[0]),
.c(re_sums[1])
);
qadd #(N-1,N) im_sum_00 (
.a(im_toadd[2]),
.b(im_sums[0]),
.c(im_sums[1])
);
qadd #(N-1,N) re_sum_01 (
.a(re_toadd[3]),
.b(re_sums[1]),
.c(re_sums[2])
);
qadd #(N-1,N) im_sum_01 (
.a(im_toadd[3]),
.b(im_sums[1]),
.c(im_sums[2])
);
qadd #(N-1,N) re_sum_newrow_1 (
.a(re_toadd[4]),
.b(re_toadd[5]),
.c(re_sums[3])
);
qadd #(N-1,N) im_sum_newrow_1 (
.a(im_toadd[4]),
.b(im_toadd[5]),
.c(im_sums[3])
);
qadd #(N-1,N) re_sum_10 (
.a(re_toadd[6]),
.b(re_sums[3]),
.c(re_sums[4])
);
qadd #(N-1,N) im_sum_10 (
.a(im_toadd[6]),
.b(im_sums[3]),
.c(im_sums[4])
);
qadd #(N-1,N) re_sum_11 (
.a(re_toadd[7]),
.b(re_sums[4]),
.c(re_sums[5])
);
qadd #(N-1,N) im_sum_11 (
.a(im_toadd[7]),
.b(im_sums[4]),
.c(im_sums[5])
);
qadd #(N-1,N) re_sum_newrow_2 (
.a(re_toadd[8]),
.b(re_toadd[9]),
.c(re_sums[6])
);
qadd #(N-1,N) im_sum_newrow_2 (
.a(im_toadd[8]),
.b(im_toadd[9]),
.c(im_sums[6])
);
qadd #(N-1,N) re_sum_20 (
.a(re_toadd[10]),
.b(re_sums[6]),
.c(re_sums[7])
);
qadd #(N-1,N) im_sum_20 (
.a(im_toadd[10]),
.b(im_sums[6]),
.c(im_sums[7])
);
qadd #(N-1,N) re_sum_21 (
.a(re_toadd[11]),
.b(re_sums[7]),
.c(re_sums[8])
);
qadd #(N-1,N) im_sum_21 (
.a(im_toadd[11]),
.b(im_sums[7]),
.c(im_sums[8])
);
qadd #(N-1,N) re_sum_newrow_3 (
.a(re_toadd[12]),
.b(re_toadd[13]),
.c(re_sums[9])
);
qadd #(N-1,N) im_sum_newrow_3 (
.a(im_toadd[12]),
.b(im_toadd[13]),
.c(im_sums[9])
);
qadd #(N-1,N) re_sum_30 (
.a(re_toadd[14]),
.b(re_sums[9]),
.c(re_sums[10])
);
qadd #(N-1,N) im_sum_30 (
.a(im_toadd[14]),
.b(im_sums[9]),
.c(im_sums[10])
);
qadd #(N-1,N) re_sum_31 (
.a(re_toadd[15]),
.b(re_sums[10]),
.c(re_sums[11])
);
qadd #(N-1,N) im_sum_31 (
.a(im_toadd[15]),
.b(im_sums[10]),
.c(im_sums[11])
);

// assign sums to output
assign o_vector[0] = re_sums[2];
assign o_vector[1] = im_sums[2];
assign o_vector[2] = re_sums[5];
assign o_vector[3] = im_sums[5];
assign o_vector[4] = re_sums[8];
assign o_vector[5] = im_sums[8];
assign o_vector[6] = re_sums[11];
assign o_vector[7] = im_sums[11];

endmodule