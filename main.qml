import QtQuick 2.12
import QtQuick.Window 2.12

import launcher.vms 1.0

Window
{
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Total Immersion Racing Launcher")

    MainWindow
    {
        main_window_vm: MainWindowVM
        {

        }

        anchors.fill: parent
    }
}
