import QtQuick 2.15
import sudoku.cube.ex 1.0

import "Colors.js" as ColorJS

Repeater {
    width: 100
    height: 100
    id: repeater
    delegate: ClickableRect{
        width: 20
        height: 20
        color: model.possible === VariantModel.POSSIBLE || model.possible === VariantModel.SELECTED ?
                   ColorJS.toColor(repeater.model.color()):"grey"
        border.width: model.possible == VariantModel.SELECTED ?3:1
        onRectClicked: {
            repeater.model.setVariant(index);
        }
    }
}
