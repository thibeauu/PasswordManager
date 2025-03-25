import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Password manager")

    Loader {
        id: viewLoader
        anchors.fill: parent
        source: passwordManager.hasPassword() ? "LoginView.qml" : "SetupView.qml"
    }
}
