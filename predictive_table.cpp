#include "predictive_table.hpp"
#include <unordered_map>

std::vector<std::vector<std::vector<int>>> table(63, std::vector<std::vector<int>>(62));

void initialize_table()
{
    table[1][2] = {2, -3, -4, -5, 3, -6};
    table[2][5] = {3, -1};
    table[2][7] = {3, 4, 5};
    table[2][10] = {3, 4, 5};
    table[2][13] = {3, -1};
    table[2][14] = {3, 4, 5};
    table[4][5] = {5, -1};
    table[4][6] = {5, -7, 3};
    table[4][13] = {5, -1};
    table[3][7] = {4, 6};
    table[3][10] = {4, 7};
    table[3][14] = {4, 8};
    table[5][7] = {6, -8, -4, 9};
    table[8][8] = {9, -9, 10, 11};
    table[8][9] = {9, -10, 12};
    table[10][5] = {11, -1};
    table[10][6] = {11, -1};
    table[10][9] = {11, -10, 12};
    table[10][13] = {11, -1};
    table[6][10] = {7, -11, -4, -12, 13, -13, 14};
    table[13][4] = {14, 15};
    table[13][8] = {14, -9, 10, 15};
    table[14][4] = {15, -5, 16, 17, -6};
    table[15][3] = {16, -1};
    table[15][5] = {16, -1};
    table[15][7] = {16, 4, 5, -14};
    table[15][10] = {16, 4, 5, -14};
    table[15][14] = {16, 4, 5, -14};
    table[15][19] = {16, -1};
    table[15][22] = {16, -1};
    table[15][25] = {16, -1};
    table[15][32] = {16, -1};
    table[15][33] = {16, -1};
    table[15][40] = {16, -1};
    table[7][14] = {8, -15, -4, -16, 18, -17};
    table[17][3] = {18, 19, 20};
    table[17][16] = {18, -1};
    table[19][6] = {20, -7, 18};
    table[19][16] = {20, -1};
    table[18][3] = {19, -4, -9, 10};
    table[12][3] = {13, 19, 21};
    table[12][12] = {13, -1};
    table[20][12] = {21, -1};
    table[20][17] = {21, -18, 13};
    table[16][3] = {17, 22, 23};
    table[16][5] = {17, -1};
    table[16][19] = {17, 22, 23};
    table[16][21] = {17, -1};
    table[16][22] = {17, 22, 23};
    table[16][24] = {17, -1};
    table[16][25] = {17, 22, 23};
    table[16][27] = {17, -1};
    table[16][28] = {17, -1};
    table[16][29] = {17, -1};
    table[16][31] = {17, -1};
    table[16][32] = {17, 22, 23};
    table[16][33] = {17, 22, 23};
    table[16][40] = {17, 22, 23};
    table[22][5] = {23, -1};
    table[22][6] = {23, -7, 17};
    table[22][21] = {23, -1};
    table[22][24] = {23, -1};
    table[22][27] = {23, -1};
    table[22][28] = {23, -1};
    table[22][29] = {23, -1};
    table[22][31] = {23, -1};
    table[21][3] = {22, 24};
    table[21][19] = {22, 25};
    table[21][22] = {22, 25};
    table[21][25] = {22, 25};
    table[21][32] = {22, 26};
    table[21][33] = {22, 27};
    table[21][40] = {22, 24};
    table[23][3] = {24, 28, 29, -10, -19};
    table[23][40] = {24, 30, -10, 12};
    table[30][3] = {31, 12, 32};
    table[30][11] = {31, 12, 32};
    table[30][12] = {31, -1};
    table[30][29] = {31, 12, 32};
    table[30][36] = {31, 12, 32};
    table[30][38] = {31, 12, 32};
    table[30][39] = {31, 12, 32};
    table[30][40] = {31, 12, 32};
    table[30][53] = {31, 12, 32};
    table[30][54] = {31, 12, 32};
    table[30][55] = {31, 12, 32};
    table[30][56] = {31, 12, 32};
    table[30][57] = {31, 12, 32};
    table[31][12] = {32, -1};
    table[31][17] = {32, -18, 31};
    table[24][19] = {25, -20, 12, -21, 17, 33, -22};
    table[24][22] = {25, -23, 12, -24, 17, 33, -25};
    table[24][25] = {25, -26, 12, -27, 34, 35, -28};
    table[32][21] = {33, -1};
    table[32][24] = {33, -1};
    table[32][28] = {33, -29, 17};
    table[33][29] = {34, 36, 37};
    table[36][27] = {37, -1};
    table[36][29] = {37, 34};
    table[36][31] = {37, -1};
    table[35][29] = {36, 38, -9, 17};
    table[37][29] = {38, 39, 40};
    table[39][8] = {40, -1};
    table[39][17] = {40, -18, 38};
    table[38][29] = {39, -30, 41};
    table[40][8] = {41, -1};
    table[40][17] = {41, -1};
    table[40][30] = {41, -31, -30};
    table[34][27] = {35, -1};
    table[34][31] = {35, -32, 17};
    table[25][32] = {26, -33, 12, -24, 17, -25};
    table[26][33] = {27, -34, 12};
    table[11][3] = {12, 42, 43};
    table[11][11] = {12, 42, 43};
    table[11][29] = {12, 42, 43};
    table[11][36] = {12, 42, 43};
    table[11][38] = {12, 42, 43};
    table[11][39] = {12, 42, 43};
    table[11][40] = {12, 42, 43};
    table[11][53] = {12, 42, 43};
    table[11][54] = {12, 42, 43};
    table[11][55] = {12, 42, 43};
    table[11][56] = {12, 42, 43};
    table[11][57] = {12, 42, 43};
    table[42][5] = {43, -1};
    table[42][6] = {43, -1};
    table[42][12] = {43, -1};
    table[42][13] = {43, -1};
    table[42][17] = {43, -1};
    table[42][20] = {43, -1};
    table[42][21] = {43, -1};
    table[42][23] = {43, -1};
    table[42][24] = {43, -1};
    table[42][26] = {43, -1};
    table[42][27] = {43, -1};
    table[42][28] = {43, -1};
    table[42][29] = {43, -1};
    table[42][31] = {43, -1};
    table[42][34] = {43, -35, 42, 43};
    table[41][3] = {42, 44, 45};
    table[41][11] = {42, 44, 45};
    table[41][29] = {42, 44, 45};
    table[41][36] = {42, 44, 45};
    table[41][38] = {42, 44, 45};
    table[41][39] = {42, 44, 45};
    table[41][40] = {42, 44, 45};
    table[41][53] = {42, 44, 45};
    table[41][54] = {42, 44, 45};
    table[41][55] = {42, 44, 45};
    table[41][56] = {42, 44, 45};
    table[41][57] = {42, 44, 45};
    table[44][5] = {45, -1};
    table[44][6] = {45, -1};
    table[44][12] = {45, -1};
    table[44][13] = {45, -1};
    table[44][17] = {45, -1};
    table[44][20] = {45, -1};
    table[44][21] = {45, -1};
    table[44][23] = {45, -1};
    table[44][24] = {45, -1};
    table[44][26] = {45, -1};
    table[44][27] = {45, -1};
    table[44][28] = {45, -1};
    table[44][29] = {45, -1};
    table[44][31] = {45, -1};
    table[44][34] = {45, -1};
    table[44][35] = {45, -36, 44, 45};
    table[43][3] = {44, 46};
    table[43][11] = {44, 46};
    table[43][29] = {44, 46};
    table[43][36] = {44, -37, 46};
    table[43][38] = {44, 46};
    table[43][39] = {44, 46};
    table[43][40] = {44, 46};
    table[43][53] = {44, 46};
    table[43][54] = {44, 46};
    table[43][55] = {44, 46};
    table[43][56] = {44, 46};
    table[43][57] = {44, 46};
    table[45][3] = {46, 47, 48};
    table[45][11] = {46, 47, 48};
    table[45][29] = {46, 47, 48};
    table[45][38] = {46, 47, 48};
    table[45][39] = {46, 47, 48};
    table[45][40] = {46, 47, 48};
    table[45][53] = {46, 47, 48};
    table[45][54] = {46, 47, 48};
    table[45][55] = {46, 47, 48};
    table[45][56] = {46, 47, 48};
    table[45][57] = {46, 47, 48};
    table[47][5] = {48, -1};
    table[47][6] = {48, -1};
    table[47][12] = {48, -1};
    table[47][13] = {48, -1};
    table[47][17] = {48, -1};
    table[47][20] = {48, -1};
    table[47][21] = {48, -1};
    table[47][23] = {48, -1};
    table[47][24] = {48, -1};
    table[47][26] = {48, -1};
    table[47][27] = {48, -1};
    table[47][28] = {48, -1};
    table[47][29] = {48, -1};
    table[47][31] = {48, -1};
    table[47][34] = {48, -1};
    table[47][35] = {48, -1};
    table[47][43] = {48, 49, 47, 48};
    table[47][44] = {48, 49, 47, 48};
    table[47][45] = {48, 49, 47, 48};
    table[47][46] = {48, 49, 47, 48};
    table[47][47] = {48, 49, 47, 48};
    table[47][48] = {48, 49, 47, 48};
    table[46][3] = {47, 50, 51};
    table[46][11] = {47, 50, 51};
    table[46][29] = {47, 50, 51};
    table[46][38] = {47, 50, 51};
    table[46][39] = {47, 50, 51};
    table[46][40] = {47, 50, 51};
    table[46][53] = {47, 50, 51};
    table[46][54] = {47, 50, 51};
    table[46][55] = {47, 50, 51};
    table[46][56] = {47, 50, 51};
    table[46][57] = {47, 50, 51};
    table[50][5] = {51, -1};
    table[50][6] = {51, -1};
    table[50][12] = {51, -1};
    table[50][13] = {51, -1};
    table[50][17] = {51, -1};
    table[50][20] = {51, -1};
    table[50][21] = {51, -1};
    table[50][23] = {51, -1};
    table[50][24] = {51, -1};
    table[50][26] = {51, -1};
    table[50][27] = {51, -1};
    table[50][28] = {51, -1};
    table[50][29] = {51, -1};
    table[50][31] = {51, -1};
    table[50][34] = {51, -1};
    table[50][35] = {51, -1};
    table[50][43] = {51, -1};
    table[50][44] = {51, -1};
    table[50][45] = {51, -1};
    table[50][46] = {51, -1};
    table[50][47] = {51, -1};
    table[50][48] = {51, -1};
    table[50][49] = {51, 52, 50, 51};
    table[50][50] = {51, 52, 50, 51};
    table[49][3] = {50, 53, 54};
    table[49][11] = {50, 53, 54};
    table[49][29] = {50, 53, 54};
    table[49][38] = {50, 53, 54};
    table[49][39] = {50, 53, 54};
    table[49][40] = {50, 53, 54};
    table[49][53] = {50, 53, 54};
    table[49][54] = {50, 53, 54};
    table[49][55] = {50, 53, 54};
    table[49][56] = {50, 53, 54};
    table[49][57] = {50, 53, 54};
    table[53][5] = {54, -1};
    table[53][6] = {54, -1};
    table[53][12] = {54, -1};
    table[53][13] = {54, -1};
    table[53][17] = {54, -1};
    table[53][20] = {54, -1};
    table[53][21] = {54, -1};
    table[53][23] = {54, -1};
    table[53][24] = {54, -1};
    table[53][26] = {54, -1};
    table[53][27] = {54, -1};
    table[53][28] = {54, -1};
    table[53][29] = {54, -1};
    table[53][31] = {54, -1};
    table[53][34] = {54, -1};
    table[53][35] = {54, -1};
    table[53][43] = {54, -1};
    table[53][44] = {54, -1};
    table[53][45] = {54, -1};
    table[53][46] = {54, -1};
    table[53][47] = {54, -1};
    table[53][48] = {54, -1};
    table[53][49] = {54, -1};
    table[53][50] = {54, -1};
    table[53][51] = {54, 55, 53, 54};
    table[53][52] = {54, 55, 53, 54};
    table[52][3] = {53, 56, 57};
    table[52][11] = {53, 56, 57};
    table[52][29] = {53, 56, 57};
    table[52][38] = {53, 56, 57};
    table[52][39] = {53, 56, 57};
    table[52][40] = {53, 56, 57};
    table[52][53] = {53, 56, 57};
    table[52][54] = {53, 56, 57};
    table[52][55] = {53, 56, 57};
    table[52][56] = {53, 56, 57};
    table[52][57] = {53, 56, 57};
    table[56][5] = {57, -1};
    table[56][6] = {57, -1};
    table[56][12] = {57, -1};
    table[56][13] = {57, -1};
    table[56][17] = {57, -1};
    table[56][20] = {57, -1};
    table[56][21] = {57, -1};
    table[56][23] = {57, -1};
    table[56][24] = {57, -1};
    table[56][26] = {57, -1};
    table[56][27] = {57, -1};
    table[56][28] = {57, -1};
    table[56][29] = {57, -1};
    table[56][31] = {57, -1};
    table[56][34] = {57, -1};
    table[56][35] = {57, -1};
    table[56][37] = {57, -38, 53};
    table[56][43] = {57, -1};
    table[56][44] = {57, -1};
    table[56][45] = {57, -1};
    table[56][46] = {57, -1};
    table[56][47] = {57, -1};
    table[56][48] = {57, -1};
    table[56][49] = {57, -1};
    table[56][50] = {57, -1};
    table[56][51] = {57, -1};
    table[56][52] = {57, -1};
    table[55][3] = {56, 58};
    table[55][11] = {56, -12, 12, -13};
    table[55][29] = {56, 59};
    table[55][38] = {56, -39, -4};
    table[55][39] = {56, 60};
    table[55][40] = {56, 30};
    table[55][53] = {56, 59};
    table[55][54] = {56, 59};
    table[55][55] = {56, 59};
    table[55][56] = {56, 59};
    table[55][57] = {56, 59};
    table[59][39] = {60, -40, -12, 61, -13};
    table[29][40] = {30, -41, -12, 62, -13};
    table[61][3] = {62, 61};
    table[61][40] = {62, 30};
    table[60][3] = {61, -4, 29};
    table[57][3] = {58, 28, 29};
    table[27][3] = {28, -4, 63};
    table[28][41] = {29, -42, -4, 29};
    table[28][42] = {29, -43};
    table[62][11] = {63, -12, 31, -13};
    table[62][41] = {63, -1};
    table[62][42] = {63, -1};
    table[48][43] = {49, -44};
    table[48][44] = {49, -45};
    table[48][45] = {49, -46};
    table[48][46] = {49, -47};
    table[48][47] = {49, -48};
    table[48][48] = {49, -49};
    table[51][49] = {52, -50};
    table[51][50] = {52, -51};
    table[54][51] = {55, -52};
    table[54][52] = {55, -53};
    table[58][29] = {59, -30};
    table[58][53] = {59, -54};
    table[58][54] = {59, -55};
    table[58][55] = {59, -56};
    table[58][56] = {59, 64};
    table[58][57] = {59, 64};
    table[63][56] = {64, -57};
    table[63][57] = {64, -58};
    table[9][3] = {10, -4};
    table[9][39] = {10, -40, -12, 10, -13};
    table[9][58] = {10, -59};
    table[9][59] = {10, -60};
    table[9][60] = {10, -61};
    table[9][61] = {10, -62};
}


