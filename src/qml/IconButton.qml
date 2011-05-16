import QtQuick 1.0

Image {
    signal clicked();

    id: iconButton;
    state: "UP";
    MouseArea {
        anchors.fill: parent;
        onPressed: {
            iconButton.state = "DOWN";
        }
        onReleased: {
            iconButton.state = "UP";
            iconButton.clicked();
        }
    }

    states: [
        State {
            name: "DOWN";
            PropertyChanges { target: iconButton; opacity: 0.5; }
        },
        State {
            name: "UP";
            PropertyChanges { target: iconButton; opacity: 1.0; }
        }
    ]
}
