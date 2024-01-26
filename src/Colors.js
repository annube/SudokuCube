
function toColor(cubeModelColor)
{
    switch(cubeModelColor)
    {
    case CubeModel.CONFLICT:
        return Qt.color("crimson");
    case CubeModel.FREE:
        return Qt.color("grey");
    case CubeModel.BLACK:
        return Qt.color("black");
    case CubeModel.BLACK:
        return Qt.color("black");
    case CubeModel.WHITE:
        return Qt.color("white");
    case CubeModel.YELLOW:
        return Qt.color("yellow");
    case CubeModel.ORANGE:
        return Qt.color("orange");
    case CubeModel.LIGHT_BLUE:
        return Qt.color("lightblue");
    case CubeModel.BLUE:
        return Qt.color("blue");
    case CubeModel.PURPLE:
        return Qt.color("purple");
    case CubeModel.RED:
        return Qt.color("red");
    case CubeModel.GREEN:
        return Qt.color("green");
    default:
        return "transparent";
    }
}
