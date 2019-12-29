#include "ByteManipulation.h"

unsigned char ByteManipulation::TruncateToByte(unsigned int value)
{
	return (value < 255u) ? static_cast<unsigned char>(value) : 255u;
}

unsigned char ByteManipulation::TruncateToByte(int value)
{
	return (value < 0) 
		? 0 
		: (value > 255) ? 255 : static_cast<unsigned char>(value);
}
