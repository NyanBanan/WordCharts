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

    Connections {
        target: wordParser

        function onErrorOccured(errorMessage) {
            console.log(errorMessage)
            messageText.text = errorMessage
            message.open()
        }

        function onStateChanged(state){
            console.log(state)
            switch (state){
                case FileWordParser.WORK:{
                    console.log(state)
                    grid.state = "WORKING"
                    break;
                }
                case FileWordParser.PAUSE:{
                    console.log(state)
                    grid.state = "PAUSED"
                    break;
                }
                case FileWordParser.STOP:{
                    console.log(state)
                    grid.state = "STOPPED"
                    break;
                }
            }
        }
    }

    FileWordParser {
        id: wordParser
        model: barModel
        Component.onCompleted: {
            progress.value = Qt.binding(function () {
                return wordParser.progress
            })
        }
    }

    ColumnLayout {
        anchors.fill: parent
        WordsGraph {
            id: graph
            Layout.row: 0
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: barModel
        }
        GridLayout {
            id: grid
            rows: 2
            columns: 2
            Layout.row: 1
            state: "STOPPED"
            states:[
                State {
                    name: "STOPPED"
                    PropertyChanges { target: upperButtonText; text: "Начать"}
                    PropertyChanges { target: upperButton; onClicked: { wordParser.startParseDocument(filePath.text) }}

                    PropertyChanges { target: lowerButtonText; text: "Открыть"}
                    PropertyChanges { target: lowerButton; onClicked: { fileDialog.open() }}
                },
                State {
                    name: "WORKING"
                    PropertyChanges { target: upperButtonText; text: "Пауза"}
                    PropertyChanges { target: upperButton; onClicked: { wordParser.state = FileWordParser.PAUSE }}

                    PropertyChanges { target: lowerButtonText; text: "Отмена"}
                    PropertyChanges { target: lowerButton; onClicked: { wordParser.state = FileWordParser.STOP; barModel.resetData() }}
                },
                State {
                    name: "PAUSED"
                    PropertyChanges { target: upperButtonText; text: "Продолжить"}
                    PropertyChanges { target: upperButton; onClicked: { wordParser.state = FileWordParser.WORK }}

                    PropertyChanges { target: lowerButtonText; text: "Отмена"}
                    PropertyChanges { target: lowerButton; onClicked: { wordParser.state = FileWordParser.STOP; barModel.resetData()}}
                }
            ]

            Button {
                id: upperButton
                Layout.row: 0
                Layout.column: 1
                Layout.preferredWidth: 100
                Layout.preferredHeight: 40
                Layout.margins: 5
                Text {
                    id: upperButtonText
                    width: parent.width
                    height: parent.height
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
            Button {
                id: lowerButton
                Layout.row: 1
                Layout.column: 1
                Layout.preferredWidth: 100
                Layout.preferredHeight: 40
                Layout.margins: 5
                Text {
                    id: lowerButtonText
                    width: parent.width
                    height: parent.height
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

            ProgressBar {
                id: progress
                Layout.row: 0
                Layout.column: 0
                Layout.fillWidth: true
                Layout.preferredHeight: 30
                Layout.margins: 5
            }
            Rectangle {
                Layout.row: 1
                Layout.column: 0
                Layout.fillWidth: true
                Layout.preferredHeight: 50
                Layout.margins: 5

                color: "#ffffff"
                border.color: filePath.enabled ? "#21be2b" : "transparent"

                Text {
                    id: filePath
                    anchors.fill: parent
                    text: fileDialog.selectedFile == "" ? "Выберите файл" : fileDialog.currentFile
                    elide: Text.ElideLeft
                    wrapMode: Text.WrapAnywhere
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }
    }
    FileDialog {
        id: fileDialog
        currentFolder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        nameFilters: ["Text files (*.txt)"]
    }

    WordFileCountModel {
        id: barModel
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