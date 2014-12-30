#include "serverinvadeUI.h"
#include "ui_serverinvade.h"

#include <QMessageBox>
#include <QTcpSocket>
#include <QDebug>
#include <QJsonDocument>

ServerInvadeUI::ServerInvadeUI(int port, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ServerInvade),
	server_{port, this}{

	ui->setupUi(this);

	if (!server_.isListening()) {
		ui->label->setText( tr("Unable to start the server: %1.").arg(server_.errorString()) );
		return;
	}

	ui->label->setText( tr("The server is running on port %1").arg(server_.serverPort()) );
}

ServerInvadeUI::~ServerInvadeUI(){
	delete ui;
}
