/****************************************************************************
**
** Copyright (C) 2014-2017 Dinu SV.
** (contact: mail@dinusv.com)
** This file is part of Live CV Application.
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
****************************************************************************/

#ifndef QPROJECTNAVIGATIONMODEL_H
#define QPROJECTNAVIGATIONMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QHash>
#include <QFutureWatcher>
#include "qlcveditorglobal.h"

namespace lcv{

class QProject;
class QProjectDocument;
class Q_LCVEDITOR_EXPORT QProjectNavigationModel : public QAbstractListModel{

    Q_OBJECT
    Q_PROPERTY(bool isIndexing READ isIndexing NOTIFY isIndexingChanged)

public:
    enum Roles{
        Name = Qt::UserRole + 1,
        Path,
        IsOpen
    };

    class Entry{
    public:
        Entry(const QString& pName, const QString& pPath) : name(pName), path(pPath){}

        QString name;
        QString path;
    };

public:
    QProjectNavigationModel(QProject* project);
    ~QProjectNavigationModel();

    bool isIndexing() const;
    void beginIndexing();
    void endIndexing();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

    const QString& filter() const;

public slots:
    void setFilter(const QString& filter);
    void directoryChanged(const QString& path);
    void reindex();
    void reindexReady();
    void requiresReindex();

signals:
    void isIndexingChanged(bool isIndexing);

private:
    void updateFilters();

    bool m_isIndexing;
    bool m_requiresReindex;
    QFutureWatcher<QList<Entry> > m_workerWatcher;

    QProject*              m_project;
    QList<Entry>           m_files;
    QList<Entry>           m_filteredOpenedFiles;
    QList<int>             m_filteredFiles;
    QHash<int, QByteArray> m_roles;
    QString                m_filter;
};

inline bool QProjectNavigationModel::isIndexing() const{
    return m_isIndexing;
}

inline void QProjectNavigationModel::beginIndexing(){
    m_isIndexing = true;
    emit isIndexingChanged(m_isIndexing);
}

inline void QProjectNavigationModel::endIndexing(){
    m_isIndexing = false;
    emit isIndexingChanged(m_isIndexing);
}

inline QHash<int, QByteArray> QProjectNavigationModel::roleNames() const{
    return m_roles;
}

inline const QString &QProjectNavigationModel::filter() const{
    return m_filter;
}

}// namespace

#endif // QPROJECTNAVIGATIONMODEL_H
