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

#ifndef QQMLLIBRARYINFO_H
#define QQMLLIBRARYINFO_H

#include "languageutils/componentversion.h"
#include "qmljs/qmljsdocument.h"

#include <QMap>

namespace lcv{

class QQmlLibraryInfo{

public:
    enum ScanStatus{
        NotScanned = 0,
        ScanError,
        NoPrototypeLink,
        RequiresDependency,
        Done
    };

public:
    class ExportVersion{
    public:
        ExportVersion()
            : versionMajor(-1)
            , versionMinor(-1)
        {}
        ExportVersion(int vma, int vmi, LanguageUtils::FakeMetaObject::ConstPtr o)
            : versionMajor(vma)
            , versionMinor(vmi)
            , object(o)
        {}
        bool isValid() const{ return versionMinor != -1 && versionMajor != -1; }

        int versionMajor;
        int versionMinor;
        LanguageUtils::FakeMetaObject::ConstPtr object;
    };

    class Export{
    public:
        QList<ExportVersion> versions;
    };


public:
    typedef QSharedPointer<QQmlLibraryInfo>       Ptr;
    typedef QSharedPointer<const QQmlLibraryInfo> ConstPtr;

public:
    static Ptr create();
    static Ptr create(const QmlDirParser& parser);

    ~QQmlLibraryInfo();

    QmlJS::LibraryInfo& data(){ return m_data; }
    const QmlJS::LibraryInfo& data() const{ return m_data; }
    QMap<QString, Export>& exports(){ return m_exports; }

    void updateExports();

    void listExports(QStringList* exports);
    ExportVersion findExport(const QString& name);
    ExportVersion findExportByClassName(const QString& name);
    LanguageUtils::FakeMetaObject::ConstPtr findObjectByClassName(const QString& name);

    void setDependencies(const QList<QString> &paths);
    const QList<QString>& dependencyPaths() const;

    void updateImportInfo(const QString& uri, int versionMajor, int versionMinor);

    ScanStatus status() const;
    void setStatus(ScanStatus status);

private:
    QQmlLibraryInfo();
    QQmlLibraryInfo(const QmlDirParser& parser);

private:
    void addExport();

    ScanStatus            m_status;
    QMap<QString, Export> m_exports;
    QmlJS::LibraryInfo    m_data;
    QList<QString>        m_dependencyPaths;
};

inline QQmlLibraryInfo::Ptr QQmlLibraryInfo::create(){
    return QQmlLibraryInfo::Ptr(new QQmlLibraryInfo);
}

inline QQmlLibraryInfo::Ptr QQmlLibraryInfo::create(const QmlDirParser &parser){
    return QQmlLibraryInfo::Ptr(new QQmlLibraryInfo(parser));
}

inline const QList<QString> &QQmlLibraryInfo::dependencyPaths() const{
    return m_dependencyPaths;
}

inline QQmlLibraryInfo::ScanStatus QQmlLibraryInfo::status() const{
    return m_status;
}

inline void QQmlLibraryInfo::setStatus(QQmlLibraryInfo::ScanStatus status){
    m_status = status;
}

}// namespace

#endif // QQMLLIBRARYINFO_H
