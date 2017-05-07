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

#include "qdenoisetvl1.h"
#include "opencv2/photo.hpp"

using namespace cv;

/*!
  \qmltype DenoiseTvl1
  \instantiates QDenoiseTvl1
  \inqmlmodule lcvphoto
  \inherits MatFilter
  \brief Denoises a grayscale or color image.

  Performs denoising using the primal-dual algorithm.
*/

/*!
  \class QDenoiseTvl1
  \inmodule lcvphoto_cpp
  \brief Performs denoising using the primal-dual algorithm.
 */

/*!
  \brief QDenoiseTvl1 constructor

  Parameters :
  \a parent
 */
QDenoiseTvl1::QDenoiseTvl1(QQuickItem *parent) :
    QMatFilter(parent),
    m_matBuffer(),
    m_bufferSize(1),
    m_lambda(1.0),
    m_nIters(30){
}

void QDenoiseTvl1::setBufferSize(int bufferSize){
    if ( bufferSize < 1 )
        bufferSize = 1;
    if ( m_bufferSize != bufferSize ){
        m_matBuffer.reserve(bufferSize);
        trimBuffer(bufferSize);
        m_bufferSize = bufferSize;
        emit bufferSizeChanged();
        QMatFilter::transform();
    }
}

void QDenoiseTvl1::trimBuffer(int size){
    if (m_matBuffer.size() > static_cast<std::size_t>(size)){
        size_t elementsToDelete = m_matBuffer.size() - size;
        m_matBuffer.erase(m_matBuffer.begin(), m_matBuffer.begin() + elementsToDelete);
    }
}

/*!
  \brief QDenoiseTvl1 destructor
 */
QDenoiseTvl1::~QDenoiseTvl1(){
}

/*!
  \brief Filter function.

  Parameters:
  \a in
  \a out
 */
void QDenoiseTvl1::transform(Mat &in, Mat &out){
    if ( !in.empty() ) {
        trimBuffer(m_bufferSize - 1);
        m_matBuffer.push_back(in);
        denoise_TVL1(m_matBuffer, out, m_lambda, m_nIters);
    }
}
