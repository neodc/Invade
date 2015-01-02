#include "invadeconnection.h"
#include "ui_invadeconnection.h"

InvadeConnection::InvadeConnection(QWidget * parent) :
	QDialog(parent),
	ui(new Ui::InvadeConnection) {
	ui->setupUi(this);

	ui->host->setText("127.0.0.1");
	ui->name->setText("Nickname");

	connect( ui->server, &QCheckBox::stateChanged, this,  &InvadeConnection::showHost);
}

InvadeConnection::~InvadeConnection() {
	delete ui;
}

bool InvadeConnection::server() {
	return ui->server->isChecked();
}

QString InvadeConnection::host() {
	return ui->host->text();
}

QString InvadeConnection::name() {
	return ui->name->text();
}

int InvadeConnection::port() {
	return ui->port->value();
}

void InvadeConnection::showHost() {
	ui->host->setEnabled( !ui->server->isChecked() );
	ui->name->setEnabled( !ui->server->isChecked() );
}
