#ifndef GPT_COMMON
#define GPT_COMMON

enum opcode {
   OP_NOP         = 0,
   OP_HLT         = 1,
   OP_EXIT        = 2,
   OP_ISUM        = 3,
   OP_SSUM        = 4,
   OP_RSUM        = 5,
   OP_ISUB        = 6,
   OP_SSUB        = 7,
   OP_RSUB        = 8,
   OP_IMUL        = 9,
   OP_RMUL        = 10,
   OP_IDIV        = 11,
   OP_RDIV        = 12,
   OP_IMOD        = 13,
   OP_RMOD        = 14,
   OP_IGE         = 15,
   OP_SGE         = 16,
   OP_RGE         = 17,
   OP_ILE         = 18,
   OP_SLE         = 19,
   OP_RLE         = 20,
   OP_INE         = 21,
   OP_SNE         = 22,
   OP_RNE         = 23,
   OP_IGT         = 24,
   OP_SGT         = 25,
   OP_RGT         = 26,
   OP_ILT         = 27,
   OP_SLT         = 28,
   OP_RLT         = 29,
   OP_IEQ         = 30,
   OP_SEQ         = 31,
   OP_REQ         = 32,
   OP_OR = 33,
   OP_AND         = 34,
   OP_XOR         = 35,
   OP_INEG = 36,
   OP_RNEG = 37,
   OP_NOT         = 38,
   OP_IINC = 39,
   OP_IDEC = 40,
   OP_I2C         = 41,
   OP_R2C         = 42,
   OP_S2C         = 43,
   OP_B2C         = 44,
   OP_I2R         = 45,
   OP_C2R         = 46,
   OP_S2R         = 47,
   OP_B2R         = 48,
   OP_I2B         = 49,
   OP_C2B         = 50,
   OP_R2B         = 51,
   OP_S2B         = 52,
   OP_I2S         = 53,
   OP_C2S         = 54,
   OP_R2S         = 55,
   OP_B2S         = 56,
   OP_P2S         = 57,
   OP_C2I         = 58,
   OP_R2I         = 59,
   OP_S2I         = 60,
   OP_B2I         = 61,
   OP_ISET = 62,
   OP_SSET = 63,
   OP_RSET = 64,
   OP_GETA = 65,
   OP_IGETV = 66,
   OP_SGETV = 67,
   OP_RGETV = 68,
   OP_ISETV = 69,
   OP_SSETV = 70,
   OP_RSETV = 71,
   OP_JMP         = 72,
   OP_IF = 73,
   OP_IFNOT = 74,
   OP_PUSH = 75,
   OP_POP         = 76,
   OP_INCSP = 77,
   OP_DECSP = 78,
   OP_PUSH_INT = 79,
   OP_PUSH_STRING = 80,
   OP_PUSH_REAL = 81,
   OP_PUSH_CHAR = 82,
   OP_PUSH_BOOL = 83,
   OP_PUSH_MATRIX = 84,
   OP_PUSH_SP = 85,
   OP_POP_SP = 86,
   OP_INCSP_4 = 87,
   OP_INCSP_8 = 88,
   OP_DECSP_4 = 89,
   OP_DECSP_8 = 90,
   OP_PCALL = 91,
   OP_RET         = 92,
   OP_SALLOC = 93,
   OP_SFREE = 94,
   OP_SSETC = 95,
   OP_SGETC = 96,
   OP_M1ALLOC = 97,
   OP_M2ALLOC = 98,
   OP_MFREE = 99,
   OP_M1SET = 100,
   OP_M1GET = 101,
   OP_M2SET = 102,
   OP_M2GET = 103,
   OP_MCOPY = 104,
   OP_MGETSIZE1 = 105,
   OP_MGETSIZE2 = 106,
   OPCODE_NUMBER  = 107
};

#endif

