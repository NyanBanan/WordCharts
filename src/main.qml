import QtQuick
import QtQuick.Controls
import QtDataVisualization

ApplicationWindow {
    id: root
    visible: true
    width: 500
    height: 500

    Component.onCompleted:{
        root.width = Screen.desktopAvailableWidth / 4
        root.height= Screen.desktopAvailableWidth / 4
        root.x = Screen.desktopAvailableWidth / 2 - width / 2
        root.y = Screen.desktopAvailableHeight / 2 - height / 2
    }

    background: Rectangle {
        gradient: Gradient {
            GradientStop {
                position: 0; color: "#10b65f"
            }
            GradientStop {
                position: 1; color: "#168c16"
            }
        }
    }

    WordsGraph{
    }
}