import QtQuick 2.0
import QtQuick.Extras 1.4
import QtQuick.Controls 2.15

Item {
    property int status
    property string ip

    signal connect
    signal disconnect
    signal reconnect
    onStatusChanged: {
        if (status==0)
            led1.color = "#000000"
        else if (status==1)
            led1.color = "#4e6d8f"
        else if (status==2)
            led1.color = "#639bd7"
        else if (status==3)
            led1.color = "#4b84c3"
        else if (status==4)
            led1.color = "#2e6cb0"
        else if (status==4)
            led1.color = "#1f5fa5"
        else if (status==5)
            led1.color = "#1f7da5"
        else if (status==6)
            led1.color = "#1fa59a"
        else if (status==7)
            led1.color = "#1fa577"
        else if (status==8)
            led1.color = "#18b221"
        else if (status==9)
            led1.color = "#bfc222"
        else if (status==10)
            led1.color = "#5c159e"
        else if (status==11)
            led1.color = "#dc1628"
    }
    Text {
        id: text1
        x: 0
        y: 283
        text: status
        font.pixelSize: 12
    }
    Button {
        x: 0
        y: 46
        text: "Connect"
        onClicked: connect()
    }
    Button {
        x: 0
        y: 138
        text: "Disconnect"
        onClicked: disconnect()
    }

    Button {
        x: 0
        y: 0
        text: "Init"
    }

    Button {
        x: 0
        y: 184
        text: "Deinit"
    }

    Button {
        x: 0
        y: 92
        text: "Reconnect"
        onClicked: reconnect()
    }

    StatusIndicator {
        id:led1
        width: 50
        height: 50
        x:25
        y:230
        active: true
    }

    Text {
        id: text2
        x: 0
        y: 313
        width: 100
        height: 13
        text: ip
        font.pixelSize: 15
        horizontalAlignment: Text.AlignHCenter
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
