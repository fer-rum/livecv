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

import QtQuick 2.0

Item{

    id : root

    property Item item : Item{}

    MouseArea{
        anchors.fill : parent
        onClicked : {
            root.item.regionX = mouse.x - 10
            root.item.regionY = mouse.y - 10
        }
    }
    Rectangle{
        width : root.item.regionWidth
        height : root.item.regionHeight
        color : "transparent"
        border.width : 1
        border.color : "#ff0000"
        x: root.item.regionX
        y: root.item.regionY
    }

}
