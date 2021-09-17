import QtQuick 2.15
import QtQuick.Dialogs 1.3

FileDialog
{
    title: qsTr("Please choose a folder")
    selectFolder: true
    folder: shortcuts.home
}
