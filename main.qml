import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import sudoku.cube.ex 1.0
import "Colors.js" as ColorJS

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    color: "grey"
    property var currentColor: CubeModel.FREE
    CubeModel{
        id: cube
        Component.onCompleted: {
            console.log("CubeModel ready");
        }
    }

    GridLayout{
        GridLayout {
            columns: 3
            Repeater {
                width: 20
                height: 100
                id: repeater
                model: colorModel
                delegate: ClickableRect{
                    width: 20
                    height: 20
                    onRectClicked: {
                        currentColor=model.color;
                    }
                }
            }
        }

        GridLayout{
            rowSpacing: 5
            columnSpacing: 5
            CubeFaceRerpresentation{
                x:100
                y: 0
                width: 100
                height: 100
                Layout.row: 0
                Layout.column: 1
                model: cube.getFace(1)
                onCoordClicked: coord => {
                    cube.setValue(coord, currentColor)
                }
            }
            CubeFaceRerpresentation{
                x:100
                y: 100
                width: 100
                height: 100
                Layout.row: 1
                Layout.column: 1
                model: cube.getFace(0)
                onCoordClicked: coord => {
                    cube.setValue(coord, currentColor)
                }
            }
            CubeFaceRerpresentation{
                x:100
                y: 200
                width: 100
                height: 100
                Layout.row: 2
                Layout.column: 1
                model: cube.getFace(2)
                onCoordClicked: coord => {
                    cube.setValue(coord, currentColor)
                }
            }
            CubeFaceRerpresentation{
                x:100
                y: 300
                width: 100
                height: 100
                Layout.row: 3
                Layout.column: 1
                model: cube.getFace(3)
                onCoordClicked: coord => {
                    cube.setValue(coord, currentColor)
                }
            }

            CubeFaceRerpresentation{
                x:100
                y: 0
                width: 100
                height: 100
                Layout.row: 1
                Layout.column: 0
                model: cube.getFace(5)
                onCoordClicked: coord => {
                    cube.setValue(coord, currentColor)
                }
            }

            CubeFaceRerpresentation{
                x:100
                y: 0
                width: 100
                height: 100
                Layout.row: 1
                Layout.column: 2
                model: cube.getFace(4)
                onCoordClicked: coord => {
                    cube.setValue(coord, currentColor)
                }
            }
        }
    }

}
