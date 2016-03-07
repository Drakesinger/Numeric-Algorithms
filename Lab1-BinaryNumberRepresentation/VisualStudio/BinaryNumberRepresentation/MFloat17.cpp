/********************************************************************
	created:	2015/03/08
	created:	8:3:2015   21:43
	filename: 	C:\Development\Projects\NumericAlgorithms\BinaryNumberRepresentation\BinaryNumberRepresentation\MFloat17.cpp
	file path:	C:\Development\Projects\NumericAlgorithms\BinaryNumberRepresentation\BinaryNumberRepresentation
	file base:	MFloat17
	file ext:	cpp
	author:		Horia Mut, Nils Ryter, Romain Claret Yakovenko

	purpose:	Function implementations
	*********************************************************************/

#include "MFloat17.h"
#include <math.h>
#include <assert.h>

/**
 * Function that converts a real number to binary form.
 * Does so in two steps, first the integer part and then the floating point part.
 *
 * @param DecimalNumber			Real number to convert
 * @param OutBinaryNumber			The real number converted to binary
 * @param OutFirstSetBitPosition	Position of the 1st set bit of the binary form
 *
 * @returns Number of digits of the number's binary form
 * @see http://www.tfinley.net/notes/cps104/floating.html
 */
int MFloat17::FindBinaryNumber(double DecimalNumber, int& OutBinaryNumber, int& OutFirstSetBitPosition)
{
	int BinaryNumberLength = 0;
	int TempBinaryNumber = 0;
	OutFirstSetBitPosition = 0;

	if (DecimalNumber == 0)
	{
		return -1;
	}

	// First we need to check if the number has a floating point.
	double Remainder = fmod(DecimalNumber, 1);

	if (Remainder == 0)
	{
		// Integer.
		BinaryNumberLength = ConstructBinaryNumber(DecimalNumber, TempBinaryNumber);

		// Shift it to the right in order to fill the Mantissa.

		if (BinaryNumberLength > M_Size)
		{
			OutBinaryNumber = TempBinaryNumber >> (BinaryNumberLength - M_Shifted_Size);
		}
		else
		{
			OutBinaryNumber = TempBinaryNumber << (M_Size - BinaryNumberLength + 1);
		}
	}
	else
	{
		// Floating point number.
		// We have two parts. The Integer part and the Floating Point part.

		int IntegerPartLength = 0;
		unsigned int Mask = 0xfff;

		// Construct the integer part first but only if the integer part actually exists.
		// Meaning that the DecimalNumber is not of the form 0.XYZ but X.YZ.
		//if (!((DecimalNumber - Remainder) <= (0 + ERROR_MARGIN)) && !((DecimalNumber - Remainder) >= (0 - ERROR_MARGIN)))
		if (DecimalNumber - Remainder != 0)
		{
			IntegerPartLength = ConstructBinaryNumber(DecimalNumber - Remainder, TempBinaryNumber);
		}

		// Shift the number by the Mantissa size in order to fill it with the remainder.
		TempBinaryNumber = TempBinaryNumber << (M_Shifted_Size);
		unsigned int Temp; // Will contain the remainder in binary form.

		// Construct the floating point part.
		ConstructBinaryRemainder(Remainder, OutFirstSetBitPosition, Temp);

		if (IntegerPartLength == 0)
		{
			// Shift Temp to have the 1st one as the leading bit.
			//Temp = Temp << (SIZE_OF_INT - FirstSetBitPosition + 2);
			Temp = Temp << (OutFirstSetBitPosition - 1);
		}

		// Shift it to the right to take out unwanted bits (out of precision).
		Temp = Temp >> (SIZE_OF_INT - M_Shifted_Size);

		// Mask everything except the mantissa size with the implied one.
		Temp = Temp & Mask;

		// Add it to the TempBinaryNumber.
		TempBinaryNumber = TempBinaryNumber | Temp;

		// TempBinaryNumber contains the full number.
		// Now, need to determine the length in order to find the exponent.
		if (IntegerPartLength != 0)
		{
			// There is an integer part.
			// Used to determine exponent.
			BinaryNumberLength = IntegerPartLength;
			// Shift it to the left for the length of the integer part - 1  (the implied One).
			OutBinaryNumber = TempBinaryNumber >> (BinaryNumberLength);
		}
		else
		{
			// No length needed. The position of the 1st set Bit is given by FirstSetBitPosition.
			OutBinaryNumber = TempBinaryNumber;
		}
	}

	return BinaryNumberLength;
}

