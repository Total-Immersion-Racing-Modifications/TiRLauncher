#include "screen_ratio_manager_vm.h"

#include <QDebug>

ScreenRatioManagerVM::ScreenRatioManagerVM(QObject *parent)
	: QAbstractListModel(parent)
	, _current_ratio(screen_ratio::ScreenRatioPresetType::Undefined)
	, _ratio_manager(std::make_shared<screen_ratio::ScreenRatioManager>())
{
	if (_ratio_manager == nullptr)
	{
		throw std::exception("Ratio Manager is null");
	}
}

ScreenRatioManagerVM::ScreenRatioManagerVM(const ScreenRatioManagerVM &other)
	: _current_ratio(other._current_ratio)
	, _ratio_manager(other._ratio_manager)
{
}

int ScreenRatioManagerVM::rowCount(const QModelIndex& parent) const noexcept
{
	Q_UNUSED(parent);
	return static_cast<int>(_ratio_manager->get_avaible_screen_ratios().size());
}

QVariant ScreenRatioManagerVM::data(const QModelIndex &index, int role) const
{
	try
	{
		if (!index.isValid())
		{
			return QVariant();
		}

		const auto ratio = _ratio_manager->get_avaible_screen_ratios().at(index.row());

		switch (static_cast<Roles>(role))
		{
		case RatioTypeRole:
			return static_cast<int>(ratio);
		case RatioTypeNameRole:
		{
			const auto screen_ratio_preset_type_name = screen_ratio::ScreenRatioPresetTypeName.find(ratio);
			if (screen_ratio_preset_type_name == screen_ratio::ScreenRatioPresetTypeName.end())
			{
				return QObject::tr("Undefined");
			}
			return screen_ratio_preset_type_name->second;
		}
		case ChoosedRole:
			return ratio == _current_ratio;
		default:
			return QVariant();
		}
	}
	catch (std::exception &e)
	{
		qDebug() << "Failed to get data at role " << role << " " << e.what();
		return {};
	}
}

QHash<int, QByteArray> ScreenRatioManagerVM::roleNames() const noexcept
{
	QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
	roles[RatioTypeRole] = "r_ratio_type";
	roles[RatioTypeNameRole] = "r_ratio_type_name";
	roles[ChoosedRole] = "r_choosed";
	return roles;
}

ScreenRatioManagerVM::ScreenRatioPreset ScreenRatioManagerVM::get_current_ratio_preset() const
{
	return _ratio_manager->get_ratio_preset(_current_ratio);
}

void ScreenRatioManagerVM::set_current_ratio(int new_ratio) noexcept
{
	try
	{
		const auto ratio = static_cast<screen_ratio::ScreenRatioPresetType>(new_ratio);
		if (_current_ratio == ratio)
		{
			return;
		}
		_current_ratio = static_cast<screen_ratio::ScreenRatioPresetType>(new_ratio);
		emit currentRatioChanged();
	}
	catch (std::exception &e)
	{
		qDebug() << "Failed to set new ratio: " << e.what();
	}
}

int ScreenRatioManagerVM::get_current_ratio() const noexcept
{
	return static_cast<int>(_current_ratio);
}
