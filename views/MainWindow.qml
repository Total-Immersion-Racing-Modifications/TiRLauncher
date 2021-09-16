import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle
{
    id: root

    property var main_window_vm
    readonly property int button_margin: 50
    readonly property int ratio_list_margin: 10
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

        Item
        {
            id: ratio_list
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.leftMargin: root.ratio_list_margin

            Text
            {
                id: ratio_list_label
                anchors.top: parent.top
                anchors.left: parent.left
                text: qsTr("Screen ratio")
                color: text_color
            }

            RatioList
            {
                anchors.top: ratio_list_label.bottom
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                screen_ratio_manager_vm: main_window_vm.screen_ratio_manager_vm
                text_color: root.text_color
            }
        }

        Button
        {
            anchors.margins: root.button_margin
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Start")
            onClicked: main_window_vm.startGameRequested()
        }
    }
}
