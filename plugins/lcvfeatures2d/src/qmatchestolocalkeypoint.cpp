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

#include "qmatchestolocalkeypoint.h"
#include <stdexcept>

QMatchesToLocalKeypoint::QMatchesToLocalKeypoint(QQuickItem *parent)
    : QQuickItem(parent)
    , m_matches1to2(0)
    , m_queryKeypointVector(0)
    , m_output(new QKeyPointToSceneMap)
{
}

QMatchesToLocalKeypoint::~QMatchesToLocalKeypoint(){
    delete m_output;
}

void QMatchesToLocalKeypoint::componentComplete(){
    QQuickItem::componentComplete();
    mapValues();
}

void QMatchesToLocalKeypoint::setQueryWithMatches(QKeyPointVector *query, QDMatchVector *matches){
    m_queryKeypointVector = query;
    m_matches1to2         = matches;

    emit matches1to2Changed();
    emit queryKeypointVectorChanged();

    mapValues();
}

void QMatchesToLocalKeypoint::mapValues(){
    if ( !isComponentComplete() )
        return;
    if ( m_matches1to2 == 0 || m_queryKeypointVector == 0 )
        return;
    if ( !m_matches1to2->matches().size() )
        return;

    m_output->resize(m_trainKeypointVectors.size());
    std::vector<cv::DMatch>& matches = m_matches1to2->matches()[0];

    try{
        for ( std::vector<cv::DMatch>::iterator it = matches.begin(); it != matches.end(); ++it ){
            cv::DMatch& match = *it;
            if ( match.imgIdx >= m_trainKeypointVectors.size() )
                return;
            QKeyPointVector* trainVector = qobject_cast<QKeyPointVector*>(m_trainKeypointVectors[match.imgIdx]);
            if ( !trainVector ){
                qWarning("Invalid keypoint vector given at %d", match.imgIdx);
                return;
            }

            m_output->mappingAt(match.imgIdx)->objectPoints.push_back(
                trainVector->keypoints().at(match.trainIdx).pt
            );
            m_output->mappingAt(match.imgIdx)->scenePoints.push_back(
                m_queryKeypointVector->keypoints().at(match.queryIdx).pt
            );

        }

    } catch ( std::out_of_range& ){
        qCritical("Out of range reached when selecting query descriptor id. Is the query image synced with the matches?");
        m_output->resize(0);
    }

    emit outputChanged();
}

