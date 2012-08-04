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

Rectangle {
    property bool active: true
    property alias duration: seekSlider.maximumValue;
    property alias position: seekSlider.value;
    property bool paused: false;

    signal seek(int position);

    id: mediaControls;
    state: "OFF";


    MouseArea {
        anchors.fill: parent;
    }

    function show() {
        mediaControls.state = "ON";
    }

    function hide() {
        mediaControls.state = "OFF";
    }

    function dateTimeFromInt(seconds) {
        var hours = (seconds / 60 / 60);
        var time = Date(0, 0, 0, hours, 0, 0);
        return time;
    }

    states: [
        State {
            name:  "OFF";
            PropertyChanges { target: mediaControls; opacity: 0.0; active: false; }
        },
        State {
            name:  "ON";
            PropertyChanges { target:  mediaControls; opacity: 0.95; active: true; }
        }
    ]

    transitions: [
        Transition {
            from: "OFF"
            to: "ON"
            PropertyAnimation { target: mediaControls; properties: "opacity"; duration: 200; }
        },
        Transition {
            from: "ON"
            to: "OFF"
            PropertyAnimation { target: mediaControls; properties: "opacity"; duration: 200; }
        }
    ]

    IconButton {
        id: playButton;
        width: 32;
        height: 32;

        source: paused ? "image://system/media-pause" : "image://system/media-play" ;

        onClicked: {
            mediaControls.paused = !mediaControls.paused;
        }
    }
    Text {
        anchors.left: playButton.right;
        anchors.verticalCenter: parent.verticalCenter;
        id: currentTime;
        text: Qt.formatTime(new Date(0, 0, 0, 0, 0, position), "hh:mm:ss");
    }
    Slider {
        id: seekSlider;
        anchors.left: currentTime.right;
        anchors.right: totalTime.left;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.leftMargin: 15;
        anchors.rightMargin: 15;

        onSeeked: {
            mediaControls.seek(seekValue);
        }
    }
    Text {
        anchors.right: parent.right;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.rightMargin: 15;
        id: totalTime;
        text: Qt.formatTime(new Date(0, 0, 0, 0, 0, duration), "hh:mm:ss");
    }
}
