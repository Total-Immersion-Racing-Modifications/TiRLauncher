#include "screen_ratio_manager_vm.h"

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

int ScreenRatioManagerVM::rowCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return static_cast<int>(_ratio_manager->get_avaible_screen_ratios().size());
}

QVariant ScreenRatioManagerVM::data(const QModelIndex &index, int role) const
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
	default:
		return QVariant();
	}
}

QHash<int, QByteArray> ScreenRatioManagerVM::roleNames() const
{
	QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
	roles[RatioTypeRole] = "r_ratio_type";
	roles[RatioTypeNameRole] = "r_ratio_type_name";
	return roles;
}

void ScreenRatioManagerVM::set_current_ratio(int new_ratio) noexcept
{
	_current_ratio = static_cast<screen_ratio::ScreenRatioPresetType>(new_ratio);
	emit currentRatioChanged();
}

int ScreenRatioManagerVM::get_current_ratio() const noexcept
{
	return static_cast<int>(_current_ratio);
}
