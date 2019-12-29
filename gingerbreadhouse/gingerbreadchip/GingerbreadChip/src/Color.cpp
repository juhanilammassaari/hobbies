#include "Color.h"

Color::Color() 
	:
	red(0u),
	green(0u),
	blue(0u)
{
}

Color::~Color() 
{
}

void Color::Set(const unsigned char red, const unsigned char green, const unsigned char blue)
{
	this->SetRed(red);
	this->SetGreen(green);
	this->SetBlue(blue);
}

void Color::Get(unsigned char& red, unsigned char& green, unsigned char& blue)
{
	red = this->GetRed();
	green = this->GetGreen();
	blue = this->GetBlue();
}

inline void Color::SetRed(const unsigned char red)
{
	this->red = red;
}

inline void Color::SetGreen(const unsigned char green)
{
	this->green = green;
}


inline void Color::SetBlue(const unsigned char blue)
{
	this->blue = blue;
}


inline unsigned char Color::GetRed()
{
	return this->red;
}

inline unsigned char Color::GetGreen()
{
	return this->green;
}

inline unsigned char Color::GetBlue()
{
	return this->blue;
}
