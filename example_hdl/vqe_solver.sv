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
parameter n_qb = 2;
reg source_flag_reg;
assign source_flag = source_flag_reg;
assign LEDR = source_flag_reg;

reg [N-1:0] y_0_0 [0:7];
reg [N-1:0] y_0_10472 [0:7];
reg [N-1:0] y_0_20944 [0:7];
reg [N-1:0] y_0_314159 [0:7];
reg [N-1:0] y_0_418879 [0:7];
reg [N-1:0] y_0_523599 [0:7];
reg [N-1:0] y_0_628319 [0:7];
reg [N-1:0] y_1_10472 [0:7];
reg [N-1:0] y_1_20944 [0:7];
reg [N-1:0] y_1_314159 [0:7];
reg [N-1:0] y_1_20944 [0:7];
reg [N-1:0] y_1_10472 [0:7];
reg [N-1:0] y_0_20944 [0:7];
reg [N-1:0] y_0_10472 [0:7];

initial begin
   source_flag_reg <= 1'b0;
   $readmemb("y_0_0.dat", y_0_0);
   $readmemb("y_0_10472.dat", y_0_10472);
   $readmemb("y_0_20944.dat", y_0_20944);
   $readmemb("y_0_314159.dat", y_0_314159);
   $readmemb("y_0_418879.dat", y_0_418879);
   $readmemb("y_0_523599.dat", y_0_523599);
   $readmemb("y_0_628319.dat", y_0_628319);
   $readmemb("y_1_10472.dat", y_1_10472);
   $readmemb("y_1_20944.dat", y_1_20944);
   $readmemb("y_1_314159.dat", y_1_314159);
   $readmemb("y_1_20944.dat", y_1_20944);
   $readmemb("y_1_10472.dat", y_1_10472);
   $readmemb("y_0_20944.dat", y_0_20944);
   $readmemb("y_0_10472.dat", y_0_10472);
end

reg [N-1:0] y0 [0:7];
reg [N-1:0] y1 [0:7];
reg [N-1:0] psi_f_temp [0:7];
reg [N-1:0] psi_f_reg [0:127];
wire [N-1:0] psi_f_array [0:127];
assign psi_f_array[0:127] = psi_f_reg[0:127];

variational_circuit2 circuit(
    .v_matrix0(y0),
    .v_matrix1(y1),
    .psi_f(psi_f_temp) 
);

clock_divider clk(
    .fast_clock(fpga_clock),
    .slow_clock(shared_clock)
);

output_2qb op(
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
            y1[0:7] <= y_0_0[0:7];
        end
        1: begin
            psi_f_reg[0:7] <= psi_f_temp[0:7];
        end

        2: begin
            y0[0:7] <= y_0_10472[0:7];
            y1[0:7] <= y_1_10472[0:7];
        end
        3: begin
            psi_f_reg[8:15] <= psi_f_temp[0:7];
        end

        4: begin
            y0[0:7] <= y_0_20944[0:7];
            y1[0:7] <= y_1_20944[0:7];
        end
        5: begin
            psi_f_reg[16:23] <= psi_f_temp[0:7];
        end

        6: begin
            y0[0:7] <= y_0_314159[0:7];
            y1[0:7] <= y_1_314159[0:7];
        end
        7: begin
            psi_f_reg[24:31] <= psi_f_temp[0:7];
        end

        8: begin
            y0[0:7] <= y_0_10472[0:7];
            y1[0:7] <= y_0_10472[0:7];
        end
        9: begin
            psi_f_reg[32:39] <= psi_f_temp[0:7];
        end

        10: begin
            y0[0:7] <= y_0_20944[0:7];
            y1[0:7] <= y_0_0[0:7];
        end
        11: begin
            psi_f_reg[40:47] <= psi_f_temp[0:7];
        end

        12: begin
            y0[0:7] <= y_0_314159[0:7];
            y1[0:7] <= y_1_10472[0:7];
        end
        13: begin
            psi_f_reg[48:55] <= psi_f_temp[0:7];
        end

        14: begin
            y0[0:7] <= y_0_418879[0:7];
            y1[0:7] <= y_1_20944[0:7];
        end
        15: begin
            psi_f_reg[56:63] <= psi_f_temp[0:7];
        end

        16: begin
            y0[0:7] <= y_0_20944[0:7];
            y1[0:7] <= y_0_20944[0:7];
        end
        17: begin
            psi_f_reg[64:71] <= psi_f_temp[0:7];
        end

        18: begin
            y0[0:7] <= y_0_314159[0:7];
            y1[0:7] <= y_0_10472[0:7];
        end
        19: begin
            psi_f_reg[72:79] <= psi_f_temp[0:7];
        end

        20: begin
            y0[0:7] <= y_0_418879[0:7];
            y1[0:7] <= y_0_0[0:7];
        end
        21: begin
            psi_f_reg[80:87] <= psi_f_temp[0:7];
        end

        22: begin
            y0[0:7] <= y_0_523599[0:7];
            y1[0:7] <= y_1_10472[0:7];
        end
        23: begin
            psi_f_reg[88:95] <= psi_f_temp[0:7];
        end

        24: begin
            y0[0:7] <= y_0_314159[0:7];
            y1[0:7] <= y_0_314159[0:7];
        end
        25: begin
            psi_f_reg[96:103] <= psi_f_temp[0:7];
        end

        26: begin
            y0[0:7] <= y_0_418879[0:7];
            y1[0:7] <= y_0_20944[0:7];
        end
        27: begin
            psi_f_reg[104:111] <= psi_f_temp[0:7];
        end

        28: begin
            y0[0:7] <= y_0_523599[0:7];
            y1[0:7] <= y_0_10472[0:7];
        end
        29: begin
            psi_f_reg[112:119] <= psi_f_temp[0:7];
        end

        30: begin
            y0[0:7] <= y_0_628319[0:7];
            y1[0:7] <= y_0_0[0:7];
        end
        31: begin
            psi_f_reg[120:127] <= psi_f_temp[0:7];
        end

        32: begin
            source_flag_reg <= 1'b1;
        end

    endcase
    i_ang = i_ang + 1;
end

endmodule