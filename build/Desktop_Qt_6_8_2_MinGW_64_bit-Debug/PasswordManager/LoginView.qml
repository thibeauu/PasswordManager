import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    anchors.fill: parent

    Rectangle {
        width: 280
        height: 180
        color: "#ffffff"
        radius: 12
        border.color: "#007acc"
        border.width: 2
        anchors.centerIn: parent

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 16
            spacing: 10

            Label {
                text: "Enter your Master Password to Log In"
                font.bold: true
                font.pointSize: 14
                color: "#007acc"
                horizontalAlignment: Text.AlignHCenter
                Layout.alignment: Qt.AlignHCenter
            }

            TextField {
                id: loginField
                echoMode: TextInput.Password
                placeholderText: "Password"
                Layout.fillWidth: true
                background: Rectangle {
                    color: "#f0faff"
                    border.color: "#007acc"
                    radius: 6
                }
            }

            Button {
                text: "Log In"
                Layout.alignment: Qt.AlignHCenter
                background: Rectangle {
                    color: "#007acc"
                    radius: 6
                }
                contentItem: Text {
                    text: "Log In"
                    color: "white"
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                onClicked: {
                    if (passwordManager.verifyPassword(loginField.text)) {
                        Qt.callLater(() => viewLoader.source = "MainView.qml")
                    } else {
                        loginField.text = ""
                        loginField.placeholderText = "Incorrect password"
                    }
                }
            }
        }
    }
}
