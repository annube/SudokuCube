import QtQuick 2.15
import QtQuick.Window 2.15
import sudoku.cube.ex 1.0
import QtQuick.Layouts 1.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    color: "grey"
    CubeModel{
        id: cube
        Component.onCompleted: {
            setValue(0,0,0, CubeModel.BLACK);
            setValue(0,2,0, CubeModel.WHITE);
            setValue(2,0,0, CubeModel.YELLOW);
            setValue(2,2,0, CubeModel.ORANGE);
            setValue(0,0,2, CubeModel.LIGHT_BLUE);
            setValue(0,2,2, CubeModel.BLUE);
            setValue(2,0,2, CubeModel.PURPLE);
            setValue(2,2,2, CubeModel.RED);
            console.log("CubeModel ready");
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
        }
        CubeFaceRerpresentation{
            x:100
            y: 100
            width: 100
            height: 100
            Layout.row: 1
            Layout.column: 1
            model: cube.getFace(0)
        }
        CubeFaceRerpresentation{
            x:100
            y: 200
            width: 100
            height: 100
            Layout.row: 2
            Layout.column: 1
            model: cube.getFace(2)
        }
        CubeFaceRerpresentation{
            x:100
            y: 300
            width: 100
            height: 100
            Layout.row: 3
            Layout.column: 1
            model: cube.getFace(3)
        }

        CubeFaceRerpresentation{
            x:100
            y: 0
            width: 100
            height: 100
            Layout.row: 1
            Layout.column: 0
            model: cube.getFace(5)
        }

        CubeFaceRerpresentation{
            x:100
            y: 0
            width: 100
            height: 100
            Layout.row: 1
            Layout.column: 2
            model: cube.getFace(4)
        }
    }

}
