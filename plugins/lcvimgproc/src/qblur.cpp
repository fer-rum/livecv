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
#include "qblur.h"
#include "opencv2/imgproc.hpp"

using namespace cv;

/*!
  \qmltype Blur
  \instantiates QBlur
  \inqmlmodule lcvimgproc
  \inherits MatFilter
  \brief Blurs an image using the normalized box filter.

  The function smoothes an image using the normalized box filter.

  \quotefile imgproc/blur.qml
*/

/*!
  \class QBlur
  \inmodule lcvimgproc_cpp
  \brief Box image blur.
 */

/*!
  \brief QBlur constructor

  Parameters :
  \a parent
 */
QBlur::QBlur(QQuickItem *parent)
    : QMatFilter(parent)
    , m_borderType(BORDER_DEFAULT)
    , m_anchor(QPoint(-1, -1))
{
}

/*!
  \brief QBlur destructor
 */
QBlur::~QBlur(){
}

/*!
  \property QBlur::ksize
  \sa Blur::ksize
 */

/*!
  \qmlproperty Size Blur::ksize

  Blurring kernel size
 */

/*!
  \property QBlur::anchor
  \sa Blur::anchor
 */

/*!
  \qmlproperty Point Blur::anchor

  Anchor point; default value Point(-1,-1) means that the anchor is at the kernel center.
 */

/*!
  \property QBlur::borderType
  \sa Blur::borderType
 */

/*!
  \qmlproperty int Blur::borderType

  Border mode used to extrapolate pixels outside of the image.

  \sa CopyMakeBorder::BorderType
 */

/*!
  \brief Transformation function

  Parameters :
  \a in
  \a out
 */
void QBlur::transform(cv::Mat &in, cv::Mat &out){
    blur(in, out, Size(m_ksize.width(), m_ksize.height()), Point(m_anchor.x(), m_anchor.y()), m_borderType);
}