// void initialize_table()
// {
//     table[1][2] = {2, -3, -4, -5, 3, -6};
//     table[2][5] = {3, -1};
//     table[2][7] = {3, 4, 5};
//     table[2][10] = {3, 4, 5};
//     table[2][13] = {3, -1};
//     table[2][14] = {3, 4, 5};
//     table[4][5] = {5, -1};
//     table[4][6] = {5, -7, 3};
//     table[4][13] = {5, -1};
//     table[3][7] = {4, 6};
//     table[3][10] = {4, 7};
//     table[3][14] = {4, 8};
//     table[5][7] = {6, -8, -4, 9};
//     table[8][8] = {9, -9, 10, 11};
//     table[8][9] = {9, -10, 12};
//     table[10][5] = {11, -1};
//     table[10][6] = {11, -1};
//     table[10][9] = {11, -10, 12};
//     table[10][13] = {11, -1};
//     table[6][10] = {7, -11, -4, -12, 13, -13, 14};
//     table[13][4] = {14, 15};
//     table[13][8] = {14, -9, 10, 15};
//     table[14][4] = {15, -5, 16, 17, -6};
//     table[15][3] = {16, -1};
//     table[15][5] = {16, -1};
//     table[15][7] = {16, 4, 5, -14};
//     table[15][10] = {16, 4, 5, -14};
//     table[15][14] = {16, 4, 5, -14};
//     table[15][19] = {16, -1};
//     table[15][22] = {16, -1};
//     table[15][25] = {16, -1};
//     table[15][32] = {16, -1};
//     table[15][33] = {16, -1};
//     table[15][40] = {16, -1};
//     table[7][14] = {8, -15, -4, -16, 18, -17};
//     table[17][3] = {18, 19, 20};
//     table[17][16] = {18, -1};
//     table[19][6] = {20, -7, 18};
//     table[19][16] = {20, -1};
//     table[18][3] = {19, -4, -9, 10};
//     table[12][3] = {13, 19, 21};
//     table[12][12] = {13, -1};
//     table[20][12] = {21, -1};
//     table[20][17] = {21, -18, 13};
//     table[16][3] = {17, 22, 23};
//     table[16][5] = {17, -1};
//     table[16][19] = {17, 22, 23};
//     table[16][21] = {17, -1};
//     table[16][22] = {17, 22, 23};
//     table[16][24] = {17, -1};
//     table[16][25] = {17, 22, 23};
//     table[16][27] = {17, -1};
//     table[16][28] = {17, -1};
//     table[16][29] = {17, -1};
//     table[16][31] = {17, -1};
//     table[16][32] = {17, 22, 23};
//     table[16][33] = {17, 22, 23};
//     table[16][40] = {17, 22, 23};
//     table[22][5] = {23, -1};
//     table[22][6] = {23, -7, 17};
//     table[22][21] = {23, -1};
//     table[22][24] = {23, -1};
//     table[22][27] = {23, -1};
//     table[22][28] = {23, -1};
//     table[22][29] = {23, -1};
//     table[22][31] = {23, -1};
//     table[21][3] = {22, 24};
//     table[21][19] = {22, 25};
//     table[21][22] = {22, 25};
//     table[21][25] = {22, 25};
//     table[21][32] = {22, 26};
//     table[21][33] = {22, 27};
//     table[21][40] = {22, 24};
//     table[23][3] = {24, 28, 29, -10, -19};
//     table[23][40] = {24, 30, -10, 12};
//     table[30][3] = {31, 12, 32};
//     table[30][11] = {31, 12, 32};
//     table[30][12] = {31, -1};
//     table[30][29] = {31, 12, 32};
//     table[30][36] = {31, 12, 32};
//     table[30][38] = {31, 12, 32};
//     table[30][39] = {31, 12, 32};
//     table[30][40] = {31, 12, 32};
//     table[30][53] = {31, 12, 32};
//     table[30][54] = {31, 12, 32};
//     table[30][55] = {31, 12, 32};
//     table[30][56] = {31, 12, 32};
//     table[30][57] = {31, 12, 32};
//     table[31][12] = {32, -1};
//     table[31][17] = {32, -18, 31};
//     table[24][19] = {25, -20, 12, -21, 17, 33, -22};
//     table[24][22] = {25, -23, 12, -24, 17, 33, -25};
//     table[24][25] = {25, -26, 12, -27, 34, 35, -28};
//     table[32][21] = {33, -1};
//     table[32][24] = {33, -1};
//     table[32][28] = {33, -29, 17};
//     table[33][29] = {34, 36, 37};
//     table[36][27] = {37, -1};
//     table[36][29] = {37, 34};
//     table[36][31] = {37, -1};
//     table[35][29] = {36, 38, -9, 17};
//     table[37][29] = {38, 39, 40};
//     table[39][8] = {40, -1};
//     table[39][17] = {40, -18, 38};
//     table[38][29] = {39, -30, 41};
//     table[40][8] = {41, -1};
//     table[40][17] = {41, -1};
//     table[40][30] = {41, -31, -30};
//     table[34][27] = {35, -1};
//     table[34][31] = {35, -32, 17};
//     table[25][32] = {26, -33, 12, -24, 17, -25};
//     table[26][33] = {27, -34, 12};
//     table[11][3] = {12, 42, 43};
//     table[11][11] = {12, 42, 43};
//     table[11][29] = {12, 42, 43};
//     table[11][36] = {12, 42, 43};
//     table[11][38] = {12, 42, 43};
//     table[11][39] = {12, 42, 43};
//     table[11][40] = {12, 42, 43};
//     table[11][53] = {12, 42, 43};
//     table[11][54] = {12, 42, 43};
//     table[11][55] = {12, 42, 43};
//     table[11][56] = {12, 42, 43};
//     table[11][57] = {12, 42, 43};
//     table[42][5] = {43, -1};
//     table[42][6] = {43, -1};
//     table[42][12] = {43, -1};
//     table[42][13] = {43, -1};
//     table[42][17] = {43, -1};
//     table[42][20] = {43, -1};
//     table[42][21] = {43, -1};
//     table[42][23] = {43, -1};
//     table[42][24] = {43, -1};
//     table[42][26] = {43, -1};
//     table[42][27] = {43, -1};
//     table[42][28] = {43, -1};
//     table[42][29] = {43, -1};
//     table[42][31] = {43, -1};
//     table[42][34] = {43, -35, 42, 43};
//     table[41][3] = {42, 44, 45};
//     table[41][11] = {42, 44, 45};
//     table[41][29] = {42, 44, 45};
//     table[41][36] = {42, 44, 45};
//     table[41][38] = {42, 44, 45};
//     table[41][39] = {42, 44, 45};
//     table[41][40] = {42, 44, 45};
//     table[41][53] = {42, 44, 45};
//     table[41][54] = {42, 44, 45};
//     table[41][55] = {42, 44, 45};
//     table[41][56] = {42, 44, 45};
//     table[41][57] = {42, 44, 45};
//     table[44][5] = {45, -1};
//     table[44][6] = {45, -1};
//     table[44][12] = {45, -1};
//     table[44][13] = {45, -1};
//     table[44][17] = {45, -1};
//     table[44][20] = {45, -1};
//     table[44][21] = {45, -1};
//     table[44][23] = {45, -1};
//     table[44][24] = {45, -1};
//     table[44][26] = {45, -1};
//     table[44][27] = {45, -1};
//     table[44][28] = {45, -1};
//     table[44][29] = {45, -1};
//     table[44][31] = {45, -1};
//     table[44][34] = {45, -1};
//     table[44][35] = {45, -36, 44, 45};
//     table[43][3] = {44, 46};
//     table[43][11] = {44, 46};
//     table[43][29] = {44, 46};
//     table[43][36] = {44, -37, 46};
//     table[43][38] = {44, 46};
//     table[43][39] = {44, 46};
//     table[43][40] = {44, 46};
//     table[43][53] = {44, 46};
//     table[43][54] = {44, 46};
//     table[43][55] = {44, 46};
//     table[43][56] = {44, 46};
//     table[43][57] = {44, 46};
//     table[45][3] = {46, 47, 48};
//     table[45][11] = {46, 47, 48};
//     table[45][29] = {46, 47, 48};
//     table[45][38] = {46, 47, 48};
//     table[45][39] = {46, 47, 48};
//     table[45][40] = {46, 47, 48};
//     table[45][53] = {46, 47, 48};
//     table[45][54] = {46, 47, 48};
//     table[45][55] = {46, 47, 48};
//     table[45][56] = {46, 47, 48};
//     table[45][57] = {46, 47, 48};
//     table[47][5] = {48, -1};
//     table[47][6] = {48, -1};
//     table[47][12] = {48, -1};
//     table[47][13] = {48, -1};
//     table[47][17] = {48, -1};
//     table[47][20] = {48, -1};
//     table[47][21] = {48, -1};
//     table[47][23] = {48, -1};
//     table[47][24] = {48, -1};
//     table[47][26] = {48, -1};
//     table[47][27] = {48, -1};
//     table[47][28] = {48, -1};
//     table[47][29] = {48, -1};
//     table[47][31] = {48, -1};
//     table[47][34] = {48, -1};
//     table[47][35] = {48, -1};
//     table[47][43] = {48, 49, 47, 48};
//     table[47][44] = {48, 49, 47, 48};
//     table[47][45] = {48, 49, 47, 48};
//     table[47][46] = {48, 49, 47, 48};
//     table[47][47] = {48, 49, 47, 48};
//     table[47][48] = {48, 49, 47, 48};
//     table[46][3] = {47, 50, 51};
//     table[46][11] = {47, 50, 51};
//     table[46][29] = {47, 50, 51};
//     table[46][38] = {47, 50, 51};
//     table[46][39] = {47, 50, 51};
//     table[46][40] = {47, 50, 51};
//     table[46][53] = {47, 50, 51};
//     table[46][54] = {47, 50, 51};
//     table[46][55] = {47, 50, 51};
//     table[46][56] = {47, 50, 51};
//     table[46][57] = {47, 50, 51};
//     table[50][5] = {51, -1};
//     table[50][6] = {51, -1};
//     table[50][12] = {51, -1};
//     table[50][13] = {51, -1};
//     table[50][17] = {51, -1};
//     table[50][20] = {51, -1};
//     table[50][21] = {51, -1};
//     table[50][23] = {51, -1};
//     table[50][24] = {51, -1};
//     table[50][26] = {51, -1};
//     table[50][27] = {51, -1};
//     table[50][28] = {51, -1};
//     table[50][29] = {51, -1};
//     table[50][31] = {51, -1};
//     table[50][34] = {51, -1};
//     table[50][35] = {51, -1};
//     table[50][43] = {51, -1};
//     table[50][44] = {51, -1};
//     table[50][45] = {51, -1};
//     table[50][46] = {51, -1};
//     table[50][47] = {51, -1};
//     table[50][48] = {51, -1};
//     table[50][49] = {51, 52, 50, 51};
//     table[50][50] = {51, 52, 50, 51};
//     table[49][3] = {50, 53, 54};
//     table[49][11] = {50, 53, 54};
//     table[49][29] = {50, 53, 54};
//     table[49][38] = {50, 53, 54};
//     table[49][39] = {50, 53, 54};
//     table[49][40] = {50, 53, 54};
//     table[49][53] = {50, 53, 54};
//     table[49][54] = {50, 53, 54};
//     table[49][55] = {50, 53, 54};
//     table[49][56] = {50, 53, 54};
//     table[49][57] = {50, 53, 54};
//     table[53][5] = {54, -1};
//     table[53][6] = {54, -1};
//     table[53][12] = {54, -1};
//     table[53][13] = {54, -1};
//     table[53][17] = {54, -1};
//     table[53][20] = {54, -1};
//     table[53][21] = {54, -1};
//     table[53][23] = {54, -1};
//     table[53][24] = {54, -1};
//     table[53][26] = {54, -1};
//     table[53][27] = {54, -1};
//     table[53][28] = {54, -1};
//     table[53][29] = {54, -1};
//     table[53][31] = {54, -1};
//     table[53][34] = {54, -1};
//     table[53][35] = {54, -1};
//     table[53][43] = {54, -1};
//     table[53][44] = {54, -1};
//     table[53][45] = {54, -1};
//     table[53][46] = {54, -1};
//     table[53][47] = {54, -1};
//     table[53][48] = {54, -1};
//     table[53][49] = {54, -1};
//     table[53][50] = {54, -1};
//     table[53][51] = {54, 55, 53, 54};
//     table[53][52] = {54, 55, 53, 54};
//     table[52][3] = {53, 56, 57};
//     table[52][11] = {53, 56, 57};
//     table[52][29] = {53, 56, 57};
//     table[52][38] = {53, 56, 57};
//     table[52][39] = {53, 56, 57};
//     table[52][40] = {53, 56, 57};
//     table[52][53] = {53, 56, 57};
//     table[52][54] = {53, 56, 57};
//     table[52][55] = {53, 56, 57};
//     table[52][56] = {53, 56, 57};
//     table[52][57] = {53, 56, 57};
//     table[56][5] = {57, -1};
//     table[56][6] = {57, -1};
//     table[56][12] = {57, -1};
//     table[56][13] = {57, -1};
//     table[56][17] = {57, -1};
//     table[56][20] = {57, -1};
//     table[56][21] = {57, -1};
//     table[56][23] = {57, -1};
//     table[56][24] = {57, -1};
//     table[56][26] = {57, -1};
//     table[56][27] = {57, -1};
//     table[56][28] = {57, -1};
//     table[56][29] = {57, -1};
//     table[56][31] = {57, -1};
//     table[56][34] = {57, -1};
//     table[56][35] = {57, -1};
//     table[56][37] = {57, -38, 53};
//     table[56][43] = {57, -1};
//     table[56][44] = {57, -1};
//     table[56][45] = {57, -1};
//     table[56][46] = {57, -1};
//     table[56][47] = {57, -1};
//     table[56][48] = {57, -1};
//     table[56][49] = {57, -1};
//     table[56][50] = {57, -1};
//     table[56][51] = {57, -1};
//     table[56][52] = {57, -1};
//     table[55][3] = {56, 58};
//     table[55][11] = {56, -12, 12, -13};
//     table[55][29] = {56, 59};
//     table[55][38] = {56, -39, -4};
//     table[55][39] = {56, 60};
//     table[55][40] = {56, 30};
//     table[55][53] = {56, 59};
//     table[55][54] = {56, 59};
//     table[55][55] = {56, 59};
//     table[55][56] = {56, 59};
//     table[55][57] = {56, 59};
//     table[59][39] = {60, -40, -12, 61, -13};
//     table[29][40] = {30, -41, -12, 62, -13};
//     table[61][3] = {62, 61};
//     table[61][40] = {62, 30};
//     table[60][3] = {61, -4, 29};
//     table[57][3] = {58, 28, 29};
//     table[27][3] = {28, -4, 63};
//     table[28][41] = {29, -42, -4, 29};
//     table[28][42] = {29, -43};
//     table[62][11] = {63, -12, 31, -13};
//     table[62][41] = {63, -1};
//     table[62][42] = {63, -1};
//     table[48][43] = {49, -44};
//     table[48][44] = {49, -45};
//     table[48][45] = {49, -46};
//     table[48][46] = {49, -47};
//     table[48][47] = {49, -48};
//     table[48][48] = {49, -49};
//     table[51][49] = {52, -50};
//     table[51][50] = {52, -51};
//     table[54][51] = {55, -52};
//     table[54][52] = {55, -53};
//     table[58][29] = {59, -30};
//     table[58][53] = {59, -54};
//     table[58][54] = {59, -55};
//     table[58][55] = {59, -56};
//     table[58][56] = {59, 64};
//     table[58][57] = {59, 64};
//     table[63][56] = {64, -57};
//     table[63][57] = {64, -58};
//     table[9][3] = {10, -4};
//     table[9][39] = {10, -40, -12, 10, -13};
//     table[9][58] = {10, -59};
//     table[9][59] = {10, -60};
//     table[9][60] = {10, -61};
//     table[9][61] = {10, -62};
// }