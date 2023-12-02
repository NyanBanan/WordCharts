import QtQuick 2.0
import QtDataVisualization 1.2

import WordChartsQml

Item {
    width: 640
    height: 480
    property alias proxy: proxy
    property alias scene: graph.scene
    Bars3D {
        id: graph
        width: parent.width
        height: parent.height

        Bar3DSeries {
            itemLabelFormat: "@colLabel, @rowLabel: @valueLabel"

            ItemModelBarDataProxy {
                id: proxy
                itemModel: barModel
                // Mapping model roles to bar series rows, columns, and values.
                rowRole: "word"
                columnRole: "doc"
                valueRole: "count"
            }
        }

        scene.activeCamera: Camera3D {
            cameraPreset: Camera3D.CameraPresetIsometricRightHigh
        }
    }

    BarChartModel{
        id: barModel
    }
}