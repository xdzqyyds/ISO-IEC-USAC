/*
This material is strictly confidential and shall remain as such.

Copyright � 1999 VoiceAge Corporation.  All Rights Reserved.  Any unauthorized
use, distribution, reproduction or storage of this material or any part thereof
is strictly prohibited.

ACELP is registered trademark of VoiceAge Corporation in Canada and / or other
countries.
*/

#define NB_SPHERE 32
#define NB_LEADER 37
#define NB_LDSIGN 226
#define NB_LDQ3   9
#define NB_LDQ4   28

/* table of successive powers of 2 (for the computation of the sign code of
   a signed leader */
const int tab_pow2[8]={128, 64, 32, 16, 8, 4, 2, 1};

/* table of factorial */
const int tab_factorial[8]={5040, 720, 120, 24, 6, 2, 1, 1};

/* Da_pos - Position of the first absolute leader on a spherical shell (or sphere) */
const int Da_pos[NB_SPHERE] = {
  0,  2,  5,  8, 13, 18, 20, 22, 23, 25, 26, 27, 27, 28, 28, 28,
 29, 30, 31, 31, 32, 32, 32, 32, 32, 34, 35, 35, 35, 35, 35, 35};

/* Da_nb - Number of absolute leaders on a spherical shell */
const int Da_nb[NB_SPHERE] = {
 2, 3, 3, 5, 5, 2, 2, 1, 2, 1, 1, 0, 1, 0, 0, 1,
 1, 1, 0, 1, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 1};

/* Da_nq - Codebook number for each absolute leader */
const int Da_nq[NB_LEADER+2] = {
  2,  2,  3,  3,  2,  4,  4,  3,  4,  4,  4,  3,  4,  4,  4,  4,
  4,  3,  4,  4,  4,  4,  3,  4,  4,  4,  4,  4,  4,  4,  4,  4,
  4,  4,  4,  4,  4,  0, 100};     /* 0=Q0, 100=outliers */

/* Da_id - identification code of an absolute leader */
const unsigned int Da_id[NB_LEADER] = {
 0x0001, 0x0004, 0x0008, 0x000B, 0x0020, 0x000C, 0x0015, 0x0024,
 0x0010, 0x001F, 0x0028, 0x0040, 0x004F, 0x0029, 0x002C, 0x0044,
 0x0059, 0x00A4, 0x0060, 0x00A8, 0x00C4, 0x012D, 0x0200, 0x0144,
 0x0204, 0x0220, 0x0335, 0x04E4, 0x0400, 0x0584, 0x0A20, 0x0A40,
 0x09C4, 0x12C4, 0x0C20, 0x2000, 0x4E20};

/*  Da - Absolute leaders */
const unsigned char Da[NB_LEADER][8]={
  { 1,  1,  1,  1,  1,  1,  1,  1},
  { 2,  2,  0,  0,  0,  0,  0,  0},
  { 2,  2,  2,  2,  0,  0,  0,  0},
  { 3,  1,  1,  1,  1,  1,  1,  1},
  { 4,  0,  0,  0,  0,  0,  0,  0},
  { 2,  2,  2,  2,  2,  2,  0,  0},
  { 3,  3,  1,  1,  1,  1,  1,  1},
  { 4,  2,  2,  0,  0,  0,  0,  0},
  { 2,  2,  2,  2,  2,  2,  2,  2},
  { 3,  3,  3,  1,  1,  1,  1,  1},
  { 4,  2,  2,  2,  2,  0,  0,  0},
  { 4,  4,  0,  0,  0,  0,  0,  0},
  { 5,  1,  1,  1,  1,  1,  1,  1},
  { 3,  3,  3,  3,  1,  1,  1,  1},
  { 4,  2,  2,  2,  2,  2,  2,  0},
  { 4,  4,  2,  2,  0,  0,  0,  0},
  { 5,  3,  1,  1,  1,  1,  1,  1},
  { 6,  2,  0,  0,  0,  0,  0,  0},
  { 4,  4,  4,  0,  0,  0,  0,  0},
  { 6,  2,  2,  2,  0,  0,  0,  0},
  { 6,  4,  2,  0,  0,  0,  0,  0},
  { 7,  1,  1,  1,  1,  1,  1,  1},
  { 8,  0,  0,  0,  0,  0,  0,  0},
  { 6,  6,  0,  0,  0,  0,  0,  0},
  { 8,  2,  2,  0,  0,  0,  0,  0},
  { 8,  4,  0,  0,  0,  0,  0,  0},
  { 9,  1,  1,  1,  1,  1,  1,  1},
  {10,  2,  0,  0,  0,  0,  0,  0},
  { 8,  8,  0,  0,  0,  0,  0,  0},
  {10,  6,  0,  0,  0,  0,  0,  0},
  {12,  0,  0,  0,  0,  0,  0,  0},
  {12,  4,  0,  0,  0,  0,  0,  0},
  {10, 10,  0,  0,  0,  0,  0,  0},
  {14,  2,  0,  0,  0,  0,  0,  0},
  {12,  8,  0,  0,  0,  0,  0,  0},
  {16,  0,  0,  0,  0,  0,  0,  0},
  {20,  0,  0,  0,  0,  0,  0,  0}};

