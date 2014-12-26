#include "serverinvade.h"
#include "ui_serverinvade.h"

#include <QMessageBox>
#include <QTcpSocket>
#include <QDebug>
#include <QJsonDocument>

ServerInvade::ServerInvade(Invade *model, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ServerInvade),
	model{model},
	blockSize{0}{

	ui->setupUi(this);

	tcpServer = new QTcpServer(this);
	if (!tcpServer->listen(QHostAddress::Any, 5423)) {
		QMessageBox::critical(this, tr("Fortune Server"),
							  tr("Unable to start the server: %1.").arg(tcpServer->errorString()));
		close();
		return;
	}

	ui->label->setText( tr("The server is running on port %1").arg(tcpServer->serverPort()) );

	connect(tcpServer, &QTcpServer::newConnection, this, &ServerInvade::newConnection);
}

ServerInvade::~ServerInvade(){
	delete ui;
}

void ServerInvade::rafraichir(SujetDObservation *){
	QJsonObject o;
	QJsonObject param;

	model->write(o);

	param["invade"] = o;

	for( const std::pair<const Side, QTcpSocket*>& c : clients ){
		param["side"] = static_cast<int>(c.first);
		sendMessage("refresh", param, c.second);
	}
}

void ServerInvade::newConnection(){
	QTcpSocket *clientConnection = tcpServer->nextPendingConnection();

	if( clients.empty() ){
		clients[Side::NORTH] = clientConnection;
	}else if( clients.size() == 1 ){
		clients[Side::SOUTH] = clientConnection;
	}else{
		// TODO error.
		clientConnection->disconnectFromHost();
		return;
	}

	connect(clientConnection, &QTcpSocket::disconnected, this, &ServerInvade::lostConnection);
	connect(clientConnection, &QTcpSocket::readyRead, this, &ServerInvade::readyRead);
	rafraichir(model);
}

void ServerInvade::lostConnection(){
	for( const std::pair<const Side, QTcpSocket*>& c : clients ){
		sendError("Client disconnected", c.second);
	}

	clients.clear();
}

void ServerInvade::readyRead(){

	QTcpSocket *clientConnection = qobject_cast<QTcpSocket *>(sender());

	QDataStream in(clientConnection);
	in.setVersion(QDataStream::Qt_4_0);

	if (blockSize == 0) {
		if (clientConnection->bytesAvailable() < (int)sizeof(quint16))
			return;

		in >> blockSize;
	}

	if (clientConnection->bytesAvailable() < blockSize)
		return;

	blockSize = 0;

	QByteArray block;

	in >> block;

	QJsonParseError error;
	QJsonDocument d = QJsonDocument::fromJson(block, &error);

	if( error.error != QJsonParseError::ParseError::NoError ){
		qDebug() << error.errorString();
		return;
	}

	if( !d.isObject() ){
		qDebug() << "Le json recu les pas valide";
		return;
	}

	for( const std::pair<const Side, QTcpSocket*>& c : clients ){
		if( c.second == client ){
			receveOrder(d.object(), c.first);
			return;
		}
	}

}

void ServerInvade::sendMessage(QString method, QJsonObject parameters, QTcpSocket * client){
	QJsonObject o;
	o["methode"] = method;
	o["parameters"] = parameters;
	QJsonDocument d{o};

	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);

	out << (quint16)0;
	out << d.toJson( QJsonDocument::JsonFormat::Compact );
	out.device()->seek(0);
	out << (quint16)(block.size() - sizeof(quint16));

	client->write(block);
}

void ServerInvade::sendError(QString reason, QTcpSocket *client){

	QJsonObject o;
	o["reason"] = reason;

	sendMessage("error", o, client);
	client->disconnectFromHost();
}

bool ServerInvade::isOrderValid(QJsonObject json){
	return json["method"].isString() && json["parameters"].isObject();
}

void ServerInvade::receveOrder(QJsonObject json, Side side){

	if( !isOrderValid(json) ){
		return;
	}

	switch (json["method"]) { // TODO : remplir les méthode dispo.
		case "":

			break;
	}

}
