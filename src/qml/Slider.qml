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
