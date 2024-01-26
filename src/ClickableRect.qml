import QtQuick 2.15
import sudoku.cube.ex 1.0
import "Colors.js" as ColorJS

Rectangle{
    id: rect
    border.color: color==Qt.color("black")?"white":"black"
    color: ColorJS.toColor(model.color)

    signal rectClicked()

    states: State {
        name: "down"; when: mouseArea.pressed == true
        PropertyChanges {
            rect {
                border.width: 3
            }
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            rectClicked();
        }
    }
}
