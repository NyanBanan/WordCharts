import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtDataVisualization

import Qt.labs.platform

import WordChartsQml

ApplicationWindow {
    id: root
    visible: true
    minimumWidth: 300
    minimumHeight: 400

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
        target: wordFrequencyAnalyst

        function onErrorOccured(errorMessage) {
            console.log(errorMessage)
            message.text = errorMessage
            message.open()
        }

        function onStateChanged(state){
            switch (state){
                case WordFrequencyAnalyst.WORK:{
                    grid.state = "WORKING"
                    break;
                }
                case WordFrequencyAnalyst.PAUSE:{
                    grid.state = "PAUSED"
                    break;
                }
                case WordFrequencyAnalyst.STOP:{
                    grid.state = "STOPPED"
                    break;
                }
            }
        }
    }

    WordFrequencyAnalyst {
        id: wordFrequencyAnalyst
        model: barModel
        Component.onCompleted: {
            progress.value = Qt.binding(function () {
                return wordFrequencyAnalyst.progress
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
                    PropertyChanges { target: upperButton; onClicked: { wordFrequencyAnalyst.startParseDocument(filePath.text) }}

                    PropertyChanges { target: lowerButtonText; text: "Открыть"}
                    PropertyChanges { target: lowerButton; onClicked: { fileDialog.open() }}
                },
                State {
                    name: "WORKING"
                    PropertyChanges { target: upperButtonText; text: "Пауза"}
                    PropertyChanges { target: upperButton; onClicked: { wordFrequencyAnalyst.state = WordFrequencyAnalyst.PAUSE }}

                    PropertyChanges { target: lowerButton; visible: false}
                },
                State {
                    name: "PAUSED"
                    PropertyChanges { target: upperButtonText; text: "Продолжить"}
                    PropertyChanges { target: upperButton; onClicked: { wordFrequencyAnalyst.state = WordFrequencyAnalyst.WORK }}

                    PropertyChanges { target: lowerButtonText; text: "Отмена"}
                    PropertyChanges { target: lowerButton; onClicked: { wordFrequencyAnalyst.state = WordFrequencyAnalyst.STOP; barModel.resetData() }}
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
                    text: "Выберите файл"
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
        nameFilters: ["Text files (*.txt)"]
        onAccepted: filePath.text = currentFile //selectedFile doesnt exist in Qt.labs.platform
    }

    WordFileCountModel {
        id: barModel
    }

    MessageDialog {
        id: message
        buttons: MessageDialog.Ok
        modality: Qt.ApplicationModal
        title: qsTr("Error")
    }
}
