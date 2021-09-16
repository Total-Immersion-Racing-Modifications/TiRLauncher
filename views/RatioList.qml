import QtQuick 2.0
import QtQuick.Controls 2.15

ListView
{
    id: root

    property var screen_ratio_manager_vm
    property color text_color: "black"

    model: screen_ratio_manager_vm
    interactive: false
    delegate: RadioButton
    {
        text: r_ratio_type_name
        onClicked: screen_ratio_manager_vm.current_ratio = r_ratio_type
        //contentItem.color: root.text_color
    }
}
