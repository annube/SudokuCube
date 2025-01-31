import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import sudoku.cube.ex 1.0
import "Colors.js" as ColorJS

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Sudoku Cube Explorer")
    color: "grey"
    property int currentColor: CubeModel.FREE
    CubeModel{
        id: cube
        Component.onCompleted: {
            console.log("CubeModel ready");
        }
    }

    GridLayout{
        anchors.fill: parent
        anchors.margins: 5
        Rectangle {
            Layout.alignment: Qt.AlignTop
            color: "transparent"
            implicitWidth: directColoringLayout.implicitWidth + 16
            implicitHeight: directColoringLayout.implicitHeight + 16
            border.color: "black"
            border.width: 3
            MouseArea{
                id: directColoringMA
                anchors.fill: parent
                hoverEnabled: true
            }
            GridLayout {
                id: directColoringLayout
                anchors.centerIn: parent
                anchors.margins: 3
                columns: 3
                ToolTip {
                    delay: 500
                    id: directColoringTT
                    text: "Choose a color here and then click somewhere on the mesh to place the color."
                    parent: parent
                    visible: directColoringMA.containsMouse
                }
                Text {
                    Layout.preferredWidth: 3*20
                    text: "Direct coloring"
                    Layout.columnSpan: 3
                    wrapMode: Text.WordWrap
                    elide:  Text.ElideLeft

                }
                ClickableRect{
                    Layout.columnSpan: 3
                    Layout.fillWidth: true
                    height: 20

                    color: ColorJS.toColor(currentColor)
                }
                Repeater {
                    width: 20
                    height: 100
                    id: colorRepeater
                    model: colorModel
                    delegate: ClickableRect{
                        width: 20
                        height: 20
                        color: ColorJS.toColor(model.color)
                        onRectClicked: {
                            currentColor=model.color;
                        }
                    }
                }
            }
        }

        Rectangle {
            Layout.column: 2
            Layout.alignment: Qt.AlignTop

            color: "transparent"
            implicitWidth: variantsLayout.implicitWidth + 16
            implicitHeight: variantsLayout.implicitHeight + 16
            border.color: "black"
            border.width: 3

            GridLayout {
                id: variantsLayout
                anchors.centerIn: parent
                columns: 4

                VariantRepeater{
                    model: cube.getFaceVariant(0)
                }
                VariantRepeater{
                    model: cube.getFaceVariant(1)
                }
                VariantRepeater{
                    model: cube.getFaceVariant(2)
                }
                VariantRepeater{
                    model: cube.getFaceVariant(3)
                }
                VariantRepeater{
                    model: cube.getFaceVariant(4)
                }
                VariantRepeater{
                    model: cube.getFaceVariant(5)
                }
                VariantRepeater{
                    model: cube.getEdgeVariant(CubeModel.RED);
                }
                VariantRepeater{
                    model: cube.getEdgeVariant(CubeModel.PURPLE);
                }
                VariantRepeater{
                    model: cube.getCornerVariant(CubeModel.GREEN);
                }

            }
        }

        Rectangle {
            Layout.column: 1

            color: "transparent"
            implicitWidth: cubeMeshLayout.implicitWidth + 16
            implicitHeight: cubeMeshLayout.implicitHeight + 16
            border.color: "black"
            border.width: 3

            GridLayout{
                id: cubeMeshLayout
                rowSpacing: 5
                columnSpacing: 5
                anchors.centerIn: parent
                CubeFaceRepresentation{
                    width: 100
                    height: 100
                    Layout.row: 0
                    Layout.column: 1
                    model: cube.getFace(1)
                    onCoordClicked: coord => {
                                        cube.setValue(coord, currentColor)
                                    }
                }
                CubeFaceRepresentation{
                    width: 100
                    height: 100
                    Layout.row: 1
                    Layout.column: 1
                    model: cube.getFace(0)
                    onCoordClicked: coord => {
                                        cube.setValue(coord, currentColor)
                                    }
                }
                CubeFaceRepresentation{
                    width: 100
                    height: 100
                    Layout.row: 2
                    Layout.column: 1
                    model: cube.getFace(2)
                    onCoordClicked: coord => {
                                        cube.setValue(coord, currentColor)
                                    }
                }
                CubeFaceRepresentation{
                    width: 100
                    height: 100
                    Layout.row: 3
                    Layout.column: 1
                    model: cube.getFace(3)
                    onCoordClicked: coord => {
                                        cube.setValue(coord, currentColor)
                                    }
                }

                CubeFaceRepresentation{
                    width: 100
                    height: 100
                    Layout.row: 1
                    Layout.column: 0
                    model: cube.getFace(5)
                    onCoordClicked: coord => {
                                        cube.setValue(coord, currentColor)
                                    }
                }

                CubeFaceRepresentation{
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

}
