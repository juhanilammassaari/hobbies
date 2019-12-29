#pragma once

class Color 
{
public:
	Color();
	virtual ~Color();
	virtual void Set(const unsigned char red, const unsigned char green, const unsigned char blue);
	virtual void Get(unsigned char& red, unsigned char& green, unsigned char& blue);
	virtual void SetRed(const unsigned char red);
	virtual void SetGreen(const unsigned char green);
	virtual void SetBlue(const unsigned char blue);
	virtual unsigned char GetRed();
	virtual unsigned char GetGreen();
	virtual unsigned char GetBlue();

private:
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};