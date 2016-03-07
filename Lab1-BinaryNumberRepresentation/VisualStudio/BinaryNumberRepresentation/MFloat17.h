/********************************************************************
	created:	2015/03/08
	created:	8:3:2015   21:41
	filename: 	C:\Development\Projects\NumericAlgorithms\BinaryNumberRepresentation\BinaryNumberRepresentation\MFloat17.h
	file path:	C:\Development\Projects\NumericAlgorithms\BinaryNumberRepresentation\BinaryNumberRepresentation
	file base:	MFloat17
	file ext:	h
	author:		Horia Mut, Nils Ryter, Romain Claret Yakovenko

	purpose:	Class declaration with inline functions
	*********************************************************************/

#pragma once
#include <string>
#include "MTypes.h"

// Mantissa over 11 bits : 11 precise BINARY digits.
#define ERROR_MARGIN 0.0001
#define SIZE_OF_INT 32

#pragma pack(push)
#pragma pack(1)

/* Number types. */
enum EType { Zero, Valid, NaN, Infinity };

/**
 * Class that encodes a real number over 17 bits.
 * 1 bit for sign, 5 for exponent, 11 for mantissa, Shift = 15
 * Exponent: 11110b = 30d - Shift = 15d -> 2^15 max power
 */
class MFloat17
{
public:
	/* Default constructor. */
	MFloat17(){}

	/**
	 * Class that encodes a real number over 17 bits.
	 * @param DecimalValue: the value to encode on 17 bits.
	 */
	MFloat17(double DecimalValue)
	{
		int Temp = 0;
		int Length = 0;
		int PosOf1stOneBit = 0;

		if (DecimalValue < 0)
		{
			Sign.S = 1;
			Length = FindBinaryNumber(-(DecimalValue), Temp, PosOf1stOneBit);
		}
		else
		{
			Sign.S = 0;
			Length = FindBinaryNumber(DecimalValue, Temp, PosOf1stOneBit);
		}

		if (Length == 0)
		{
			Exponent.E = TwoComplement(-(-(/*SIZE_OF_INT -*/ PosOf1stOneBit)+Shift));
		}
		else
		{
			if (DecimalValue == 0)
			{
				Exponent.E = 0;
			}
			else
			{
				Exponent.E = TwoComplement(-(Length - 1 + Shift));
			}
		}

		// Temp contains the full binary number now.
		// Build the truncated mantissa.
		Mantissa.M = ComputeMantissa(Temp, Length, PosOf1stOneBit);

		DetermineType();
	}

	/**
	 * Encode a real number according to a specific type.
	 * @param Type		The type @see(EType) of the number
	 */
	MFloat17(EType Type)
	{
		NumberType = Type;
		SetNumberAccordingToType(Type);
	}

public:
	/* Setters
	************************************************************************/
	void SetS(MSBit S){ Sign = S; }
	void SetE(MExponent E){ Exponent = E; }
	void SetM(MMantissa M){ Mantissa = M; }
	void SetM(unsigned short M){ Mantissa.M = M; }

	/* Getters
	************************************************************************/
	MSBit GetS(){ return Sign; }
	MExponent GetE(){ return Exponent; }
	MMantissa GetM() { return Mantissa; }

	/* Conversion tools
	************************************************************************/

	/**
	* @returns string equivalent of an MFloat17 number in binary form
	*/
	std::string ToString();

	/**
	* @returns An MFloat17 number converted into a double
	*/
	double ToDouble();

	/* Test tools
	************************************************************************/
	bool IsZero();
	bool IsNaN();
	bool IsInfinity();
	bool IsValid();

	void UpdateType(){ this->DetermineType(); }

public:

	/* Operator overloads
	************************************************************************/

	MFloat17 operator + (const MFloat17& MFloat17Number);
	MFloat17 operator * (const MFloat17& MFloat17Number);

protected:
private:

	/* Tools
	************************************************************************/

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
	int FindBinaryNumber(double DecimalNumber, int& OutBinaryNumber, int& OutFirstSetBitPosition);

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
	int ConstructBinaryNumber(double DecimalNumber, int& OutBinaryNumber);

	/**
	* Function that constructs the binary equivalent of the floating point part of a real number.
	*
	* @param	DecimalNumber		The Floating Point part ( 0.XXXX form )
	* @param	OutFirstSetBitPos	The position of the 1st bit that is set to one of the converted number
	* @param	OutBinaryNumber		The converted number in binary form over 32 bits
	*/
	void ConstructBinaryRemainder(double DecimalNumber, int& OutFirstSetBitPos, unsigned int& OutBinaryNumber);

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
	int ComputeMantissa(int BinaryNumber, int Length, int Index);

	/**
	* Function that returns the two's complement of a number.
	*
	* @param Number	The number
	*
	* @returns The two's complement of the number
	*/
	int TwoComplement(int Number);

	/**
	* Function that determines the type of an MFloat17 number.
	* Called in constructor only.
	*/
	void DetermineType();

	/**
	* Function that sets a MFloat17 number according to a given type.
	* Used in constructor only.
	*/
	void SetNumberAccordingToType(EType Type);

	/* Operations
	************************************************************************/

	/**
	* Do addition of two MFloat17 numbers.
	* @param Left			Left MFloat17 operand
	* @param Right			Right MFloat17 operand
	* @param Destination	output MFloat17 number
	*
	* @see Hyde, Randall (2004). Write great code: understanding the machine. Floating-Point Addition and Subtraction (pp. 81-92). No Starch Press, Inc. ISBN 1-59327-003-8
	*/
	void MFloatAddition(MFloat17 Left, MFloat17 Right, MFloat17*& Destination);

	/**
	* Do subtraction of two MFloat17 numbers.
	* @param Left			Left MFloat17 operand
	* @param Right			Right MFloat17 operand
	* @param Destination	output MFloat17 number
	*
	* @see Hyde, Randall (2004). Write great code: understanding the machine. Floating-Point Addition and Subtraction (pp. 81-92). No Starch Press, Inc. ISBN 1-59327-003-8
	*/
	void MFloatSubtraction(MFloat17 Left, MFloat17 Right, MFloat17*& Destination);

	void MFloatDivision(MFloat17 Left, MFloat17 Right, MFloat17*& Destination);

	/**
	* Do bitwise multiplication of two MFloat17 numbers.
	*
	* @param Left			Left MFloat17 operand
	* @param Right			Right MFloat17 operand
	* @param Destination	output MFloat17 number
	*
	* @see Hyde, Randall (2004). Write great code: understanding the machine. Floating-Point Multiplication (pp. 93-97). No Starch Press, Inc. ISBN 1-59327-003-8
	*/
	void MFloatMultiplication(MFloat17 Left, MFloat17 Right, MFloat17*& Destination);

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
	void ShiftAndRound(int* ValueToShift, int BitsToShift);

	/* Attributes
	************************************************************************/

	EType NumberType;
	MSBit Sign;
	MExponent Exponent;
	MMantissa Mantissa;
};
#pragma pack(pop)