#ifndef REGISTERED_ENUMS_H
#define REGISTERED_ENUMS_H

#include <QObject>

#include "screen_ratio/screen_ratio_preset_type.h"

class ScreenRatioPresetType : public QObject
{
	Q_OBJECT
public:
	explicit ScreenRatioPresetType(QObject *parent = nullptr);

	enum class Enum
	{
		Undefined = screen_ratio::ScreenRatioPresetType::Undefined,
		Ratio_5_4 = screen_ratio::ScreenRatioPresetType::Ratio_5_4,
		Ratio_16_10 = screen_ratio::ScreenRatioPresetType::Ratio_16_10,
		Ratio_15_9 = screen_ratio::ScreenRatioPresetType::Ratio_15_9,
		Ratio_16_9 = screen_ratio::ScreenRatioPresetType::Ratio_16_9,
		Ratio_21_9 = screen_ratio::ScreenRatioPresetType::Ratio_21_9,
		Count = screen_ratio::ScreenRatioPresetType::Count
	};

	Q_ENUM(Enum)
};

#endif // REGISTERED_ENUMS_H
