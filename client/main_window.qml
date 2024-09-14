import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "Simple QML Window"

    // Main layout for the window
    Rectangle {
        anchors.fill: parent
        color: "#f0f0f0" // Light gray background

        // A button in the center of the window
        Button {
            text: "Click Me"
            anchors.centerIn: parent
            onClicked: {
                console.log("Button clicked!")
            }
        }
    }
}
