import QtQuick 2.15

Rectangle
{
    color: "black"
    height: banner_image.height
    Image
    {
        id: banner_image
        anchors.horizontalCenter: parent.horizontalCenter
        source: "qrc:/images/banner.png"
    }
}
