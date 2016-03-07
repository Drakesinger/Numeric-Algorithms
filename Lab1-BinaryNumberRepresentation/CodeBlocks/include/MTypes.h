#pragma once
//#define USE_IEEE true
#define USE_17BITS false

#ifdef USE_IEEE

// IEEE
#define M_Shifted_Size 24

#define M_Size 23
#define S_Size 1
#define E_Size 8

#define Shift 127
#define MAX_EXPONENT 255

// Align data to 1 byte.
#pragma pack(push)
#pragma pack(1)
typedef struct /*_attribute_(packed)*/
{
	unsigned int S : S_Size; // Sign = 1 -> negative number | 0 -> positive number
} MSBit;

typedef struct
{
	unsigned int E : E_Size;
} MExponent;

typedef struct
{
	unsigned int M : M_Size;
} MMantissa;

typedef struct
{
	unsigned int M : M_Shifted_Size;
} MShiftedMantissa;
#pragma pack(pop)

#endif // USE_IEEE

#ifdef USE_17BITS

#define M_Shifted_Size 12

#define M_Size 11
#define S_Size 1
#define E_Size 5

// Exponent Shift : 2^(Exp.length()-1)-1
#define Shift 15
#define MAX_EXPONENT 31

// Align data to 1 byte.
#pragma pack(push)
#pragma pack(1)
typedef struct
{
	unsigned char S : S_Size; // Sign = 1 -> negative number | 0 -> positive number
} MSBit;

typedef struct
{
	unsigned char E : E_Size;
} MExponent;

typedef struct
{
	unsigned short M : M_Size;
} MMantissa;

typedef struct
{
	unsigned int M : M_Shifted_Size;
} MShiftedMantissa;
#pragma pack(pop)

#endif // USE_17BITS