/**
 * Function that constructs the binary equivalent of the integer part of a real number.
 *
 * @param DecimalNumber		The integer part of a floating point number
 * @param OutBinaryNumber	The converted number in binary form over 32 bits.
 *
 * @returns The number of digits of the binary number.
 *
 * @see: http://www.catonmat.net/blog/low-level-bit-hacks-you-absolutely-must-know/
 */
int MFloat17::ConstructBinaryNumber(double DecimalNumber, int& OutBinaryNumber)
{
	double Remainder;

	// Represents the total length of the binary number.
	int Index = 0;

	do
	{
		Remainder = fmod(DecimalNumber, 2);
		DecimalNumber = (DecimalNumber - Remainder) / 2;

		if (Remainder == 1)
		{
			// Set the Index Bit to 1.
			OutBinaryNumber = OutBinaryNumber | (1 << Index++);
		}
		else if (Remainder == 0)
		{
			// Set the Index Bit to 0.
			OutBinaryNumber = OutBinaryNumber | (0 << Index++);
		}
	} while (DecimalNumber != 0 /*&& Index < M_Size*/);

	return Index;
}

/**
 * Function that constructs the binary equivalent of the floating point part of a real number.
 *
 * @param	DecimalNumber		The Floating Point part ( 0.XXXX form )
 * @param	OutFirstSetBitPos	The position of the 1st bit that is set to one of the converted number
 * @param	OutBinaryNumber		The converted number in binary form over 32 bits
 */
void MFloat17::ConstructBinaryRemainder(double DecimalNumber, int& OutFirstSetBitPos, unsigned int& OutBinaryNumber)
{
	OutBinaryNumber = 0;
	OutFirstSetBitPos = -1;

	for (int i = 0; i < SIZE_OF_INT - 1; i++)
	{
		DecimalNumber *= 2;

		if (DecimalNumber < 1)
		{
			OutBinaryNumber = OutBinaryNumber | (0);
		}
		else
		{
			if (OutFirstSetBitPos == -1)
			{
				OutFirstSetBitPos = i + 1;
			}

			DecimalNumber -= 1;
			OutBinaryNumber = OutBinaryNumber | (1);
		}
		OutBinaryNumber = OutBinaryNumber << 1;
	}
}

/**
 * Function that computes the mantissa of a Binary number.
 * Takes out the implied bit that is found with either the length of the number or the position of the 1st set bit.
 *
 * @param BinaryNumber	The binary number
 * @param Length		Length (number of digits) of the binary number
 * @param Index			Position of the 1st set bit in the binary number
 *
 * @returns The binary number without the implied one
 */
int MFloat17::ComputeMantissa(int BinaryNumber, int Length, int Index)
{
	// Take out the implied 1 bit.
	if (Length != 0)
	{
		return BinaryNumber & ~(1 << (Length + M_Size));
	}
	else
	{
		return BinaryNumber & ~(1 << (Index));
	}
}

/**
 * Function that returns the two's complement of a number.
 *
 * @param Number	The number
 *
 * @returns The two's complement of the number
 */
int MFloat17::TwoComplement(int Number)
{
	Number = ~Number;
	Number = Number + 1;

	return Number;
}

bool MFloat17::IsZero()
{
	return NumberType == EType::Zero;
}

bool MFloat17::IsInfinity()
{
	return NumberType == EType::Infinity;
}

bool MFloat17::IsNaN()
{
	return NumberType == EType::NaN;
}

bool MFloat17::IsValid()
{
	return NumberType == EType::Valid;
}

#define APPEND_SECTION	NewString.append("|")
#define APPEND_1		NewString.append("1")
#define APPEND_0		NewString.append("0")

/**
 * @returns string equivalent of an MFloat17 number in binary form
 */
std::string MFloat17::ToString()
{
	std::string NewString("");

	if (this->Sign.S)
	{
		APPEND_1;
	}
	else
	{
		APPEND_0;
	}

	APPEND_SECTION;

	unsigned short Exponent = this->Exponent.E;
	for (short i = E_Size - 1; i >= 0; i--)
	{
		if (Exponent & (1 << i))
		{
			APPEND_1;
		}
		else
		{
			APPEND_0;
		}
	}

	APPEND_SECTION;

	unsigned short Mantiss = this->Mantissa.M;
	for (short i = M_Size - 1; i >= 0; i--)
	{
		if (Mantiss & (1 << i))
		{
			APPEND_1;
		}
		else
		{
			APPEND_0;
		}
	}

	return NewString;
}

#undef APPEND_SECTION
#undef APPEND_1
#undef APPEND_0

/**
 * @returns An MFloat17 number converted into a double
 * @author Stephane Gobron
 * @note The algorithm is faulty
 */
