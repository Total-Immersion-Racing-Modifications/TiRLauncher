import QtQuick 2.0

Rectangle
{
    property var main_window_vm
    color: "gray"
    RatioList
    {
        screen_ratio_manager_vm: main_window_vm.screen_ratio_manager_vm
        anchors.fill: parent
    }
}
