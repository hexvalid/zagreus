import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Extras 1.4
import QtQuick.Controls 2.15
Window {
    width: 1024
    height: 600
    visible: true

    Indicator{
        x: 0
        y: 0
        width: 103
        height: 298
        status: Router1.getStatus
        onConnect: Router1.connect()
        onDisconnect: Router1.disconnect()
        onReconnect: Router1.reconnect()
    }

    Indicator {
        x: 109
        y: 0
        width: 103
        height: 298
        status: Router2.getStatus
        onConnect: Router2.connect()
        onDisconnect: Router2.disconnect()
        onReconnect: Router2.reconnect()

    }

    Indicator {
        x: 218
        y: 0
        width: 103
        height: 298
        status: Router3.getStatus
        onConnect: Router3.connect()
        onDisconnect: Router3.disconnect()
        onReconnect: Router3.reconnect()

    }

    Indicator {
        x: 327
        y: 0
        width: 103
        height: 298
        status: Router4.getStatus
        onConnect: Router4.connect()
        onDisconnect: Router4.disconnect()
        onReconnect: Router4.reconnect()

    }

    Indicator {
        x: 436
        y: 0
        width: 103
        height: 298
        status: Router5.getStatus
        onConnect: Router5.connect()
        onDisconnect: Router5.disconnect()
        onReconnect: Router5.reconnect()
    }

    Rectangle {
        x: 0
        y: 457
        width: 1024
        height: 143
        color: "#282a36"

        RouterDeck {
            id: deck1
            x: 8
            y: 5
            no: 1
            conProgress: Router1.conProgress
            status:  Router1.getStatus
            pid: Router1.pid
            processIsRunning: Router1.processIsRunning
            peer: Router1.peer
            gateway: Router1.gateway
            local: Router1.local
            remote: Router1.remote
            netActing: Router1.netActing

        }
    }






    //    NOT_RUNNING = 0,
    //    STARTED = 1,
    //    CONNECTING_0 =2 ,
    //    CONNECTING_1 =3 ,
    //    CONNECTING_2 = 4,
    //    CONNECTING_3=5,
    //    CONNECTING_4=6,
    //    CONNECTING_5=7,
    //    CONNECTED=8,
    //    RECONNECTING=9,
    //    DISCONNECTING=10,
    //    ERROR=11,
}






