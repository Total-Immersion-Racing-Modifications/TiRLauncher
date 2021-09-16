import QtQuick 2.15
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
        contentItem: Text {
            text: parent.text
            font: parent.font
            opacity: enabled ? 1.0 : 0.3
            color: root.text_color
            verticalAlignment: Text.AlignVCenter
            leftPadding: parent.indicator.width + parent.spacing
        }
    }
}
