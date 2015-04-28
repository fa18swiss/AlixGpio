#pragma once
class IGpio
{
public:

	IGpio()
	{
	}

	virtual ~IGpio()
	{
	}
	virtual void SetPin(int pin, bool high) = 0;
};