double MFloat17::ToDouble()
{
	int m = 0;
	double M = 0.0;
	int e = 0;
	double result;

	int s = Sign.S;

	unsigned short Exponent = this->Exponent.E;
	for (short i = 0; i < E_Size; i++)
	{
		if (Exponent & (1 << i))
		{
			e += std::pow(2, i);
		}
	}

	unsigned short Mantiss = this->Mantissa.M;
	for (short i = 0; i < M_Size; i++)
	{
		if (Mantiss & (1 << i))
		{
			m += std::pow(2, i);
		}
	}

	// Add the implied bit.
	m += std::pow(2, M_Size);

	// Divide by 0x800
	M = ((double)m / pow(2, M_Size + 1));
	if (M >= 0.5 && M < 1 && e - Shift == Shift)
	{
		result = (-2 * s + 1) * (M)* std::pow(2, e - (Shift));
	}
	else
	{
		result = (-2 * s + 1) * (M)* std::pow(2, e - (Shift - 1));
	}

	return result;
}

MFloat17 MFloat17::operator + (const MFloat17& MFloat17Number)
{
	MFloat17* Destination = new MFloat17(0.0);
	MFloatAddition(*this, MFloat17Number, Destination);
	return *Destination;
}

MFloat17 MFloat17::operator * (const MFloat17& MFloat17Number)
{
	MFloat17* Destination = new MFloat17(0.0);
	MFloatMultiplication(*this, MFloat17Number, Destination);
	return *Destination;
}

/**
 * Do addition of two MFloat17 numbers.
 * @param Left			Left MFloat17 operand
 * @param Right			Right MFloat17 operand
 * @param Destination	output MFloat17 number
 *
 * @see Hyde, Randall (2004). Write great code: understanding the machine. Floating-Point Addition and Subtraction (pp. 81-92). No Starch Press, Inc. ISBN 1-59327-003-8
 */
void MFloat17::MFloatAddition(MFloat17 Left, MFloat17 Right, MFloat17*& Destination)
{
	int LExponent = (int)Left.GetE().E - Shift;
	int LMantissa = (int)Left.GetM().M | 0x800;
	int LSign = (int)Left.GetS().S;

	int RExponent = (int)Right.GetE().E - Shift;
	int RMantissa = (int)Right.GetM().M | 0x800;
	int RSign = (int)Right.GetS().S;

	int DExponent;
	int DMantissa;
	int DSign;

	// Special case for zero.
	if (Left.IsZero())
	{
		*Destination = Right;
		return;
	}
	else if (Right.IsZero())
	{
		*Destination = Left;
		return;
	}

	if (LExponent == MAX_EXPONENT)
	{
		if (LMantissa == 0)
		{
			if (RExponent == MAX_EXPONENT)
			{
				//Infinity
				if (RMantissa == 0)
				{
					//Calculate the sum of infinity
					//result is infinity or nan
					if (LSign == RSign)
					{
						//Infinity
						//*Destination = Right;//Or Left, just for the sign
						*Destination = MFloat17(Infinity);
					}
					else
					{
						*Destination = MFloat17(NaN);
					}
				}
				else
				{
					*Destination = MFloat17(NaN);
				}
			}
		}
		// Mantissa non 0 and exp all 1.
		else
		{
			*Destination = MFloat17(NaN);
		}
		//Result has been set: stop.
		return;
	}
	else if (RExponent == MAX_EXPONENT)
	{
		*Destination = MFloat17(NaN);
		//Result has been set: stop.
		return;
	}

	// We've got two actual floating-point values.
	// Let's add them together.
	// First, we have to "de-normalize" one of the operands if their exponents aren't the same (when adding or subtracting values, the exponents must be the same).
	//
	// Algorithm:
	// Choose the value with the smaller exponent.
	// Shift its mantissa to the right the number of bits specified by the difference between the two exponents.

	DExponent = RExponent;
	if (RExponent > LExponent)
	{
		ShiftAndRound(&LMantissa, (RExponent - LExponent));
	}
	else if (RExponent  < LExponent)
	{
		ShiftAndRound(&RMantissa, (LExponent - RExponent));
		DExponent = LExponent;
	}

	//Check if sign is different.
	if (RSign != LSign)
	{
		//We have to subtract the smaller from the bigger.
		if (LMantissa > RMantissa)
		{
			DMantissa = LMantissa - RMantissa;
			DSign = LSign;
		}
		else
		{
			DMantissa = RMantissa - LMantissa;
			DSign = RSign;
		}
	}
	else
	{
		// Signs are the same, so add the values
		DSign = LSign;
		DMantissa = LMantissa + RMantissa;
	}

	//Normalize result

	//If mantissa is in overflow, shift it to right
	if (DMantissa >= 0x1000)
	{
		ShiftAndRound(&DMantissa, 1); // Move result into 24 bits.
		++DExponent; //Counteract the shift by increasing exponent
	}
	else
	{
		//No overflow : normalize result
		if (DMantissa != 0)
		{
			//To normalize, must shift left until the first
			//1 as gone (and decrease the exponent)
			while ((DMantissa < 0x400) && (DExponent > 0))
			{
				DMantissa = DMantissa << 1;
				--DExponent;
			}
		}
		else
		{
			// If the mantissa went to zero, clear everything else, too.
			DSign = 0;
			DExponent = 0;
		}

		MExponent E;
		E.E = DExponent + Shift;
		Destination->SetE(E);

		MSBit S;
		S.S = DSign;
		Destination->SetS(S);

		MMantissa M;
		M.M = DMantissa & 0x7ff;
		Destination->SetM(M);
	}
}

