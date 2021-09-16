import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle
{
    id: root

    property var main_window_vm
    readonly property int elements_margins: 50
    readonly property color text_color: "white"
    color: "black"
    Banner
    {
        id: banner
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
    }
    Item
    {
        anchors.top: banner.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        RatioList
        {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            screen_ratio_manager_vm: main_window_vm.screen_ratio_manager_vm
            text_color: root.text_color
        }
        Button
        {
            anchors.margins: root.elements_margins
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Start")
            onClicked: main_window_vm.startGameRequested()
        }
    }
}
