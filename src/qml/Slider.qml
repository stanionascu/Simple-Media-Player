/************************************************************************************
** Simple Media Player, allows to watch videos with simple and uncluttered interface.
** Copyright (C) 2011 Stanislav Ionascu
**
** Contact: Stanislav Ionascu <stanislav.ionascu@gmail.com>
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.

** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************************/

import QtQuick 1.0

Rectangle {
    property int value: 0;
    property int maximumValue: 100;

    signal pressed();
    signal released();
    signal seeked(int seekValue);

    id: slider;
    color: "darkGray";
    height: 5;

    function calculateWidth() {
        return slider.width * (value / maximumValue);
    }

    Rectangle {
        color: "black";
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        width: calculateWidth();
    }

    MouseArea {
        anchors.fill: parent;
        onPressed: {
            slider.pressed();
        }
        onReleased: {
            slider.released();
        }
        onMousePositionChanged: {
            if (mouseX > 0 && mouseX < width)
                slider.seeked(maximumValue * (mouseX / width));
        }
    }
}
