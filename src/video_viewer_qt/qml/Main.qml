import QtQuick
import QtQuick.Window

Window {
    id: root
    visible: true
    width: 1280
    height: 720
    title: "video_ros2 viewer"
    color: "#0b0f14"
    property bool configVisible: false
    property string lastToastText: ""

    function enqueueToast(message) {
        if (!message || message.length === 0) {
            return
        }
        toastModel.append({
            text: message,
            expiresAt: Date.now() + 3000
        })
        toastCleanupTimer.restart()
    }

    function openConfig() {
        configVisible = true
    }

    function closeConfig() {
        configVisible = false
        keyCatcher.forceActiveFocus()
    }

    function blurInput() {
        robotIdField.focus = false
        keyCatcher.forceActiveFocus()
    }

    function connectMqtt() {
        viewer.requestMqttConnect(robotIdField.text.trim())
    }

    function disconnectMqtt() {
        viewer.requestMqttDisconnect()
    }

    ListModel {
        id: toastModel
    }

    Timer {
        id: toastCleanupTimer
        interval: 250
        repeat: true
        running: false
        onTriggered: {
            const now = Date.now()
            for (let i = toastModel.count - 1; i >= 0; --i) {
                if (toastModel.get(i).expiresAt <= now) {
                    toastModel.remove(i)
                }
            }
            if (toastModel.count === 0) {
                toastCleanupTimer.stop()
            }
        }
    }

    Connections {
        target: viewer
        function onStateChanged() {
            if (viewer.loginStatusText !== root.lastToastText) {
                root.lastToastText = viewer.loginStatusText
                root.enqueueToast(viewer.loginStatusText)
            }
        }
    }

    Item {
        id: keyCatcher
        anchors.fill: parent
        focus: true
        Keys.priority: Keys.BeforeItem
        Keys.onPressed: function(event) {
            if (event.key === Qt.Key_B) {
                if (configVisible) {
                    closeConfig()
                } else {
                    openConfig()
                }
                event.accepted = true
                return
            }
        }
    }

    Component.onCompleted: {
        keyCatcher.forceActiveFocus()
        root.lastToastText = viewer.loginStatusText
    }

    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#10141b" }
            GradientStop { position: 1.0; color: "#05070a" }
        }
    }

    Item {
        anchors.fill: parent
        anchors.margins: 24
        visible: !configVisible

        Rectangle {
            anchors.fill: parent
            color: "#11161f"
            radius: 18
            border.color: "#273140"
            border.width: 1

            Image {
                id: frameView
                anchors.fill: parent
                anchors.margins: 18
                visible: viewer.hasFrame
                fillMode: Image.PreserveAspectFit
                cache: false
                smooth: true
                source: viewer.hasFrame ? ("image://viewer/latest?rev=" + viewer.frameRevision) : ""
            }

            Text {
                anchors.centerIn: parent
                visible: !viewer.hasFrame
                text: viewer.statusText
                color: "#9fb2c7"
                font.pixelSize: 24
            }
        }

        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            height: 54
            radius: 14
            color: "#1a2230"
            border.color: "#2d3a4d"
            border.width: 1

            Text {
                anchors.fill: parent
                anchors.leftMargin: 20
                anchors.rightMargin: 20
                verticalAlignment: Text.AlignVCenter
                text: viewer.statusText
                color: "#d8e4f2"
                font.pixelSize: 16
                elide: Text.ElideRight
            }
        }

        Rectangle {
            anchors.right: parent.right
            anchors.top: parent.top
            width: 220
            height: 40
            radius: 12
            color: "#1b2432"
            border.color: "#2d3a4d"
            border.width: 1

            Text {
                anchors.centerIn: parent
                text: "Press B to configure"
                color: "#8fa3ba"
                font.pixelSize: 14
            }
        }
    }

    Item {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 18
        width: Math.min(parent.width * 0.76, 760)

        Column {
            width: parent.width
            spacing: 8

                Repeater {
                    model: toastModel

                    delegate: Rectangle {
                        property string lowered: String(model.text).toLowerCase()
                        property color accent: lowered.indexOf("disconnected") !== -1
                                               ? "#ef4444"
                                               : (lowered.indexOf("error") !== -1 || lowered.indexOf("failed") !== -1
                                                  ? "#ef4444"
                                                  : (lowered.indexOf("connected") !== -1
                                                     ? "#22c55e"
                                                     : "#60a5fa"))
                        width: parent.width
                        height: Math.max(44, messageText.implicitHeight + 20)
                        radius: 14
                        color: "#0f172a"
                        border.color: accent
                        border.width: 1
                        opacity: 0.98

                        Text {
                            id: messageText
                            anchors.fill: parent
                            anchors.leftMargin: 18
                            anchors.rightMargin: 18
                            anchors.topMargin: 10
                            anchors.bottomMargin: 10
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            text: model.text
                            color: lowered.indexOf("disconnected") !== -1 || lowered.indexOf("error") !== -1 || lowered.indexOf("failed") !== -1
                                 ? "#fee2e2"
                                 : (lowered.indexOf("connected") !== -1 ? "#dcfce7" : "#dbeafe")
                            font.pixelSize: 16
                            wrapMode: Text.WordWrap
                        }
                    }
                }
        }
    }

    Item {
        anchors.fill: parent
        visible: configVisible

        Rectangle {
            anchors.fill: parent
            color: "#000000"
            opacity: 0.58
        }

        MouseArea {
            anchors.fill: parent
            onClicked: blurInput()
        }

        Rectangle {
            id: configCard
            width: Math.min(parent.width - 72, 620)
            height: 320
            radius: 20
            color: "#11161f"
            border.color: "#334155"
            border.width: 1
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            Column {
                anchors.fill: parent
                anchors.margins: 28
                spacing: 18

                Text {
                    text: "连接机器人"
                    color: "#f1f5f9"
                    font.pixelSize: 30
                    font.bold: true
                }

                Text {
                    text: "输入 client_id，然后点击登录。按 B 切换配置页。"
                    color: "#94a3b8"
                    font.pixelSize: 16
                    wrapMode: Text.WordWrap
                }

                Rectangle {
                    width: parent.width
                    height: 58
                    radius: 14
                    color: "#0b1220"
                    border.color: robotIdField.activeFocus ? "#60a5fa" : "#334155"
                    border.width: 1

                    MouseArea {
                        anchors.fill: parent
                        onClicked: robotIdField.forceActiveFocus()
                    }

                    TextInput {
                        id: robotIdField
                        anchors.fill: parent
                        anchors.leftMargin: 16
                        anchors.rightMargin: 16
                        verticalAlignment: TextInput.AlignVCenter
                        color: "#e2e8f0"
                        font.pixelSize: 18
                        selectByMouse: true
                        inputMethodHints: Qt.ImhNoPredictiveText
                        onAccepted: connectMqtt()
                        onActiveFocusChanged: {
                            if (!activeFocus) {
                                keyCatcher.forceActiveFocus()
                            }
                        }
                        Text {
                            anchors.left: parent.left
                            anchors.verticalCenter: parent.verticalCenter
                            visible: robotIdField.text.length === 0 && !robotIdField.activeFocus
                            text: "请输入 client_id"
                            color: "#64748b"
                            font.pixelSize: 18
                        }
                    }
                }

                Row {
                    spacing: 12

                    Rectangle {
                        width: 132
                        height: 46
                        radius: 12
                        color: viewer.loginPending ? "#334155" : "#2563eb"
                        opacity: viewer.loginPending ? 0.7 : 1.0
                        border.color: "#1d4ed8"
                        border.width: 1

                        Text {
                            anchors.centerIn: parent
                            text: viewer.loginPending ? "登录中..." : "登录"
                            color: "#ffffff"
                            font.pixelSize: 16
                            font.bold: true
                        }

                        MouseArea {
                            anchors.fill: parent
                            enabled: !viewer.loginPending
                            onClicked: {
                                connectMqtt()
                                blurInput()
                            }
                        }
                    }

                    Rectangle {
                        width: 132
                        height: 46
                        radius: 12
                        color: viewer.loginPending ? "#334155" : "#475569"
                        opacity: viewer.loginPending ? 0.7 : 1.0
                        border.color: "#64748b"
                        border.width: 1

                        Text {
                            anchors.centerIn: parent
                            text: viewer.loginPending ? "退出中..." : "退出"
                            color: "#e2e8f0"
                            font.pixelSize: 16
                            font.bold: true
                        }

                        MouseArea {
                            anchors.fill: parent
                            enabled: !viewer.loginPending
                            onClicked: {
                                disconnectMqtt()
                                blurInput()
                            }
                        }
                    }
                }
            }
        }
    }
}
