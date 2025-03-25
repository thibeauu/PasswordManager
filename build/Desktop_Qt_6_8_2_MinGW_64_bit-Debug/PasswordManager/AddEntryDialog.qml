import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    id: addEntryDialog
    title: "Add New Password"
    modal: true
    standardButtons: Dialog.Ok | Dialog.Cancel

    contentItem: ColumnLayout {
        spacing: 10
        width: parent.width * 0.8

        TextField {
            id: titleField
            placeholderText: "Title (e.g. Gmail)"
        }
        TextField {
            id: usernameField
            placeholderText: "Username"
        }
        TextField {
            id: passwordField
            placeholderText: "Password"
            echoMode: TextInput.Password
        }
        TextField {
            id: urlField
            placeholderText: "URL (optional)"
        }
    }

    onAccepted: {
        if (titleField.text !== "" && passwordField.text !== "") {
            passwordVault.addEntry(
                titleField.text,
                usernameField.text,
                passwordField.text,
                urlField.text
            )
        }
        titleField.text = ""
        usernameField.text = ""
        passwordField.text = ""
        urlField.text = ""
    }

    onRejected: {
        titleField.text = ""
        usernameField.text = ""
        passwordField.text = ""
        urlField.text = ""
    }
}
