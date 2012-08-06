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

import QtQuick 2.0
import QtMultimedia 5.0
import com.ionascu.SMP 1.0

Rectangle {
    id: root
    width: 320;
    height: 240;
    color: "black"

    Video {
        id: video
        anchors.fill: parent
        source: currentVideo

        Component.onCompleted: {
            play()
        }

        onPlaying: {
            mediaControls.paused = false
        }

        onPaused: {
            mediaControls.paused = true
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (mediaControls.state === "ON")
                mediaControls.state = "OFF"
            else
                mediaControls.state = "ON"
        }
    }

    MediaControls {
        id: mediaControls;
        anchors.bottom: parent.bottom;
        anchors.left: parent.left;
        anchors.right: parent.right;
        height: 32;

        duration: video.duration / 1000;
        position: video.position / 1000;

        onPausedChanged: {
            if (mediaControls.paused)
                video.play()
            else
                video.pause()
        }

        onSeek: {
        }
    }
}
