import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3


ApplicationWindow {
	id: mainWindow
	title: "Mounts"

	width: 320
	height: 240

	visible: true

	Action {
		id: quitApplicationAction
		text: qsTr("&Quit")
		tooltip: qsTr("Quit the application")
		shortcut: StandardKey.Quit
		onTriggered: Qt.quit();
	}

	Action {
		id: clearLogAction
		text: qsTr("&Clear")
		tooltip: qsTr("Clear the log contents")
		shortcut: StandardKey.Backspace
		onTriggered: testModel.clear();
	}

	menuBar: MenuBar {
		Menu {
			title: qsTr("&File");
			MenuItem { action: quitApplicationAction }
		}

		Menu {
			title: qsTr("&Edit");
			MenuItem { action: clearLogAction }
		}
	}

	statusBar: StatusBar {
		RowLayout {
			anchors.fill: parent
			Label { text: qsTr("Please, insert (remove) storage device...") }
		}
	}

	TableView {
		id: tableView
		anchors.fill:parent
		model: mountsModel // see main.cpp

		backgroundVisible: false
		headerVisible: true

		TableViewColumn {
			role: "path"
			title: "Path"
			width: 200
		}
		TableViewColumn {
			role: "device"
			title: "Device"
			width: 100
		}

	}
}
