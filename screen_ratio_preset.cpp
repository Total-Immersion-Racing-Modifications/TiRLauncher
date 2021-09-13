#include "screen_ratio_preset.h"

ScreenRatioPreset::ScreenRatioPreset(int firtst_digit, int second_digit)
	: _firtst_digit(firtst_digit)
	, _second_digit(second_digit)
{
}

int ScreenRatioPreset::get_firtst_digit() const noexcept
{
	return _firtst_digit;
}

int ScreenRatioPreset::get_second_digit() const noexcept
{
	return _second_digit;
}
