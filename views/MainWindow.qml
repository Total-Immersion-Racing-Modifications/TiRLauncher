import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle
{
    property var main_window_vm
    color: "gray"
    RatioList
    {
        screen_ratio_manager_vm: main_window_vm.screen_ratio_manager_vm
        anchors.fill: parent
    }
    Button
    {
        y: 200
        text: qsTr("Start")
        onClicked: main_window_vm.startGameRequested()
    }
}
