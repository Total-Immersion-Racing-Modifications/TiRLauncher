import QtQuick 2.15
import QtQuick.Dialogs 1.3

FileDialog
{
    title: qsTr("Please choose a file")
    selectFolder: true
    folder: shortcuts.home
}
