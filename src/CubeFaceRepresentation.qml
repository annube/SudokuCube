import QtQuick 2.15
import sudoku.cube.ex 1.0
import "Colors.js" as ColorJS

Item {
    property alias model: table.model
    signal coordClicked(coord: intvec3d)
    Rectangle {
        id: frame
        anchors.fill: parent
        color: "transparent"
        border.color: "black"
        border.width: 3
        TableView
        {
            columnSpacing: 3
            rowSpacing: 3
            anchors.margins: 3
            anchors.fill: parent
            id: table


            delegate:
                ClickableRect{
                implicitHeight: (frame.width-2*table.rowSpacing - 2*table.anchors.margins)/3
                implicitWidth: (frame.height-2*table.columnSpacing - 2*table.anchors.margins)/3
                onRectClicked: {
                    coordClicked(table.model.coordFromIndex(modelIndex));
                }
            }
        }
    }


}
