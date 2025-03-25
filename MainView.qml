import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    anchors.fill: parent

    Rectangle {
        id: blurLayer
        anchors.fill: parent
        visible: addEntryDialog.visible
        color: "#000000"
        opacity: 0.3
        z: 9
    }

    ListView {
        id: passwordList
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            bottom: addButton.top
            bottomMargin: 10
        }
        model: passwordVault
        delegate: Item {
            width: parent.width
            height: 100

            Column {
                anchors.fill: parent
                anchors.margins: 12
                spacing: 6

                Text {
                    text: "🔐 " + title
                    font.bold: true
                    font.pointSize: 14
                }

                Text {
                    text: "👤 " + username
                    color: "#444"
                }

                Text {
                    text: "🌐 " + url
                    color: "#007acc"
                }
            }

            Rectangle {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                height: 1
                color: "#007acc"
            }
        }

        spacing: 12
        z: 1
    }

    Button {
        id: addButton
        text: "Add Password"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        z: 1

        background: Rectangle {
            color: "#007acc"
            radius: 6
        }

        contentItem: Text {
            text: addButton.text
            color: "white"
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        onClicked: addEntryDialog.open()
    }

    Dialog {
        id: addEntryDialog
        modal: true
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        width: 400
        height: 300
        title: ""
        z: 10

        background: Rectangle {
            color: "#f5f5f5"
            radius: 12
            border.color: "#007acc"
            border.width: 2
        }

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 20
            spacing: 16

            Text {
                text: "Add New Password"
                font.bold: true
                font.pointSize: 16
                color: "#222"
                horizontalAlignment: Text.AlignHCenter
                Layout.alignment: Qt.AlignHCenter
            }

            TextField {
                id: titleField
                placeholderText: "Title"
                Layout.fillWidth: true
                background: Rectangle {
                    color: "#ffffff"
                    border.color: "#cccccc"
                    radius: 6
                }
            }

            TextField {
                id: usernameField
                placeholderText: "Username"
                Layout.fillWidth: true
                background: Rectangle {
                    color: "#ffffff"
                    border.color: "#cccccc"
                    radius: 6
                }
            }

            TextField {
                id: passwordField
                placeholderText: "Password"
                echoMode: TextInput.Password
                Layout.fillWidth: true
                background: Rectangle {
                    color: "#ffffff"
                    border.color: "#cccccc"
                    radius: 6
                }
            }

            TextField {
                id: urlField
                placeholderText: "URL"
                Layout.fillWidth: true
                background: Rectangle {
                    color: "#ffffff"
                    border.color: "#cccccc"
                    radius: 6
                }
            }

            RowLayout {
                Layout.alignment: Qt.AlignRight
                spacing: 12

                Button {
                    text: "OK"
                    background: Rectangle {
                        color: "#007acc"
                        radius: 6
                    }
                    contentItem: Text {
                        text: "OK"
                        color: "white"
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    onClicked: {
                        passwordVault.addEntry(
                            titleField.text,
                            usernameField.text,
                            passwordField.text,
                            urlField.text
                        );

                        titleField.text = ""
                        usernameField.text = ""
                        passwordField.text = ""
                        urlField.text = ""

                        addEntryDialog.close()
                    }
                }

                Button {
                    text: "Cancel"
                    onClicked: addEntryDialog.close()
                }
            }
        }
    }
}
