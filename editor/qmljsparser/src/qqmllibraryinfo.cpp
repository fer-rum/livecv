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

#include "qqmllibraryinfo_p.h"

namespace lcv{

QQmlLibraryInfo::QQmlLibraryInfo()
    : m_status(QQmlLibraryInfo::NotScanned)
{
}

QQmlLibraryInfo::QQmlLibraryInfo(const QmlDirParser &parser)
    : m_status(QQmlLibraryInfo::NotScanned)
    , m_data(parser)
{
}

QQmlLibraryInfo::~QQmlLibraryInfo(){
}

void QQmlLibraryInfo::updateExports(){
    m_exports.clear();
    foreach( const LanguageUtils::FakeMetaObject::ConstPtr& obj, m_data.metaObjects()){
        foreach( const LanguageUtils::FakeMetaObject::Export& e, obj->exports() ){
            if ( e.version.isValid() ){
                m_exports[e.type].versions.append(ExportVersion(e.version.majorVersion(), e.version.minorVersion(), obj));
            }
        }
    }
}

void QQmlLibraryInfo::listExports(QStringList *exports){
    for ( QMap<QString, QQmlLibraryInfo::Export>::ConstIterator it = m_exports.begin(); it != m_exports.end(); ++it ){
        exports->append(it.key());
    }
}

QQmlLibraryInfo::ExportVersion QQmlLibraryInfo::findExport(const QString &type){
    QQmlLibraryInfo::ExportVersion base;
    if ( m_exports.contains(type) ){
        QQmlLibraryInfo::Export e = m_exports.value(type);
        foreach( QQmlLibraryInfo::ExportVersion ev, e.versions ){
            if ( ev.versionMajor > base.versionMajor )
                base = ev;
            else if ( ev.versionMajor == base.versionMajor && ev.versionMinor > base.versionMinor )
                base = ev;
        }
    }
    return base;
}

QQmlLibraryInfo::ExportVersion QQmlLibraryInfo::findExportByClassName(const QString &name){
    QQmlLibraryInfo::ExportVersion base;
    foreach( const LanguageUtils::FakeMetaObject::ConstPtr& obj, m_data.metaObjects()){
        if ( obj->className() == name ){
            foreach( const LanguageUtils::FakeMetaObject::Export& e, obj->exports() ){
                if ( e.version.isValid() ){
                    return findExport(e.type);
                }
            }
            return base;
        }
    }
    return base;
}

LanguageUtils::FakeMetaObject::ConstPtr QQmlLibraryInfo::findObjectByClassName(const QString &name){
    foreach( const LanguageUtils::FakeMetaObject::ConstPtr& obj, m_data.metaObjects()){
        if ( obj->className() == name )
            return obj;
    }
    return LanguageUtils::FakeMetaObject::ConstPtr(0);
}

void QQmlLibraryInfo::setDependencies(const QList<QString> &paths){
    m_dependencyPaths = paths;
}

}// namespace
