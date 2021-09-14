#ifndef SCREENRATIOVM_H
#define SCREENRATIOVM_H

#include <QObject>

#include "screen_ratio_preset_type.h"

namespace screen_ratio
{

class ScreenRatioManager
{
public:
	using ScreenRatioPreset = std::pair<int, int>;

	ScreenRatioManager();
	ScreenRatioPreset get_ratio_preset(ScreenRatioPresetType screen_ratio_preset_type) const;
	std::vector<ScreenRatioPresetType> get_avaible_screen_ratios() const noexcept;

private:
	std::vector<ScreenRatioPresetType> generate_avaible_screen_ratios() noexcept;

private:
	const std::vector<ScreenRatioPresetType> _avaible_screen_ratios;
};

} // namespace screen_ratio

#endif // SCREENRATIOVM_H
