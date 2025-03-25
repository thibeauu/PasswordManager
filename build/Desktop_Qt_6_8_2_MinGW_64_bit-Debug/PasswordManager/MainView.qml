import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    anchors.fill: parent

    ListView {
        anchors.fill: parent
        model: passwordVault

        delegate: Rectangle{
            width: parent.width
            height: 80
            border.color: "#007acc"
            border.width: 1
            radius: 6

            Column {
                anchors.fill: parent
                spacing: 4

                Text { text: "🔐 " + title }
                Text { text: "👤 " + username }
                Text { text: "🌐 " + url }
            }
        }

        spacing: 12
    }
}
