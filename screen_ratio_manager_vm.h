#ifndef SCREENRATIOMANAGERVM_H
#define SCREENRATIOMANAGERVM_H

#include <memory>
#include <QAbstractListModel>

#include "screen_ratio_manager.h"

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
		RatioTypeNameRole
	};

	ScreenRatioManagerVM(QObject *parent = nullptr);
	ScreenRatioManagerVM(const ScreenRatioManagerVM &other);

	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	QHash<int, QByteArray> roleNames() const;

	ScreenRatioPreset get_current_ratio_preset();

signals:
	void currentRatioChanged();

private:
	void set_current_ratio(int new_ratio) noexcept;
	int get_current_ratio() const noexcept;

private:
	screen_ratio::ScreenRatioPresetType _current_ratio;
	ScreenRatioManagerPtr _ratio_manager;
};

Q_DECLARE_METATYPE(ScreenRatioManagerVM)

#endif // SCREENRATIOMANAGERVM_H