/**
 * Do subtraction of two MFloat17 numbers.
 * @param Left			Left MFloat17 operand
 * @param Right			Right MFloat17 operand
 * @param Destination	output MFloat17 number
 *
 * @see Hyde, Randall (2004). Write great code: understanding the machine. Floating-Point Addition and Subtraction (pp. 81-92). No Starch Press, Inc. ISBN 1-59327-003-8
 */
void MFloat17::MFloatSubtraction(MFloat17 Left, MFloat17 Right, MFloat17*& Destination)
{
	MSBit Sign = Right.GetS();
	Sign.S = Sign.S ^ 1; // Invert the sign bit of the right operand.
	Right.SetS(Sign);
	MFloatAddition(Left, Right, Destination); // Let the addition do the real work.
}

/**
 * Shifts a mantissa to the right the number of bits specified.
 * Rounds the result according to the IEEE rules for rounding, which are:
 *
 * If the bits we shift out are a value that is greater than one-half the value of the LO bit we are left with:
 * then we need to round the value up by adding one to the LO bit position.
 *
 * If the bits we shift out are a value that is less than one-half the value of the LO bit we are left with (after denormalization):
 * then we need to round the value down (i.e., just leave the value alone).
 *
 * If the bits we shift out are exactly one-half the value of the LO bit we are left with:
 * then we need to round the value to the next larger number that has a zero in the LO bit (round up if there's currently a one, or leave the value unchanged if the LO bit contains a zero).
 *
 * @param ValueToShift	The value that must be shifted (mantissa)
 * @param BitsToShift	Number of bits that must be shifted
 *
 * @see Hyde, Randall (2004). Write great code: understanding the machine. Floating-Point Addition and Subtraction (pp. 81-92). No Starch Press, Inc. ISBN 1-59327-003-8
 */
void MFloat17::ShiftAndRound(int* ValueToShift, int BitsToShift)
{
	// Masks is used to mask out bits to check for a "sticky" bit.
	static unsigned masks[11] =
	{
		0, 1, 3, 7, 0xf, 0x1f, 0x3f, 0x7f,
		0xff, 0x1ff, 0x3ff
	};

	// HOmasks: Masks out the HO bit of the value masked by the masks entry.
	static unsigned HOmasks[11] =
	{
		0, 1, 2, 4, 0x8, 0x10, 0x20, 0x40, 0x80,
		0x100, 0x200
	};

	assert(BitsToShift <= M_Size);

	// memory of value before shift
	unsigned int shiftedOut = *ValueToShift & masks[BitsToShift];

	//Shift the value
	*ValueToShift = *ValueToShift >> BitsToShift;

	//Check if should round
	if (shiftedOut > HOmasks[BitsToShift])
	{
		//rounded value > 50% of L0 bit -> add one
		*ValueToShift = *ValueToShift + 1;
	}
	else if (shiftedOut == HOmasks[BitsToShift])
	{
		//rounded value = 50% of L0 bit -> add the value of L0
		*ValueToShift = *ValueToShift + (*ValueToShift & 1);
	}
}

/**
 * Do bitwise multiplication of two MFloat17 numbers.
 *
 * @param Left			Left MFloat17 operand
 * @param Right			Right MFloat17 operand
 * @param Destination	output MFloat17 number
 *
 * @see Hyde, Randall (2004). Write great code: understanding the machine. Floating-Point Multiplication (pp. 93-97). No Starch Press, Inc. ISBN 1-59327-003-8
 */
