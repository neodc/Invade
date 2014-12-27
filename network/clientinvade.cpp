#include "clientinvade.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonParseError>

ClientInvade::ClientInvade(QObject *parent) :
	QObject(parent),
	connection_{this},
	stable_{false},
	blockSize_{0}{

	connect(&connection_, &QTcpSocket::readyRead, this, &ClientInvade::readyRead);
	connect(&connection_, &QTcpSocket::disconnected, this, &ClientInvade::lostConnection);
	connect(&connection_, &QTcpSocket::connected, this, &ClientInvade::newConnection);
}

bool ClientInvade::stable() const{ return stable_; }
const Invade & ClientInvade::model() const{ return model_; }

void ClientInvade::connectToHost(const QString & hostName, quint16 port){
	if( !stable_ ){
		connection_.connectToHost(hostName, port);
	}
}

void ClientInvade::readyRead(){

	QTcpSocket *clientConnection = qobject_cast<QTcpSocket *>(sender());

	QDataStream in(clientConnection);
	in.setVersion(QDataStream::Qt_4_0);

	if (blockSize_ == 0) {
		if (clientConnection->bytesAvailable() < (int)sizeof(quint16))
			return;

		in >> blockSize_;
	}

	if (clientConnection->bytesAvailable() < blockSize_)
		return;

	blockSize_ = 0;

	QByteArray block;

	in >> block;

	QJsonParseError error;
	QJsonDocument d = QJsonDocument::fromJson(block, &error);

	if( error.error != QJsonParseError::ParseError::NoError ){
		qDebug() << error.errorString();
		return;
	}

	if( !d.isObject() ){
		qDebug() << "Le json recu n'est pas valide";
		return;
	}

	receiveOrder( d.object() );

}

void ClientInvade::lostConnection(){
	stable_ = false;
}

void ClientInvade::newConnection(){

}

bool ClientInvade::isOrderValid(QJsonObject json){
	return json["method"].isString() && json["parameters"].isObject();
}

void ClientInvade::receiveOrder(QJsonObject json){
	if( !isOrderValid(json) ){
		return;
	}

	QString method = json["method"].toString();

	if( method == "refresh" ){
		receiveRefresh(json["parameters"].toObject());
	}else if( method == "error" ){
		receiveError(json["parameters"].toObject());
	}
}

void ClientInvade::receiveRefresh(QJsonObject json){
	if( !json["invade"].isObject() || !json["side"].isDouble() ){
		return;
	}

	side_ = static_cast<Side>(json["side"].toInt());

	model_.read( json["invade"].toObject() );

	stable_ = true;
	notifierChangement();
}

void ClientInvade::receiveError(QJsonObject json){
	if( !json["reason"].isString() ){
		return;
	}

	qDebug() << "ERROR: " << json["reason"].toString();
}
