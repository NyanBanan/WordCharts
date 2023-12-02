import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import QtDataVisualization

import WordChartsQml

ApplicationWindow {
    id: root
    visible: true
    minimumWidth: 300
    minimumHeight: 400
    Component.onCompleted: {
        root.width = Screen.desktopAvailableWidth / 4
        root.height = Screen.desktopAvailableWidth / 4
        root.x = Screen.desktopAvailableWidth / 2 - width / 2
        root.y = Screen.desktopAvailableHeight / 2 - height / 2

        // graph.width = Qt.binding(function () {
        //     return root.width
        // })
        // graph.height = Qt.binding(function () {
        //     return root.height
        // })
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
    GridLayout {
        anchors.fill: parent
        columns: 2
        rows: 2
        flow: width > height ? GridLayout.LeftToRight : GridLayout.TopToBottom
        WordsGraph {
            id: graph
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: 500
            Layout.preferredHeight: 500
            Layout.row: 0
            Layout.column: 0
            model: barModel
        }
        ColumnLayout {
            Layout.row: 0
            Layout.column: 1
            Button {
                id: start
                Layout.preferredWidth: 100
                Layout.preferredHeight: 100
                onClicked: {
                    wordParser.startParseDocument(fileDialog.currentFile)
                }
                Text {
                    text: "Start"
                    width: parent.width
                    height: parent.height
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
            Button {
                id: open
                Layout.preferredWidth: 100
                Layout.preferredHeight: 100
                onClicked: {
                    fileDialog.open()
                }
                Text {
                    text: "Open"
                    width: parent.width
                    height: parent.height
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }

        ProgressBar {
            id: progress
            Layout.row: 1
            Layout.column: 0
            Layout.fillWidth: true
            Layout.preferredHeight: 100
            Layout.margins: 5
        }
    }
    FileDialog {
        id: fileDialog
        currentFolder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
    }

    WordFileCountModel {
        id: barModel
    }

    FileWordParser {
        id: wordParser
        model: barModel
        Component.onCompleted :{
            progress.value = Qt.binding(function (){return barModel.progress})
        }
    }

    Connections {
        target: wordParser
        function onErrorOccured(errorMessage) {
            console.log(errorMessage)
            messageText.text = errorMessage
            message.open()
        }
    }

    Dialog {
        id: message
        width: parent.width / 2
        height: parent.height / 2
        anchors.centerIn: parent
        modal: true
        title: qsTr("Error")
        Text {
            id: messageText
            width: parent.width
            height: parent.height
            wrapMode: Text.Wrap
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        standardButtons: Dialog.Ok
    }
}