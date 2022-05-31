`timescale 1ns/1ps
module vqe_solver(
    input wire listener_flag,
    input wire fpga_clock,
    output wire shared_clock,
    output wire LEDR,
    output wire[7:0] out,
    output wire source_flag,
    output wire parity 
);

parameter N = 16;
parameter n_qb = 1;
reg source_flag_reg;
assign source_flag = source_flag_reg;
assign LEDR = source_flag_reg;

reg [N-1:0] y_0_0 [0:7];
reg [N-1:0] y_0_0571199 [0:7];
reg [N-1:0] y_0_11424 [0:7];
reg [N-1:0] y_0_17136 [0:7];
reg [N-1:0] y_0_228479 [0:7];
reg [N-1:0] y_0_285599 [0:7];
reg [N-1:0] y_0_342719 [0:7];
reg [N-1:0] y_0_399839 [0:7];
reg [N-1:0] y_0_456959 [0:7];
reg [N-1:0] y_0_514079 [0:7];
reg [N-1:0] y_0_571199 [0:7];
reg [N-1:0] y_0_628319 [0:7];

initial begin
   source_flag_reg <= 1'b0;
   $readmemb("y_0_0.dat", y_0_0);
   $readmemb("y_0_0571199.dat", y_0_0571199);
   $readmemb("y_0_11424.dat", y_0_11424);
   $readmemb("y_0_17136.dat", y_0_17136);
   $readmemb("y_0_228479.dat", y_0_228479);
   $readmemb("y_0_285599.dat", y_0_285599);
   $readmemb("y_0_342719.dat", y_0_342719);
   $readmemb("y_0_399839.dat", y_0_399839);
   $readmemb("y_0_456959.dat", y_0_456959);
   $readmemb("y_0_514079.dat", y_0_514079);
   $readmemb("y_0_571199.dat", y_0_571199);
   $readmemb("y_0_628319.dat", y_0_628319);
end

reg [N-1:0] y0 [0:7];
reg [N-1:0] psi_f_temp [0:3];
reg [N-1:0] psi_f_reg [0:47];
wire [N-1:0] psi_f_array [0:47];
assign psi_f_array[0:47] = psi_f_reg[0:47];

variational_circuit1 circuit(
    .v_matrix0(y0),
    .psi_f(psi_f_temp) 
);

clock_divider clk(
    .fast_clock(fpga_clock),
    .slow_clock(shared_clock)
);

output_1qb op(
    .psi_f(psi_f_array),
    .i_clock(shared_clock),
    .listener_flag(listener_flag),
    .out(out),
    .parity(parity)
);

integer i_ang = 0;
always @ (posedge shared_clock)
begin
    case(i_ang)
        0: begin
            y0[0:7] <= y_0_0[0:7];
        end
        1: begin
            psi_f_reg[0:3] <= psi_f_temp[0:3];
        end

        2: begin
            y0[0:7] <= y_0_0571199[0:7];
        end
        3: begin
            psi_f_reg[4:7] <= psi_f_temp[0:3];
        end

        4: begin
            y0[0:7] <= y_0_11424[0:7];
        end
        5: begin
            psi_f_reg[8:11] <= psi_f_temp[0:3];
        end

        6: begin
            y0[0:7] <= y_0_17136[0:7];
        end
        7: begin
            psi_f_reg[12:15] <= psi_f_temp[0:3];
        end

        8: begin
            y0[0:7] <= y_0_228479[0:7];
        end
        9: begin
            psi_f_reg[16:19] <= psi_f_temp[0:3];
        end

        10: begin
            y0[0:7] <= y_0_285599[0:7];
        end
        11: begin
            psi_f_reg[20:23] <= psi_f_temp[0:3];
        end

        12: begin
            y0[0:7] <= y_0_342719[0:7];
        end
        13: begin
            psi_f_reg[24:27] <= psi_f_temp[0:3];
        end

        14: begin
            y0[0:7] <= y_0_399839[0:7];
        end
        15: begin
            psi_f_reg[28:31] <= psi_f_temp[0:3];
        end

        16: begin
            y0[0:7] <= y_0_456959[0:7];
        end
        17: begin
            psi_f_reg[32:35] <= psi_f_temp[0:3];
        end

        18: begin
            y0[0:7] <= y_0_514079[0:7];
        end
        19: begin
            psi_f_reg[36:39] <= psi_f_temp[0:3];
        end

        20: begin
            y0[0:7] <= y_0_571199[0:7];
        end
        21: begin
            psi_f_reg[40:43] <= psi_f_temp[0:3];
        end

        22: begin
            y0[0:7] <= y_0_628319[0:7];
        end
        23: begin
            psi_f_reg[44:47] <= psi_f_temp[0:3];
        end

        24: begin
            source_flag_reg <= 1'b1;
        end

    endcase
    i_ang = i_ang + 1;
end

endmodule