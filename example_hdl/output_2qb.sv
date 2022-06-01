// Output module generated using c++
// sends final state-vector to arduino
module output_2qb #(
parameter N = 16
)
(
input [N-1:0] psi_f [0:127],
input wire i_clock,
input wire listener_flag,
output wire[7:0] out,
output wire parity
);

// used for iterating through output
integer n_num = 256;
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
    96: begin
         out_reg[7:0] <= psi_f[48][15:8];
         parity_reg <= ^psi_f[48][15:8];
       end
    97: begin
         out_reg[7:0] <= psi_f[48][7:0];
         parity_reg <= ^psi_f[48][7:0];
       end
    98: begin
         out_reg[7:0] <= psi_f[49][15:8];
         parity_reg <= ^psi_f[49][15:8];
       end
    99: begin
         out_reg[7:0] <= psi_f[49][7:0];
         parity_reg <= ^psi_f[49][7:0];
       end
    100: begin
         out_reg[7:0] <= psi_f[50][15:8];
         parity_reg <= ^psi_f[50][15:8];
       end
    101: begin
         out_reg[7:0] <= psi_f[50][7:0];
         parity_reg <= ^psi_f[50][7:0];
       end
    102: begin
         out_reg[7:0] <= psi_f[51][15:8];
         parity_reg <= ^psi_f[51][15:8];
       end
    103: begin
         out_reg[7:0] <= psi_f[51][7:0];
         parity_reg <= ^psi_f[51][7:0];
       end
    104: begin
         out_reg[7:0] <= psi_f[52][15:8];
         parity_reg <= ^psi_f[52][15:8];
       end
    105: begin
         out_reg[7:0] <= psi_f[52][7:0];
         parity_reg <= ^psi_f[52][7:0];
       end
    106: begin
         out_reg[7:0] <= psi_f[53][15:8];
         parity_reg <= ^psi_f[53][15:8];
       end
    107: begin
         out_reg[7:0] <= psi_f[53][7:0];
         parity_reg <= ^psi_f[53][7:0];
       end
    108: begin
         out_reg[7:0] <= psi_f[54][15:8];
         parity_reg <= ^psi_f[54][15:8];
       end
    109: begin
         out_reg[7:0] <= psi_f[54][7:0];
         parity_reg <= ^psi_f[54][7:0];
       end
    110: begin
         out_reg[7:0] <= psi_f[55][15:8];
         parity_reg <= ^psi_f[55][15:8];
       end
    111: begin
         out_reg[7:0] <= psi_f[55][7:0];
         parity_reg <= ^psi_f[55][7:0];
       end
    112: begin
         out_reg[7:0] <= psi_f[56][15:8];
         parity_reg <= ^psi_f[56][15:8];
       end
    113: begin
         out_reg[7:0] <= psi_f[56][7:0];
         parity_reg <= ^psi_f[56][7:0];
       end
    114: begin
         out_reg[7:0] <= psi_f[57][15:8];
         parity_reg <= ^psi_f[57][15:8];
       end
    115: begin
         out_reg[7:0] <= psi_f[57][7:0];
         parity_reg <= ^psi_f[57][7:0];
       end
    116: begin
         out_reg[7:0] <= psi_f[58][15:8];
         parity_reg <= ^psi_f[58][15:8];
       end
    117: begin
         out_reg[7:0] <= psi_f[58][7:0];
         parity_reg <= ^psi_f[58][7:0];
       end
    118: begin
         out_reg[7:0] <= psi_f[59][15:8];
         parity_reg <= ^psi_f[59][15:8];
       end
    119: begin
         out_reg[7:0] <= psi_f[59][7:0];
         parity_reg <= ^psi_f[59][7:0];
       end
    120: begin
         out_reg[7:0] <= psi_f[60][15:8];
         parity_reg <= ^psi_f[60][15:8];
       end
    121: begin
         out_reg[7:0] <= psi_f[60][7:0];
         parity_reg <= ^psi_f[60][7:0];
       end
    122: begin
         out_reg[7:0] <= psi_f[61][15:8];
         parity_reg <= ^psi_f[61][15:8];
       end
    123: begin
         out_reg[7:0] <= psi_f[61][7:0];
         parity_reg <= ^psi_f[61][7:0];
       end
    124: begin
         out_reg[7:0] <= psi_f[62][15:8];
         parity_reg <= ^psi_f[62][15:8];
       end
    125: begin
         out_reg[7:0] <= psi_f[62][7:0];
         parity_reg <= ^psi_f[62][7:0];
       end
    126: begin
         out_reg[7:0] <= psi_f[63][15:8];
         parity_reg <= ^psi_f[63][15:8];
       end
    127: begin
         out_reg[7:0] <= psi_f[63][7:0];
         parity_reg <= ^psi_f[63][7:0];
       end
    128: begin
         out_reg[7:0] <= psi_f[64][15:8];
         parity_reg <= ^psi_f[64][15:8];
       end
    129: begin
         out_reg[7:0] <= psi_f[64][7:0];
         parity_reg <= ^psi_f[64][7:0];
       end
    130: begin
         out_reg[7:0] <= psi_f[65][15:8];
         parity_reg <= ^psi_f[65][15:8];
       end
    131: begin
         out_reg[7:0] <= psi_f[65][7:0];
         parity_reg <= ^psi_f[65][7:0];
       end
    132: begin
         out_reg[7:0] <= psi_f[66][15:8];
         parity_reg <= ^psi_f[66][15:8];
       end
    133: begin
         out_reg[7:0] <= psi_f[66][7:0];
         parity_reg <= ^psi_f[66][7:0];
       end
    134: begin
         out_reg[7:0] <= psi_f[67][15:8];
         parity_reg <= ^psi_f[67][15:8];
       end
    135: begin
         out_reg[7:0] <= psi_f[67][7:0];
         parity_reg <= ^psi_f[67][7:0];
       end
    136: begin
         out_reg[7:0] <= psi_f[68][15:8];
         parity_reg <= ^psi_f[68][15:8];
       end
    137: begin
         out_reg[7:0] <= psi_f[68][7:0];
         parity_reg <= ^psi_f[68][7:0];
       end
    138: begin
         out_reg[7:0] <= psi_f[69][15:8];
         parity_reg <= ^psi_f[69][15:8];
       end
    139: begin
         out_reg[7:0] <= psi_f[69][7:0];
         parity_reg <= ^psi_f[69][7:0];
       end
    140: begin
         out_reg[7:0] <= psi_f[70][15:8];
         parity_reg <= ^psi_f[70][15:8];
       end
    141: begin
         out_reg[7:0] <= psi_f[70][7:0];
         parity_reg <= ^psi_f[70][7:0];
       end
    142: begin
         out_reg[7:0] <= psi_f[71][15:8];
         parity_reg <= ^psi_f[71][15:8];
       end
    143: begin
         out_reg[7:0] <= psi_f[71][7:0];
         parity_reg <= ^psi_f[71][7:0];
       end
    144: begin
         out_reg[7:0] <= psi_f[72][15:8];
         parity_reg <= ^psi_f[72][15:8];
       end
    145: begin
         out_reg[7:0] <= psi_f[72][7:0];
         parity_reg <= ^psi_f[72][7:0];
       end
    146: begin
         out_reg[7:0] <= psi_f[73][15:8];
         parity_reg <= ^psi_f[73][15:8];
       end
    147: begin
         out_reg[7:0] <= psi_f[73][7:0];
         parity_reg <= ^psi_f[73][7:0];
       end
    148: begin
         out_reg[7:0] <= psi_f[74][15:8];
         parity_reg <= ^psi_f[74][15:8];
       end
    149: begin
         out_reg[7:0] <= psi_f[74][7:0];
         parity_reg <= ^psi_f[74][7:0];
       end
    150: begin
         out_reg[7:0] <= psi_f[75][15:8];
         parity_reg <= ^psi_f[75][15:8];
       end
    151: begin
         out_reg[7:0] <= psi_f[75][7:0];
         parity_reg <= ^psi_f[75][7:0];
       end
    152: begin
         out_reg[7:0] <= psi_f[76][15:8];
         parity_reg <= ^psi_f[76][15:8];
       end
    153: begin
         out_reg[7:0] <= psi_f[76][7:0];
         parity_reg <= ^psi_f[76][7:0];
       end
    154: begin
         out_reg[7:0] <= psi_f[77][15:8];
         parity_reg <= ^psi_f[77][15:8];
       end
    155: begin
         out_reg[7:0] <= psi_f[77][7:0];
         parity_reg <= ^psi_f[77][7:0];
       end
    156: begin
         out_reg[7:0] <= psi_f[78][15:8];
         parity_reg <= ^psi_f[78][15:8];
       end
    157: begin
         out_reg[7:0] <= psi_f[78][7:0];
         parity_reg <= ^psi_f[78][7:0];
       end
    158: begin
         out_reg[7:0] <= psi_f[79][15:8];
         parity_reg <= ^psi_f[79][15:8];
       end
    159: begin
         out_reg[7:0] <= psi_f[79][7:0];
         parity_reg <= ^psi_f[79][7:0];
       end
    160: begin
         out_reg[7:0] <= psi_f[80][15:8];
         parity_reg <= ^psi_f[80][15:8];
       end
    161: begin
         out_reg[7:0] <= psi_f[80][7:0];
         parity_reg <= ^psi_f[80][7:0];
       end
    162: begin
         out_reg[7:0] <= psi_f[81][15:8];
         parity_reg <= ^psi_f[81][15:8];
       end
    163: begin
         out_reg[7:0] <= psi_f[81][7:0];
         parity_reg <= ^psi_f[81][7:0];
       end
    164: begin
         out_reg[7:0] <= psi_f[82][15:8];
         parity_reg <= ^psi_f[82][15:8];
       end
    165: begin
         out_reg[7:0] <= psi_f[82][7:0];
         parity_reg <= ^psi_f[82][7:0];
       end
    166: begin
         out_reg[7:0] <= psi_f[83][15:8];
         parity_reg <= ^psi_f[83][15:8];
       end
    167: begin
         out_reg[7:0] <= psi_f[83][7:0];
         parity_reg <= ^psi_f[83][7:0];
       end
    168: begin
         out_reg[7:0] <= psi_f[84][15:8];
         parity_reg <= ^psi_f[84][15:8];
       end
    169: begin
         out_reg[7:0] <= psi_f[84][7:0];
         parity_reg <= ^psi_f[84][7:0];
       end
    170: begin
         out_reg[7:0] <= psi_f[85][15:8];
         parity_reg <= ^psi_f[85][15:8];
       end
    171: begin
         out_reg[7:0] <= psi_f[85][7:0];
         parity_reg <= ^psi_f[85][7:0];
       end
    172: begin
         out_reg[7:0] <= psi_f[86][15:8];
         parity_reg <= ^psi_f[86][15:8];
       end
    173: begin
         out_reg[7:0] <= psi_f[86][7:0];
         parity_reg <= ^psi_f[86][7:0];
       end
    174: begin
         out_reg[7:0] <= psi_f[87][15:8];
         parity_reg <= ^psi_f[87][15:8];
       end
    175: begin
         out_reg[7:0] <= psi_f[87][7:0];
         parity_reg <= ^psi_f[87][7:0];
       end
    176: begin
         out_reg[7:0] <= psi_f[88][15:8];
         parity_reg <= ^psi_f[88][15:8];
       end
    177: begin
         out_reg[7:0] <= psi_f[88][7:0];
         parity_reg <= ^psi_f[88][7:0];
       end
    178: begin
         out_reg[7:0] <= psi_f[89][15:8];
         parity_reg <= ^psi_f[89][15:8];
       end
    179: begin
         out_reg[7:0] <= psi_f[89][7:0];
         parity_reg <= ^psi_f[89][7:0];
       end
    180: begin
         out_reg[7:0] <= psi_f[90][15:8];
         parity_reg <= ^psi_f[90][15:8];
       end
    181: begin
         out_reg[7:0] <= psi_f[90][7:0];
         parity_reg <= ^psi_f[90][7:0];
       end
    182: begin
         out_reg[7:0] <= psi_f[91][15:8];
         parity_reg <= ^psi_f[91][15:8];
       end
    183: begin
         out_reg[7:0] <= psi_f[91][7:0];
         parity_reg <= ^psi_f[91][7:0];
       end
    184: begin
         out_reg[7:0] <= psi_f[92][15:8];
         parity_reg <= ^psi_f[92][15:8];
       end
    185: begin
         out_reg[7:0] <= psi_f[92][7:0];
         parity_reg <= ^psi_f[92][7:0];
       end
    186: begin
         out_reg[7:0] <= psi_f[93][15:8];
         parity_reg <= ^psi_f[93][15:8];
       end
    187: begin
         out_reg[7:0] <= psi_f[93][7:0];
         parity_reg <= ^psi_f[93][7:0];
       end
    188: begin
         out_reg[7:0] <= psi_f[94][15:8];
         parity_reg <= ^psi_f[94][15:8];
       end
    189: begin
         out_reg[7:0] <= psi_f[94][7:0];
         parity_reg <= ^psi_f[94][7:0];
       end
    190: begin
         out_reg[7:0] <= psi_f[95][15:8];
         parity_reg <= ^psi_f[95][15:8];
       end
    191: begin
         out_reg[7:0] <= psi_f[95][7:0];
         parity_reg <= ^psi_f[95][7:0];
       end
    192: begin
         out_reg[7:0] <= psi_f[96][15:8];
         parity_reg <= ^psi_f[96][15:8];
       end
    193: begin
         out_reg[7:0] <= psi_f[96][7:0];
         parity_reg <= ^psi_f[96][7:0];
       end
    194: begin
         out_reg[7:0] <= psi_f[97][15:8];
         parity_reg <= ^psi_f[97][15:8];
       end
    195: begin
         out_reg[7:0] <= psi_f[97][7:0];
         parity_reg <= ^psi_f[97][7:0];
       end
    196: begin
         out_reg[7:0] <= psi_f[98][15:8];
         parity_reg <= ^psi_f[98][15:8];
       end
    197: begin
         out_reg[7:0] <= psi_f[98][7:0];
         parity_reg <= ^psi_f[98][7:0];
       end
    198: begin
         out_reg[7:0] <= psi_f[99][15:8];
         parity_reg <= ^psi_f[99][15:8];
       end
    199: begin
         out_reg[7:0] <= psi_f[99][7:0];
         parity_reg <= ^psi_f[99][7:0];
       end
    200: begin
         out_reg[7:0] <= psi_f[100][15:8];
         parity_reg <= ^psi_f[100][15:8];
       end
    201: begin
         out_reg[7:0] <= psi_f[100][7:0];
         parity_reg <= ^psi_f[100][7:0];
       end
    202: begin
         out_reg[7:0] <= psi_f[101][15:8];
         parity_reg <= ^psi_f[101][15:8];
       end
    203: begin
         out_reg[7:0] <= psi_f[101][7:0];
         parity_reg <= ^psi_f[101][7:0];
       end
    204: begin
         out_reg[7:0] <= psi_f[102][15:8];
         parity_reg <= ^psi_f[102][15:8];
       end
    205: begin
         out_reg[7:0] <= psi_f[102][7:0];
         parity_reg <= ^psi_f[102][7:0];
       end
    206: begin
         out_reg[7:0] <= psi_f[103][15:8];
         parity_reg <= ^psi_f[103][15:8];
       end
    207: begin
         out_reg[7:0] <= psi_f[103][7:0];
         parity_reg <= ^psi_f[103][7:0];
       end
    208: begin
         out_reg[7:0] <= psi_f[104][15:8];
         parity_reg <= ^psi_f[104][15:8];
       end
    209: begin
         out_reg[7:0] <= psi_f[104][7:0];
         parity_reg <= ^psi_f[104][7:0];
       end
    210: begin
         out_reg[7:0] <= psi_f[105][15:8];
         parity_reg <= ^psi_f[105][15:8];
       end
    211: begin
         out_reg[7:0] <= psi_f[105][7:0];
         parity_reg <= ^psi_f[105][7:0];
       end
    212: begin
         out_reg[7:0] <= psi_f[106][15:8];
         parity_reg <= ^psi_f[106][15:8];
       end
    213: begin
         out_reg[7:0] <= psi_f[106][7:0];
         parity_reg <= ^psi_f[106][7:0];
       end
    214: begin
         out_reg[7:0] <= psi_f[107][15:8];
         parity_reg <= ^psi_f[107][15:8];
       end
    215: begin
         out_reg[7:0] <= psi_f[107][7:0];
         parity_reg <= ^psi_f[107][7:0];
       end
    216: begin
         out_reg[7:0] <= psi_f[108][15:8];
         parity_reg <= ^psi_f[108][15:8];
       end
    217: begin
         out_reg[7:0] <= psi_f[108][7:0];
         parity_reg <= ^psi_f[108][7:0];
       end
    218: begin
         out_reg[7:0] <= psi_f[109][15:8];
         parity_reg <= ^psi_f[109][15:8];
       end
    219: begin
         out_reg[7:0] <= psi_f[109][7:0];
         parity_reg <= ^psi_f[109][7:0];
       end
    220: begin
         out_reg[7:0] <= psi_f[110][15:8];
         parity_reg <= ^psi_f[110][15:8];
       end
    221: begin
         out_reg[7:0] <= psi_f[110][7:0];
         parity_reg <= ^psi_f[110][7:0];
       end
    222: begin
         out_reg[7:0] <= psi_f[111][15:8];
         parity_reg <= ^psi_f[111][15:8];
       end
    223: begin
         out_reg[7:0] <= psi_f[111][7:0];
         parity_reg <= ^psi_f[111][7:0];
       end
    224: begin
         out_reg[7:0] <= psi_f[112][15:8];
         parity_reg <= ^psi_f[112][15:8];
       end
    225: begin
         out_reg[7:0] <= psi_f[112][7:0];
         parity_reg <= ^psi_f[112][7:0];
       end
    226: begin
         out_reg[7:0] <= psi_f[113][15:8];
         parity_reg <= ^psi_f[113][15:8];
       end
    227: begin
         out_reg[7:0] <= psi_f[113][7:0];
         parity_reg <= ^psi_f[113][7:0];
       end
    228: begin
         out_reg[7:0] <= psi_f[114][15:8];
         parity_reg <= ^psi_f[114][15:8];
       end
    229: begin
         out_reg[7:0] <= psi_f[114][7:0];
         parity_reg <= ^psi_f[114][7:0];
       end
    230: begin
         out_reg[7:0] <= psi_f[115][15:8];
         parity_reg <= ^psi_f[115][15:8];
       end
    231: begin
         out_reg[7:0] <= psi_f[115][7:0];
         parity_reg <= ^psi_f[115][7:0];
       end
    232: begin
         out_reg[7:0] <= psi_f[116][15:8];
         parity_reg <= ^psi_f[116][15:8];
       end
    233: begin
         out_reg[7:0] <= psi_f[116][7:0];
         parity_reg <= ^psi_f[116][7:0];
       end
    234: begin
         out_reg[7:0] <= psi_f[117][15:8];
         parity_reg <= ^psi_f[117][15:8];
       end
    235: begin
         out_reg[7:0] <= psi_f[117][7:0];
         parity_reg <= ^psi_f[117][7:0];
       end
    236: begin
         out_reg[7:0] <= psi_f[118][15:8];
         parity_reg <= ^psi_f[118][15:8];
       end
    237: begin
         out_reg[7:0] <= psi_f[118][7:0];
         parity_reg <= ^psi_f[118][7:0];
       end
    238: begin
         out_reg[7:0] <= psi_f[119][15:8];
         parity_reg <= ^psi_f[119][15:8];
       end
    239: begin
         out_reg[7:0] <= psi_f[119][7:0];
         parity_reg <= ^psi_f[119][7:0];
       end
    240: begin
         out_reg[7:0] <= psi_f[120][15:8];
         parity_reg <= ^psi_f[120][15:8];
       end
    241: begin
         out_reg[7:0] <= psi_f[120][7:0];
         parity_reg <= ^psi_f[120][7:0];
       end
    242: begin
         out_reg[7:0] <= psi_f[121][15:8];
         parity_reg <= ^psi_f[121][15:8];
       end
    243: begin
         out_reg[7:0] <= psi_f[121][7:0];
         parity_reg <= ^psi_f[121][7:0];
       end
    244: begin
         out_reg[7:0] <= psi_f[122][15:8];
         parity_reg <= ^psi_f[122][15:8];
       end
    245: begin
         out_reg[7:0] <= psi_f[122][7:0];
         parity_reg <= ^psi_f[122][7:0];
       end
    246: begin
         out_reg[7:0] <= psi_f[123][15:8];
         parity_reg <= ^psi_f[123][15:8];
       end
    247: begin
         out_reg[7:0] <= psi_f[123][7:0];
         parity_reg <= ^psi_f[123][7:0];
       end
    248: begin
         out_reg[7:0] <= psi_f[124][15:8];
         parity_reg <= ^psi_f[124][15:8];
       end
    249: begin
         out_reg[7:0] <= psi_f[124][7:0];
         parity_reg <= ^psi_f[124][7:0];
       end
    250: begin
         out_reg[7:0] <= psi_f[125][15:8];
         parity_reg <= ^psi_f[125][15:8];
       end
    251: begin
         out_reg[7:0] <= psi_f[125][7:0];
         parity_reg <= ^psi_f[125][7:0];
       end
    252: begin
         out_reg[7:0] <= psi_f[126][15:8];
         parity_reg <= ^psi_f[126][15:8];
       end
    253: begin
         out_reg[7:0] <= psi_f[126][7:0];
         parity_reg <= ^psi_f[126][7:0];
       end
    254: begin
         out_reg[7:0] <= psi_f[127][15:8];
         parity_reg <= ^psi_f[127][15:8];
       end
    255: begin
         out_reg[7:0] <= psi_f[127][7:0];
         parity_reg <= ^psi_f[127][7:0];
       end
    default: out_reg[7:0] <= 8'b00000000;
    endcase
    i_num = i_num + 1;
end
endmodule