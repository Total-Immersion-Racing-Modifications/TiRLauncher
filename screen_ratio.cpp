#include "screen_ratio.h"

ScreenRatio::ScreenRatio(int firtst_digit, int second_digit)
	: _firtst_digit(firtst_digit)
	, _second_digit(second_digit)
{
}

int ScreenRatio::get_firtst_digit() const noexcept
{
	return _firtst_digit;
}

int ScreenRatio::get_second_digit() const noexcept
{
	return _second_digit;
}
