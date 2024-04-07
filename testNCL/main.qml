import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 500
    height: 400

    Rectangle {
        width: 100
        height: 40
        color: "red"

        MouseArea {
            anchors.fill: parent
            onClicked: {
                CTRL.addSV("D","Nguyễn")
                listStudent.model = CTRL.getLength()
            }
        }
    }

    ListView {
        id: listStudent
        width: 350
        height: 390
        clip: true
        spacing: 10
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: title.bottom
            topMargin: 30
        }

        model: CTRL.getLength()

        delegate: Rectangle {
            width: 350
            height: 90
            radius: 20
            border.color: "black"

            MouseArea {
                anchors.fill: parent
                onPressed: parent.scale = 0.95
                onReleased: parent.scale = 1
            }

            Column {
                Text {
                    text: '<b>Name:</b> ' + CTRL.getData(index).name
                    font.pixelSize: 15
                }
                Text {
                    text: '<b>Lastname:</b> ' + CTRL.getData(index).lastname
                    font.pixelSize: 15
                }
                anchors {
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                    leftMargin: 30
                }
            }
        }
    }
}
