import QtQuick 2.0
import QtDataVisualization 1.2

Item {
    property alias model: proxy.itemModel
    Bars3D {
        id: graph
        width: parent.width
        height: parent.height

        Bar3DSeries {
            itemLabelFormat: "@colLabel in @rowLabel: repeating %d times"

            ItemModelBarDataProxy {
                id: proxy
                itemModel: barModel
                // Mapping model roles to bar series rows, columns, and values.
                rowRole: "file"
                columnRole: "word"
                valueRole: "count"
            }
        }

        scene.activeCamera: Camera3D {
            cameraPreset: Camera3D.CameraPresetIsometricRightHigh
        }
    }
}