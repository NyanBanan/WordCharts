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
    ColumnLayout {
        anchors.fill: parent
        WordsGraph {
            id: graph
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.row: 0
            model: barModel
        }
        RowLayout {
            Layout.row: 1
            ColumnLayout {
                Button {
                    id: start
                    Layout.preferredWidth: 100
                    Layout.preferredHeight: 40
                    onClicked: {
                        wordParser.startParseDocument(filePath.text)
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
                    Layout.preferredHeight: 40
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
            ColumnLayout {
                ProgressBar {
                    id: progress
                    Layout.fillWidth: true
                    Layout.preferredHeight: 30
                    Layout.margins: 5
                }
                TextField {
                    id: filePath
                    placeholderText: qsTr("Enter path")
                    text: fileDialog.currentFile
                    Layout.fillWidth: true
                    Layout.preferredHeight: 50
                    Layout.margins: 5
                    background: Rectangle {
                        color: "#ffffff"
                        border.color: filePath.enabled ? "#21be2b" : "transparent"
                    }
                }
            }
        }
    }
    FileDialog {
        id: fileDialog
        currentFolder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
    }

    WordFileCountModel {
        id: barModel
        Component.onCompleted: {
            progress.value = barModel.progress
        }
    }

    FileWordParser {
        id: wordParser
        model: barModel

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