/* Ds - Sign codes of all signed leaders */
const unsigned char Ds[NB_LDSIGN]={
  0,3,15,63,255,
  0,64,192,
  0,16,48,112,240,
  1,7,31,127,128,131,143,191,
  0,128,
  0,4,12,28,60,124,252,
  0,3,15,63,65,71,95,192,195,207,255,
  0,32,96,128,160,224,
  0,1,3,7,15,31,63,127,255,
  1,7,31,32,35,47,97,103,127,224,227,239,
  0,8,24,56,120,128,136,152,184,248,
  0,64,192,
  0,3,15,63,129,135,159,255,
  0,3,15,17,23,48,51,63,113,119,240,243,255,
  0,2,6,14,30,62,126,128,130,134,142,158,190,254,
  0,16,48,64,80,112,192,208,240,
  1,7,31,64,67,79,127,128,131,143,191,193,199,223,
  0,64,128,192,
  0,32,96,224,
  0,16,48,112,128,144,176,240,
  0,32,64,96,128,160,192,224,
  1,7,31,127,128,131,143,191,
  0,128,
  0,64,192,
  0,32,96,128,160,224,
  0,64,128,192,
  0,3,15,63,129,135,159,255,
  0,64,128,192,
  0,64,192,
  0,64,128,192,
  0,128,
  0,64,128,192,
  0,64,192,
  0,64,128,192,
  0,64,128,192,
  0,128,
  0,128
};

/* Ns - Number of signed leader associated to a given absolute leader */
const int Ns[NB_LEADER]= {
   5,  3,  5,  8,  2,  7, 11,  6,  9, 12, 10,  3,
   8, 13, 14,  9, 14,  4,  4,  8,  8,  8,  2,  3,
   6,  4,  8,  4,  3,  4,  2,  4,  3,  4,  4,  2,  2};

/* Ia - Position of the first signed leader associated to an absolute leader */
const int Ia[NB_LEADER]= {
    0,   5,   8,  13,  21,  23,  30,  41,  47,  56,  68,  78,
   81,  89, 102, 116, 125, 139, 143, 147, 155, 163, 171, 173,
  176, 182, 186, 194, 198, 201, 205, 207, 211, 214, 218, 222, 224};

/* Is - Cardinalite offset of signed leaders */
const unsigned int Is[NB_LDSIGN]={
     0,     1,    29,    99,   127,   128,   156,   212,
   256,   326,   606,  1026,  1306,  1376,  1432,  1712,
  1880,  1888,  1896,  2064,  2344,   240,   248,     0,
    28,   196,   616,  1176,  1596,  1764,  1792,  1820,
  2240,  2660,  2688,  3024,  4144,  4480,  4508,  4928,
  5348,  2400,  2568,  2904,  3072,  3240,  3576,  5376,
  5377,  5385,  5413,  5469,  5539,  5595,  5623,  5631,
  5632,  5912,  6472,  6528,  6696,  8376,  9216, 10056,
 11736, 11904, 11960, 12520, 12800, 13080, 14200, 15880,
 17000, 17280, 17560, 18680, 20360, 21480,  3744,  3772,
  3828, 21760, 21768, 21936, 22216, 22272, 22328, 22608,
 22776, 22784, 22854, 23274, 23344, 24464, 25584, 26004,
 28524, 28944, 30064, 31184, 31254, 31674, 31744, 31800,
 32136, 32976, 34096, 34936, 35272, 35328, 35384, 35720,
 36560, 37680, 38520, 38856, 38912, 39332, 40172, 40592,
 41432, 43112, 43952, 44372, 45212, 45632, 45968, 47088,
 47424, 47480, 48320, 49160, 49216, 49272, 50112, 50952,
 51008, 51344, 52464,  3856,  3912,  3968,  4024, 52800,
 52856, 53024, 53192, 53248, 53528, 54368, 55208, 55488,
 55768, 56608, 57448, 57728, 58064, 58400, 58736, 59072,
 59408, 59744, 60080, 60416, 60472, 60752, 60920, 60928,
 60936, 61104, 61384,  4080,  4088, 61440, 61468, 61524,
 61552, 61720, 62056, 62224, 62392, 62728, 62896, 62952,
 63008, 63064, 63120, 63128, 63296, 63576, 63632, 63688,
 63968, 64136, 64144, 64200, 64256, 64312, 64368, 64396,
 64452, 64480, 64536, 64592, 64648, 64704, 64712, 64720,
 64776, 64832, 64888, 64944, 64972, 65028, 65056, 65112,
 65168, 65224, 65280, 65336, 65392, 65448, 65504, 65512,
 65520, 65528};

/* A3 - Number of the absolute leaders in codebooks Q2 and Q3 */
const int A3[NB_LDQ3]={
   0,  1,  4,  2,  3,  7, 11, 17, 22};

/* A4 - Number of the absolute leaders in codebook Q4 */
const int A4[NB_LDQ4]={
   5,  6,  8,  9, 10, 12, 13, 14, 15,
  16, 18, 19, 20, 21, 23, 24, 25, 26,
  27, 28, 29, 30, 31, 32, 33, 34, 35, 36};

/* I3 - Cardinality offsets for absolute leaders in Q3 */
const unsigned int I3[NB_LDQ3]={
      0,   128,   240,   256,  1376,  2400,  3744,  3856,  4080};

/* I4 - Cardinality offset for absolute leaders in Q4 */
const unsigned int I4[NB_LDQ4]={
      0,  1792,  5376,  5632, 12800, 21760, 22784, 31744, 38912,
  45632, 52800, 53248, 57728, 60416, 61440, 61552, 62896, 63120,
  64144, 64368, 64480, 64704, 64720, 64944, 65056, 65280, 65504, 65520};


