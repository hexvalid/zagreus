import QtQuick 2.0


Item {
    property int no: 0
    property int status: 0
    property int pid: 0
    property int peer: 0
    property string gateway
    property string local
    property string remote
    property double conProgress: 0
    property bool netActing: false

    property bool processIsRunning
    width: 150
    height: 130

    onStatusChanged: {
        switch(status){
        case 0:
            statusText.text="idle"
            statusText.color="#e6e6e6"
            break;
        case 1:
            statusText.text="connecting"
            statusText.color="#caa9fa"
            break;
        case 2:
            statusText.text="disconnecting"
            statusText.color="#f1fa8c"
            break;
        case 3:
            statusText.text="reconnecting"
            statusText.color="#e6e6e6"
            break;
        case 4:
            statusText.text="error"
            statusText.color="#ff5555"
            break;
        case 10:
            statusText.text="connected"
            statusText.color="#50fa7b"
            break;
        default:
            statusText.text="unknown"
            statusText.color="#ff6e67"
            break;
        }

    }


    Rectangle {
        x: 0
        y: 5
        width: 150
        height: 125
        color: "#282a36"
        border.color: "#8be9fd"
        border.width: 1
    }

    Rectangle {
        x: 8
        y: 0
        width: 52
        height: 10
        color: "#282a36"

        Text {
            x: 3
            y: 0
            width: 46
            height: 10
            color: "#e6e6e6"
            text: "router " + no
            font.pixelSize: 10
            font.family: "bitocrafull"
            textFormat: Text.PlainText
            font.kerning: false
            font.hintingPreference: Font.PreferNoHinting
            font.preferShaping: false
        }
    }


    Column {
        id: column
        x: 5
        y: 13
        width: 140
        height: 82
        spacing: 2

        Row {
            width: 140
            height: 10
            spacing: 5

            Text {
                width: 45
                height: 10
                color: "#bfbfbf"
                text: "status"
                font.pixelSize: 10
                horizontalAlignment: Text.AlignRight
                font.family: "bitocrafull"
                textFormat: Text.PlainText
                font.kerning: false
                font.hintingPreference: Font.PreferNoHinting
                font.preferShaping: false
            }

            Text {
                id: statusText
                width: 90
                height: 10
                color: "#e6e6e6"
                text: "ide"
                font.pixelSize: 10
                font.family: "bitocrafull"
                textFormat: Text.PlainText
                font.kerning: false
                font.hintingPreference: Font.PreferNoHinting
                font.preferShaping: false
            }
        }

        Row {
            width: 140
            height: 10
            spacing: 5
            Text {
                width: 45
                height: 10
                color: "#bfbfbf"
                text: "task"
                font.pixelSize: 10
                horizontalAlignment: Text.AlignRight
                font.family: "bitocrafull"
                textFormat: Text.PlainText
                font.kerning: false
                font.hintingPreference: Font.PreferNoHinting
                font.preferShaping: false
            }

            Text {
                width: 90
                height: 10
                color: "#e6e6e6"
                text: "idle"
                font.pixelSize: 10
                font.family: "bitocrafull"
                textFormat: Text.PlainText
                font.kerning: false
                font.hintingPreference: Font.PreferNoHinting
                font.preferShaping: false
            }
        }

        Row {
            width: 140
            height: 10
            spacing: 5
            Text {
                width: 45
                height: 10
                color: "#bfbfbf"
                text: "pid"
                font.pixelSize: 10
                horizontalAlignment: Text.AlignRight
                font.family: "bitocrafull"
                textFormat: Text.PlainText
                font.kerning: false
                font.hintingPreference: Font.PreferNoHinting
                font.preferShaping: false
            }

            Text {
                width: 90
                height: 10
                color: processIsRunning ? "#e6e6e6" : "#8d8d8d"
                text: processIsRunning ? pid : "n/a"
                font.pixelSize: 10
                font.family: "bitocrafull"
                textFormat: Text.PlainText
                font.kerning: false
                font.hintingPreference: Font.PreferNoHinting
                font.preferShaping: false
            }
        }

        Row {
            width: 140
            height: 10
            spacing: 5
            Text {
                width: 45
                height: 10
                color: "#bfbfbf"
                text: "peer"
                font.pixelSize: 10
                horizontalAlignment: Text.AlignRight
                font.family: "bitocrafull"
                textFormat: Text.PlainText
                font.kerning: false
                font.hintingPreference: Font.PreferNoHinting
                font.preferShaping: false
            }

            Text {
                width: 90
                height: 10
                color: status==10 ? "#e6e6e6" : "#898989"
                text: status==10 ? peer: "n/a"
                font.pixelSize: 10
                font.family: "bitocrafull"
                textFormat: Text.PlainText
                font.kerning: false
                font.hintingPreference: Font.PreferNoHinting
                font.preferShaping: false
            }
        }

        Row {
            width: 140
            height: 10
            spacing: 5
            Text {
                width: 45
                height: 10
                color: "#bfbfbf"
                text: "gateway"
                font.pixelSize: 10
                horizontalAlignment: Text.AlignRight
                font.family: "bitocrafull"
                textFormat: Text.PlainText
                font.kerning: false
                font.hintingPreference: Font.PreferNoHinting
                font.preferShaping: false
            }

            Text {
                width: 90
                height: 10
                color: status==10 ? "#e6e6e6" : "#898989"
                text: status==10 ? gateway: "n/a"
                font.pixelSize: 10
                font.family: "bitocrafull"
                textFormat: Text.PlainText
                font.kerning: false
                font.hintingPreference: Font.PreferNoHinting
                font.preferShaping: false
            }
        }

        Row {
            width: 140
            height: 10
            spacing: 5
            Text {
                width: 45
                height: 10
                color: "#bfbfbf"
                text: "local"
                font.pixelSize: 10
                horizontalAlignment: Text.AlignRight
                font.family: "bitocrafull"
                textFormat: Text.PlainText
                font.kerning: false
                font.hintingPreference: Font.PreferNoHinting
                font.preferShaping: false
            }

            Text {
                width: 90
                height: 10
                color: status==10 ? "#e6e6e6" : "#898989"
                text: status==10 ? local: "n/a"
                font.pixelSize: 10
                font.family: "bitocrafull"
                textFormat: Text.PlainText
                font.kerning: false
                font.hintingPreference: Font.PreferNoHinting
                font.preferShaping: false
            }
        }

        Row {
            width: 140
            height: 10
            spacing: 5
            Text {
                width: 45
                height: 10
                color: "#bfbfbf"
                text: "remote"
                font.pixelSize: 10
                horizontalAlignment: Text.AlignRight
                font.family: "bitocrafull"
                textFormat: Text.PlainText
                font.kerning: false
                font.hintingPreference: Font.PreferNoHinting
                font.preferShaping: false
            }

            Text {
                width: 90
                height: 10
                color: status==10 ? "#e6e6e6" : "#898989"
                text: status==10 ? remote: "n/a"
                font.pixelSize: 10
                font.family: "bitocrafull"
                textFormat: Text.PlainText
                font.kerning: false
                font.hintingPreference: Font.PreferNoHinting
                font.preferShaping: false
            }
        }


    }




    Rectangle {
        x: 1
        y: 99
        width: 148
        height: 1
        color: "#bfbfbf"
    }

    Text {
        x: 99
        y: 104
        width: 40
        height: 10
        color: "#bfbfbf"
        text: "net act"
        font.pixelSize: 10
        horizontalAlignment: Text.AlignLeft
        font.family: "bitocrafull"
        textFormat: Text.PlainText
        font.kerning: false
        font.hintingPreference: Font.PreferNoHinting
        font.preferShaping: false
    }

    Rectangle {
        x: 97
        y: 114
        width: 44
        height: 10
        color: netActing? "#ff5555"  : "#282a36"
        border.color: "#303745"
        border.width: 2
    }

    Text {
        x: 11
        y: 104
        width: 70
        height: 10
        color: "#bfbfbf"
        text: "con progress"
        font.pixelSize: 10
        horizontalAlignment: Text.AlignLeft
        font.family: "bitocrafull"
        textFormat: Text.PlainText
        font.kerning: false
        font.hintingPreference: Font.PreferNoHinting
        font.preferShaping: false
    }

    Rectangle {
        x: 9
        y: 114
        width: 74
        height: 10
        color: "#282a36"
        border.color: "#303745"
        border.width: 2

        Rectangle {
            id: conProgressBar
            x: 2
            y: 2
            width: (70*conProgress)
            height: 6
            color: status==10?"#50fa7b":"#caa9fa"
        }
    }
}



/*##^##
Designer {
    D{i:0;formeditorZoom:2}
}
##^##*/
