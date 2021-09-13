#ifndef SCREENRATIO_H
#define SCREENRATIO_H

#include <QObject>

class ScreenRatio
{
public:
	ScreenRatio(int firtst_digit, int second_digit);

	int get_firtst_digit() const noexcept;
	int get_second_digit() const noexcept;

private:
	const int _firtst_digit;
	const int _second_digit;
};

#endif // SCREENRATIO_H
