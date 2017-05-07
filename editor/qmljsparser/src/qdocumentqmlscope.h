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

#ifndef QDOCUMENTSCOPE_H
#define QDOCUMENTSCOPE_H

#include "qqmljsparserglobal.h"
#include <QString>
#include <QSharedPointer>
#include "qprojectqmlscope.h"
#include "qdocumentqmlinfo.h"

namespace lcv{

class Q_QMLJSPARSER_EXPORT QDocumentQmlScope{

public:
    typedef QSharedPointer<QDocumentQmlScope> Ptr;

    class Import{

    public:
        static const int NoVersion;

        enum Type{
            Invalid,
            Library,
            Directory,
            ImplicitDirectory,
            File,
            UnknownFile
        };

        Import(
            Type importType,
            const QString& path,
            const QString& as = "",
            int vMajor = NoVersion,
            int vMinor = NoVersion
        );


        Type importType() const;
        void setImportType(Type importType);

        const QString& path() const;
        const QString& as() const;
        int versionMajor() const;
        int versionMinor() const;
        bool isVersionValid() const;

        bool operator ==(const Import& other) const;

    private:
        Type    m_type;
        QString m_path;
        QString m_as;
        int     m_versionMajor;
        int     m_versionMinor;
    };

    typedef QPair<Import, QString> ImportEntry;
    typedef QList<ImportEntry> ImportList;

private:
    QDocumentQmlScope(QProjectQmlScope::Ptr projectScope, QDocumentQmlInfo::MutablePtr documentInfo);

public:
    ~QDocumentQmlScope();

    static QDocumentQmlScope::Ptr createEmptyScope(
        QProjectQmlScope::Ptr projectScope
    );
    static QDocumentQmlScope::Ptr createScope(
        const QString& fileName,
        const QString& data,
        QProjectQmlScope::Ptr projectScope
    );

    static QList<Import> extractImports(QDocumentQmlInfo::MutablePtr document);

    bool hasImport(const Import& key);
    int totalImports() const;
    const ImportList& imports() const;

    void addImport(const Import& key, const QString& path);

    QDocumentQmlInfo::Ptr info() const;
    QProjectQmlScope::Ptr projectScope() const;

    QString path() const;
    QString componentName() const;

private:
    ImportList                   m_imports;
    QProjectQmlScope::Ptr        m_projectScope;
    QDocumentQmlInfo::MutablePtr m_documentInfo;
};

inline int QDocumentQmlScope::Import::versionMajor() const{
    return m_versionMajor;
}

inline int QDocumentQmlScope::Import::versionMinor() const{
    return m_versionMinor;
}

inline bool QDocumentQmlScope::Import::isVersionValid() const{
    return m_versionMajor >= 0 && m_versionMinor >= 0;
}

inline bool QDocumentQmlScope::Import::operator ==(const QDocumentQmlScope::Import &other) const{
    if ( path() != other.path() )
        return false;
    if ( versionMajor() != other.versionMajor() )
        return false;
    return versionMinor() == other.versionMinor();
}

inline const QString &QDocumentQmlScope::Import::path() const{
    return m_path;
}

inline void QDocumentQmlScope::Import::setImportType(QDocumentQmlScope::Import::Type importType){
    m_type = importType;
}

inline QDocumentQmlScope::Import::Type QDocumentQmlScope::Import::importType() const{
    return m_type;
}

inline const QString &QDocumentQmlScope::Import::as() const{
    return m_as;
}

inline int QDocumentQmlScope::totalImports() const{
    return m_imports.size();
}

inline QDocumentQmlInfo::Ptr QDocumentQmlScope::info() const{
    return m_documentInfo;
}

inline const QDocumentQmlScope::ImportList &QDocumentQmlScope::imports() const{
    return m_imports;
}

inline QProjectQmlScope::Ptr QDocumentQmlScope::projectScope() const{
    return m_projectScope;
}

inline QString QDocumentQmlScope::path() const{
    return m_documentInfo->path();
}

inline QString QDocumentQmlScope::componentName() const{
    return m_documentInfo->componentName();
}

}// namespace

#endif // QDOCUMENTSCOPE_H
