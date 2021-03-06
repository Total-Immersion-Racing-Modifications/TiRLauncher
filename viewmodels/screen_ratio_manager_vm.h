#ifndef SCREENRATIOMANAGERVM_H
#define SCREENRATIOMANAGERVM_H

#include <memory>
#include <QAbstractListModel>

#include "screen_ratio/screen_ratio_manager.h"

class ScreenRatioManagerVM : public QAbstractListModel
{
	Q_OBJECT

	using ScreenRatioManagerPtr = std::shared_ptr<screen_ratio::ScreenRatioManager>;
	using ScreenRatioPreset = std::pair<int, int>;

	Q_PROPERTY(int current_ratio READ get_current_ratio WRITE set_current_ratio NOTIFY currentRatioChanged);

public:
	enum Roles
	{
		RatioTypeRole = Qt::UserRole + 1,
		RatioTypeNameRole,
		ChoosedRole
	};

	ScreenRatioManagerVM(QObject *parent = nullptr);
	ScreenRatioManagerVM(const ScreenRatioManagerVM &other);

	int rowCount(const QModelIndex& parent = QModelIndex()) const noexcept;
	QVariant data(const QModelIndex &index, int role) const;
	QHash<int, QByteArray> roleNames() const noexcept;

	ScreenRatioPreset get_current_ratio_preset() const;
	int get_current_ratio() const noexcept;
	void set_current_ratio(int new_ratio) noexcept;

signals:
	void currentRatioChanged();

private:
	screen_ratio::ScreenRatioPresetType _current_ratio;
	const ScreenRatioManagerPtr _ratio_manager;
};

Q_DECLARE_METATYPE(ScreenRatioManagerVM)

#endif // SCREENRATIOMANAGERVM_H
