#ifndef SCREEN_RATIO_PRESET_TYPEH_H
#define SCREEN_RATIO_PRESET_TYPEH_H

#include <map>
#include <QObject>
#include <QString>

namespace screen_ratio
{

enum ScreenRatioPresetType
{
	Undefined = 0,
	Ratio_5_4,
	Ratio_16_10,
	Ratio_15_9,
	Ratio_16_9,
	Ratio_21_9,
	Count
};

static const std::map<ScreenRatioPresetType, QString> ScreenRatioPresetTypeName
{
	{ ScreenRatioPresetType::Undefined,   QObject::tr("Undefined") },
	{ ScreenRatioPresetType::Ratio_5_4,   QString("5:4") },
	{ ScreenRatioPresetType::Ratio_16_10, QString("16:10") },
	{ ScreenRatioPresetType::Ratio_15_9,  QString("15:9") },
	{ ScreenRatioPresetType::Ratio_16_9,  QString("16:9") },
	{ ScreenRatioPresetType::Ratio_21_9,  QString("21:9") },
};

/*QString get_screen_ratio_preset_type_name(ScreenRatioPresetType screen_ratio_preset_type)
{
	const auto screen_ratio_preset_type_name = ScreenRatioPresetTypeName.find(screen_ratio_preset_type);
	if (screen_ratio_preset_type_name == ScreenRatioPresetTypeName.end())
	{
		return QObject::tr("Undefined");
	}
	return screen_ratio_preset_type_name->second;
}*/

}

#endif // SCREEN_RATIO_PRESET_TYPEH_H