void MFloat17::MFloatMultiplication(MFloat17 Left, MFloat17 Right, MFloat17*& Destination)
{
	// Check if any of the two floats are 0.0.
	if (Left.IsZero() || Right.IsZero())
	{
		Destination = new MFloat17(0.0);
		return;
	}

	// Compute the sign.
	// Sign = 1 -> negative number | 0 -> positive number
	MSBit Sign;
	Sign.S = Left.GetS().S ^ Right.GetS().S;
	Destination->SetS(Sign);

	// Add the Exponents.
	MExponent TempExp;
	TempExp.E = ((int)Left.GetE().E + (int)Right.GetE().E) - Shift;
	Destination->SetE(TempExp);

	// Multiply the mantissas.
	// @see http://www.cs.umd.edu/class/sum2003/cmsc311/Notes/BinMath/multFloat.html
	MMantissa LMant = Left.GetM();
	MMantissa RMant = Right.GetM();

	// Reveal the implied bits.
	MShiftedMantissa LSMant;
	LSMant.M = LMant.M | (1 << M_Size);

	MShiftedMantissa RSMant;
	RSMant.M = RMant.M | (1 << M_Size);

	unsigned int MultResult = 0;

	// Two ways to do it.
	// 1st way:
	// Multiply the Mantissa operands.
	MultResult = (int)LSMant.M * (int)RSMant.M;

	// 2nd way:
	// Bitwise and of 1st mantissa and each bit of the 2nd mantissa.
	// Shift the result according to the bit's index.
	// Add all the results then shift to only use the Mantissa size.
	/*
	unsigned int BigMantissa[M_Shifted_Size];
	// Now do the multiplication (bitwise AND) and shift.
	for (short iBigMantissa = 0; iBigMantissa < M_Shifted_Size; iBigMantissa++)
	{
	// Get the i-th bit.
	if (RSMant.M & (1 << iBigMantissa))
	{
	// i-th bit is a 1.
	BigMantissa[iBigMantissa] = (LSMant.M << iBigMantissa);
	}
	else
	{
	// i-th bit is a 0.
	BigMantissa[iBigMantissa] = (0);
	}
	}

	// Stupid addition of the BigMantissas.
	for (short iBigMantissa = 0; iBigMantissa < M_Shifted_Size; iBigMantissa++)
	{
	MultResult += BigMantissa[iBigMantissa];
	}
	*/
	/*
	* Rounding problems.
	* if excess = 0 -> drop it.
	* if excess = 1 et excess(+1) = 0 -> roound down = drop it.
	* if excess = excess(+1) = 1 -> round up == +1
	*/

	MultResult = MultResult >> (M_Size);
	/*
	// Rounding.
	// Get the excess bit.
	if (MultResult & (1))
	{
	// If the bit before the excess bit is 1
	if (MultResult & (2))
	{
	// round up
	MultResult++;
	}
	else
	{
	// drop the excess bit.
	MultResult = MultResult >> (1);
	}
	if (false)
	{
	TempExp.E++;
	Destination->SetE(TempExp);
	}
	}
	else
	{
	// drop it
	MultResult = MultResult >> (1);
	}
	*/

	// Unset the implied bit.
	MultResult = MultResult & ~(1 << M_Size);
	Destination->SetM(MultResult);
}

void MFloat17::MFloatDivision(MFloat17 Left, MFloat17 Right, MFloat17*& Destination)
{
	// TODO
}

/**
 * Function that determines the type of an MFloat17 number.
 * Called in constructor only.
 */
void MFloat17::DetermineType()
{
	if (Exponent.E == 31 && Mantissa.M != 0)
	{
		NumberType = EType::NaN;
		return;
	}

	if (Exponent.E == 31 && Mantissa.M == 0)
	{
		NumberType = EType::Infinity;
		return;
	}

	if (Mantissa.M == 0 && Exponent.E == 0)
	{
		NumberType = EType::Zero;
		return;
	}

	{
		NumberType = EType::Valid;
		return;
	}
}

/**
 * Function that sets a MFloat17 number according to a given type.
 * Used in constructor only.
 */
void MFloat17::SetNumberAccordingToType(EType Type)
{
	if (Type == EType::Infinity)
	{
		Exponent.E = 31;
		Mantissa.M = 0;
	}

	if (Type == EType::NaN)
	{
		Exponent.E = 31;
		Mantissa.M = 0x7f;
	}
	if (Type == EType::Zero)
	{
		Exponent.E = 0;
		Mantissa.M = 0;
	}

	if (Type == EType::Valid)
	{
		Exponent.E = Shift;
		Mantissa.M = 0;
	}
}