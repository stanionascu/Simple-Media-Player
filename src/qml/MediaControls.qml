import QtQuick 1.0

Rectangle {
    property bool active: false;
    property alias duration: seekSlider.maximumValue;
    property alias position: seekSlider.value;
    property bool paused: false;

    signal pause();
    signal resume();
    signal seek(int position);

    id: mediaControls;
    state: "OFF";
    opacity: 0.0;

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
            if (mediaControls.paused)
                mediaControls.pause();
            else
                mediaControls.resume();
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

        onPressed: {
            mediaControls.pause();
        }
        onReleased: {
            mediaControls.resume();
        }
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
