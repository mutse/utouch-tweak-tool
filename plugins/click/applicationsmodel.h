/*
  This file is part of ut-tweak-tool
  Copyright (C) 2015 Stefano Verzegnassi

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License 3 as published by
  the Free Software Foundation.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see http://www.gnu.org/licenses/.
*/

#ifndef APPLICATIONSMODEL_H
#define APPLICATIONSMODEL_H

#include <QAbstractListModel>

struct AppEntry
{
    bool valid = false;

    QString name;
    QString icon;
    QString exec;
};

class ApplicationsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_DISABLE_COPY(ApplicationsModel)
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)

public:
    enum Roles {
        NameRole,
        IconRole,
        ExecRole
    };

    explicit ApplicationsModel(QAbstractListModel *parent = 0);
    virtual ~ApplicationsModel();

    QHash<int, QByteArray> roleNames() const;

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE QVariantMap get(QString exec) const;

Q_SIGNALS:
    void countChanged();

private:
    QList<AppEntry> m_entries;

    void init();
    AppEntry processDesktopFile(QString path);
    QStringList searchRecursively(QString path, QStringList filters);
};

#endif // APPLICATIONSMODEL_H
