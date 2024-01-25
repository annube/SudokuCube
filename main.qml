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
                id: colorRepeater
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
        GridLayout {
            columns: 4
            Repeater {
                width: 100
                height: 100
                id: face0VariantRepeater
                model: cube.getFaceVariant(0);
                delegate: ClickableRect{
                    width: 20
                    height: 20
                    color: model.possible == FaceVariantModel.POSSIBLE || model.possible == FaceVariantModel.SELECTED ?"black":"grey"
                    border.width: model.possible == FaceVariantModel.SELECTED ?3:1
                    border.color: "white"
                    onRectClicked: {
                        face0VariantRepeater.model.setVariant(index);
                    }

                }
            }
            Repeater {
                width: 100
                height: 100
                id: face1VariantRepeater
                model: cube.getFaceVariant(1);
                delegate: ClickableRect{
                    width: 20
                    height: 20
                    color: model.possible == FaceVariantModel.POSSIBLE || model.possible == FaceVariantModel.SELECTED ?"orange":"grey"
                    border.width: model.possible == FaceVariantModel.SELECTED ?3:1
                    onRectClicked: {
                        face1VariantRepeater.model.setVariant(index);
                    }
                }
            }
            Repeater {
                width: 100
                height: 100
                id: face2VariantRepeater
                model: cube.getFaceVariant(2);
                delegate: ClickableRect{
                    width: 20
                    height: 20
                    color: model.possible == FaceVariantModel.POSSIBLE || model.possible == FaceVariantModel.SELECTED ?"yellow":"grey"
                    border.width: model.possible == FaceVariantModel.SELECTED ?3:1
                    onRectClicked: {
                        face2VariantRepeater.model.setVariant(index);
                    }
                }
            }
            Repeater {
                width: 100
                height: 100
                id: face3VariantRepeater
                model: cube.getFaceVariant(3);
                delegate: ClickableRect{
                    width: 20
                    height: 20
                    color: model.possible == FaceVariantModel.POSSIBLE || model.possible == FaceVariantModel.SELECTED ?"white":"grey"
                    border.width: model.possible == FaceVariantModel.SELECTED ?3:1
                    onRectClicked: {
                        face3VariantRepeater.model.setVariant(index);
                    }
                }
            }
            Repeater {
                width: 100
                height: 100
                id: face4VariantRepeater
                model: cube.getFaceVariant(4);
                delegate: ClickableRect{
                    width: 20
                    height: 20
                    color: model.possible == FaceVariantModel.POSSIBLE || model.possible == FaceVariantModel.SELECTED ?"blue":"grey"
                    border.width: model.possible == FaceVariantModel.SELECTED ?3:1
                    onRectClicked: {
                        face4VariantRepeater.model.setVariant(index);
                    }
                }
            }
            Repeater {
                width: 100
                height: 100
                id: face5VariantRepeater
                model: cube.getFaceVariant(5);
                delegate: ClickableRect{
                    width: 20
                    height: 20
                    color: model.possible == FaceVariantModel.POSSIBLE || model.possible == FaceVariantModel.SELECTED ?"lightblue":"grey"
                    border.width: model.possible == FaceVariantModel.SELECTED ?3:1
                    onRectClicked: {
                        face5VariantRepeater.model.setVariant(index);
                    }
                }
            }
        }

        GridLayout{
            rowSpacing: 5
            columnSpacing: 5
            CubeFaceRerpresentation{
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
