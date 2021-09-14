#include "screen_ratio_manager.h"
#include "screen_ratio_preset_type.h"
#include <map>

namespace
{
using namespace screen_ratio;
const std::map<ScreenRatioPresetType, ScreenRatioManager::ScreenRatioPreset> screen_ratio_presets
{
	{ ScreenRatioPresetType::Ratio_16_9, std::make_pair(0x3FE20000, 0x3cb01d9f) }
};
} // namespace

namespace screen_ratio
{

ScreenRatioManager::ScreenRatioManager()
	: _avaible_screen_ratios(generate_avaible_screen_ratios())
{
}

ScreenRatioManager::ScreenRatioPreset ScreenRatioManager::get_ratio_preset(ScreenRatioPresetType screen_ratio_preset_type) const
{
	const auto screen_ratio_preset = screen_ratio_presets.find(screen_ratio_preset_type);
	if (screen_ratio_preset == screen_ratio_presets.end())
	{
		throw std::exception("Can not find needed preset");
	}
	return screen_ratio_preset->second;
}

std::vector<ScreenRatioPresetType> ScreenRatioManager::get_avaible_screen_ratios() const noexcept
{
	return _avaible_screen_ratios;
}

std::vector<ScreenRatioPresetType> ScreenRatioManager::generate_avaible_screen_ratios() noexcept
{
	std::vector<ScreenRatioPresetType> avaible_screen_ratios;
	for (const auto& screen_ratio_preset : screen_ratio_presets)
	{
		avaible_screen_ratios.emplace_back(screen_ratio_preset.first);
	}
	return avaible_screen_ratios;
}

}
