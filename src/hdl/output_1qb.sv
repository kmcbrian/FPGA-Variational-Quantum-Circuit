// Output module generated using c++
// sends final state-vector to arduino
module output_1qb #(
parameter N = 16
)
(
input [N-1:0] psi_f [0:47],
input wire i_clock,
input wire listener_flag,
output wire[7:0] out,
output wire parity
);

// used for iterating through output
integer n_num = 96;
integer i_num = 0;
reg [7:0] out_reg; // for assigning numbers in always block
assign out[7:0] = out_reg[7:0];
reg parity_reg;
assign parity = parity_reg;

// intialization of values
initial begin
    out_reg <= 8'b10001011;
    parity_reg <= 1'b0;
end


// transfer data to arduino
always @ (posedge listener_flag)
begin
    case(i_num)
    0: begin
         out_reg[7:0] <= psi_f[0][15:8];
         parity_reg <= ^psi_f[0][15:8];
       end
    1: begin
         out_reg[7:0] <= psi_f[0][7:0];
         parity_reg <= ^psi_f[0][7:0];
       end
    2: begin
         out_reg[7:0] <= psi_f[1][15:8];
         parity_reg <= ^psi_f[1][15:8];
       end
    3: begin
         out_reg[7:0] <= psi_f[1][7:0];
         parity_reg <= ^psi_f[1][7:0];
       end
    4: begin
         out_reg[7:0] <= psi_f[2][15:8];
         parity_reg <= ^psi_f[2][15:8];
       end
    5: begin
         out_reg[7:0] <= psi_f[2][7:0];
         parity_reg <= ^psi_f[2][7:0];
       end
    6: begin
         out_reg[7:0] <= psi_f[3][15:8];
         parity_reg <= ^psi_f[3][15:8];
       end
    7: begin
         out_reg[7:0] <= psi_f[3][7:0];
         parity_reg <= ^psi_f[3][7:0];
       end
    8: begin
         out_reg[7:0] <= psi_f[4][15:8];
         parity_reg <= ^psi_f[4][15:8];
       end
    9: begin
         out_reg[7:0] <= psi_f[4][7:0];
         parity_reg <= ^psi_f[4][7:0];
       end
    10: begin
         out_reg[7:0] <= psi_f[5][15:8];
         parity_reg <= ^psi_f[5][15:8];
       end
    11: begin
         out_reg[7:0] <= psi_f[5][7:0];
         parity_reg <= ^psi_f[5][7:0];
       end
    12: begin
         out_reg[7:0] <= psi_f[6][15:8];
         parity_reg <= ^psi_f[6][15:8];
       end
    13: begin
         out_reg[7:0] <= psi_f[6][7:0];
         parity_reg <= ^psi_f[6][7:0];
       end
    14: begin
         out_reg[7:0] <= psi_f[7][15:8];
         parity_reg <= ^psi_f[7][15:8];
       end
    15: begin
         out_reg[7:0] <= psi_f[7][7:0];
         parity_reg <= ^psi_f[7][7:0];
       end
    16: begin
         out_reg[7:0] <= psi_f[8][15:8];
         parity_reg <= ^psi_f[8][15:8];
       end
    17: begin
         out_reg[7:0] <= psi_f[8][7:0];
         parity_reg <= ^psi_f[8][7:0];
       end
    18: begin
         out_reg[7:0] <= psi_f[9][15:8];
         parity_reg <= ^psi_f[9][15:8];
       end
    19: begin
         out_reg[7:0] <= psi_f[9][7:0];
         parity_reg <= ^psi_f[9][7:0];
       end
    20: begin
         out_reg[7:0] <= psi_f[10][15:8];
         parity_reg <= ^psi_f[10][15:8];
       end
    21: begin
         out_reg[7:0] <= psi_f[10][7:0];
         parity_reg <= ^psi_f[10][7:0];
       end
    22: begin
         out_reg[7:0] <= psi_f[11][15:8];
         parity_reg <= ^psi_f[11][15:8];
       end
    23: begin
         out_reg[7:0] <= psi_f[11][7:0];
         parity_reg <= ^psi_f[11][7:0];
       end
    24: begin
         out_reg[7:0] <= psi_f[12][15:8];
         parity_reg <= ^psi_f[12][15:8];
       end
    25: begin
         out_reg[7:0] <= psi_f[12][7:0];
         parity_reg <= ^psi_f[12][7:0];
       end
    26: begin
         out_reg[7:0] <= psi_f[13][15:8];
         parity_reg <= ^psi_f[13][15:8];
       end
    27: begin
         out_reg[7:0] <= psi_f[13][7:0];
         parity_reg <= ^psi_f[13][7:0];
       end
    28: begin
         out_reg[7:0] <= psi_f[14][15:8];
         parity_reg <= ^psi_f[14][15:8];
       end
    29: begin
         out_reg[7:0] <= psi_f[14][7:0];
         parity_reg <= ^psi_f[14][7:0];
       end
    30: begin
         out_reg[7:0] <= psi_f[15][15:8];
         parity_reg <= ^psi_f[15][15:8];
       end
    31: begin
         out_reg[7:0] <= psi_f[15][7:0];
         parity_reg <= ^psi_f[15][7:0];
       end
    32: begin
         out_reg[7:0] <= psi_f[16][15:8];
         parity_reg <= ^psi_f[16][15:8];
       end
    33: begin
         out_reg[7:0] <= psi_f[16][7:0];
         parity_reg <= ^psi_f[16][7:0];
       end
    34: begin
         out_reg[7:0] <= psi_f[17][15:8];
         parity_reg <= ^psi_f[17][15:8];
       end
    35: begin
         out_reg[7:0] <= psi_f[17][7:0];
         parity_reg <= ^psi_f[17][7:0];
       end
    36: begin
         out_reg[7:0] <= psi_f[18][15:8];
         parity_reg <= ^psi_f[18][15:8];
       end
    37: begin
         out_reg[7:0] <= psi_f[18][7:0];
         parity_reg <= ^psi_f[18][7:0];
       end
    38: begin
         out_reg[7:0] <= psi_f[19][15:8];
         parity_reg <= ^psi_f[19][15:8];
       end
    39: begin
         out_reg[7:0] <= psi_f[19][7:0];
         parity_reg <= ^psi_f[19][7:0];
       end
    40: begin
         out_reg[7:0] <= psi_f[20][15:8];
         parity_reg <= ^psi_f[20][15:8];
       end
    41: begin
         out_reg[7:0] <= psi_f[20][7:0];
         parity_reg <= ^psi_f[20][7:0];
       end
    42: begin
         out_reg[7:0] <= psi_f[21][15:8];
         parity_reg <= ^psi_f[21][15:8];
       end
    43: begin
         out_reg[7:0] <= psi_f[21][7:0];
         parity_reg <= ^psi_f[21][7:0];
       end
    44: begin
         out_reg[7:0] <= psi_f[22][15:8];
         parity_reg <= ^psi_f[22][15:8];
       end
    45: begin
         out_reg[7:0] <= psi_f[22][7:0];
         parity_reg <= ^psi_f[22][7:0];
       end
    46: begin
         out_reg[7:0] <= psi_f[23][15:8];
         parity_reg <= ^psi_f[23][15:8];
       end
    47: begin
         out_reg[7:0] <= psi_f[23][7:0];
         parity_reg <= ^psi_f[23][7:0];
       end
    48: begin
         out_reg[7:0] <= psi_f[24][15:8];
         parity_reg <= ^psi_f[24][15:8];
       end
    49: begin
         out_reg[7:0] <= psi_f[24][7:0];
         parity_reg <= ^psi_f[24][7:0];
       end
    50: begin
         out_reg[7:0] <= psi_f[25][15:8];
         parity_reg <= ^psi_f[25][15:8];
       end
    51: begin
         out_reg[7:0] <= psi_f[25][7:0];
         parity_reg <= ^psi_f[25][7:0];
       end
    52: begin
         out_reg[7:0] <= psi_f[26][15:8];
         parity_reg <= ^psi_f[26][15:8];
       end
    53: begin
         out_reg[7:0] <= psi_f[26][7:0];
         parity_reg <= ^psi_f[26][7:0];
       end
    54: begin
         out_reg[7:0] <= psi_f[27][15:8];
         parity_reg <= ^psi_f[27][15:8];
       end
    55: begin
         out_reg[7:0] <= psi_f[27][7:0];
         parity_reg <= ^psi_f[27][7:0];
       end
    56: begin
         out_reg[7:0] <= psi_f[28][15:8];
         parity_reg <= ^psi_f[28][15:8];
       end
    57: begin
         out_reg[7:0] <= psi_f[28][7:0];
         parity_reg <= ^psi_f[28][7:0];
       end
    58: begin
         out_reg[7:0] <= psi_f[29][15:8];
         parity_reg <= ^psi_f[29][15:8];
       end
    59: begin
         out_reg[7:0] <= psi_f[29][7:0];
         parity_reg <= ^psi_f[29][7:0];
       end
    60: begin
         out_reg[7:0] <= psi_f[30][15:8];
         parity_reg <= ^psi_f[30][15:8];
       end
    61: begin
         out_reg[7:0] <= psi_f[30][7:0];
         parity_reg <= ^psi_f[30][7:0];
       end
    62: begin
         out_reg[7:0] <= psi_f[31][15:8];
         parity_reg <= ^psi_f[31][15:8];
       end
    63: begin
         out_reg[7:0] <= psi_f[31][7:0];
         parity_reg <= ^psi_f[31][7:0];
       end
    64: begin
         out_reg[7:0] <= psi_f[32][15:8];
         parity_reg <= ^psi_f[32][15:8];
       end
    65: begin
         out_reg[7:0] <= psi_f[32][7:0];
         parity_reg <= ^psi_f[32][7:0];
       end
    66: begin
         out_reg[7:0] <= psi_f[33][15:8];
         parity_reg <= ^psi_f[33][15:8];
       end
    67: begin
         out_reg[7:0] <= psi_f[33][7:0];
         parity_reg <= ^psi_f[33][7:0];
       end
    68: begin
         out_reg[7:0] <= psi_f[34][15:8];
         parity_reg <= ^psi_f[34][15:8];
       end
    69: begin
         out_reg[7:0] <= psi_f[34][7:0];
         parity_reg <= ^psi_f[34][7:0];
       end
    70: begin
         out_reg[7:0] <= psi_f[35][15:8];
         parity_reg <= ^psi_f[35][15:8];
       end
    71: begin
         out_reg[7:0] <= psi_f[35][7:0];
         parity_reg <= ^psi_f[35][7:0];
       end
    72: begin
         out_reg[7:0] <= psi_f[36][15:8];
         parity_reg <= ^psi_f[36][15:8];
       end
    73: begin
         out_reg[7:0] <= psi_f[36][7:0];
         parity_reg <= ^psi_f[36][7:0];
       end
    74: begin
         out_reg[7:0] <= psi_f[37][15:8];
         parity_reg <= ^psi_f[37][15:8];
       end
    75: begin
         out_reg[7:0] <= psi_f[37][7:0];
         parity_reg <= ^psi_f[37][7:0];
       end
    76: begin
         out_reg[7:0] <= psi_f[38][15:8];
         parity_reg <= ^psi_f[38][15:8];
       end
    77: begin
         out_reg[7:0] <= psi_f[38][7:0];
         parity_reg <= ^psi_f[38][7:0];
       end
    78: begin
         out_reg[7:0] <= psi_f[39][15:8];
         parity_reg <= ^psi_f[39][15:8];
       end
    79: begin
         out_reg[7:0] <= psi_f[39][7:0];
         parity_reg <= ^psi_f[39][7:0];
       end
    80: begin
         out_reg[7:0] <= psi_f[40][15:8];
         parity_reg <= ^psi_f[40][15:8];
       end
    81: begin
         out_reg[7:0] <= psi_f[40][7:0];
         parity_reg <= ^psi_f[40][7:0];
       end
    82: begin
         out_reg[7:0] <= psi_f[41][15:8];
         parity_reg <= ^psi_f[41][15:8];
       end
    83: begin
         out_reg[7:0] <= psi_f[41][7:0];
         parity_reg <= ^psi_f[41][7:0];
       end
    84: begin
         out_reg[7:0] <= psi_f[42][15:8];
         parity_reg <= ^psi_f[42][15:8];
       end
    85: begin
         out_reg[7:0] <= psi_f[42][7:0];
         parity_reg <= ^psi_f[42][7:0];
       end
    86: begin
         out_reg[7:0] <= psi_f[43][15:8];
         parity_reg <= ^psi_f[43][15:8];
       end
    87: begin
         out_reg[7:0] <= psi_f[43][7:0];
         parity_reg <= ^psi_f[43][7:0];
       end
    88: begin
         out_reg[7:0] <= psi_f[44][15:8];
         parity_reg <= ^psi_f[44][15:8];
       end
    89: begin
         out_reg[7:0] <= psi_f[44][7:0];
         parity_reg <= ^psi_f[44][7:0];
       end
    90: begin
         out_reg[7:0] <= psi_f[45][15:8];
         parity_reg <= ^psi_f[45][15:8];
       end
    91: begin
         out_reg[7:0] <= psi_f[45][7:0];
         parity_reg <= ^psi_f[45][7:0];
       end
    92: begin
         out_reg[7:0] <= psi_f[46][15:8];
         parity_reg <= ^psi_f[46][15:8];
       end
    93: begin
         out_reg[7:0] <= psi_f[46][7:0];
         parity_reg <= ^psi_f[46][7:0];
       end
    94: begin
         out_reg[7:0] <= psi_f[47][15:8];
         parity_reg <= ^psi_f[47][15:8];
       end
    95: begin
         out_reg[7:0] <= psi_f[47][7:0];
         parity_reg <= ^psi_f[47][7:0];
       end
    default: out_reg[7:0] <= 8'b00000000;
    endcase
    i_num = i_num + 1;
end
endmodule