module complex_mult #(
		parameter N = 16 // data size
		)
		(
		// inputs: (a+ib)(c+id)
		input [N-1:0] a,
		input [N-1:0] b,
		input [N-1:0] c,
		input [N-1:0] d,
		output [N-1:0] re,  // = ac-bd
		output [N-1:0] im, // = ad+bc
		output ovr);


	wire [N-1:0] ac;
	wire [N-1:0] bd;
	wire [N-1:0] neg_bd; // first bit flipped from bd
	wire [N-1:0] bc;
	wire [N-1:0] ad;
	
	wire ovr_ac;
	wire ovr_bd;
	wire ovr_bc;
	wire ovr_ad;
	wire ovr_re; // need overflow flag
	wire ovr_im; // for addition

	qmult #(N-1,N) ac_mult (
		.i_multiplicand(a), 
		.i_multiplier(c), 
		.o_result(ac),
		.ovr(ovr_ac)
	);

	qmult #(N-1,N) bd_mult (
		.i_multiplicand(b), 
		.i_multiplier(d), 
		.o_result(bd),
		.ovr(ovr_bd)
	);
	
	qmult #(N-1,N) bc_mult (
		.i_multiplicand(b), 
		.i_multiplier(c), 
		.o_result(bc),
		.ovr(ovr_bc)
	);

	qmult #(N-1,N) ad_mult (
		.i_multiplicand(a), 
		.i_multiplier(d), 
		.o_result(ad),
		.ovr(ovr_ad)
	);

	qadd #(N-1,N) re_sum (
		.a(ac), 
		.b(neg_bd), 
		.c(re)
	);
	
	qadd #(N-1,N) im_sum (
		.a(ad), 
		.b(bc), 
		.c(im)
	);

assign neg_bd[N-2:0] = bd[N-2:0];
assign neg_bd[N-1] = ~bd[N-1];

assign ovr = ovr_ac | ovr_bd | ovr_bc | ovr_ad;


endmodule
