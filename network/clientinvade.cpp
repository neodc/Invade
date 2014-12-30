#include "clientinvade.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonParseError>

ClientInvade::ClientInvade(QObject *parent) :
	QObject(parent),
	requestedNewGame_{false},
	connection_{this},
	stable_{false},
	blockSize_{0}{

	connect(&connection_, &QTcpSocket::readyRead, this, &ClientInvade::readyRead);
	connect(&connection_, &QTcpSocket::disconnected, this, &ClientInvade::lostConnection);
	connect(&connection_, &QTcpSocket::connected, this, &ClientInvade::newConnection);
}

bool ClientInvade::stable() const{ return stable_; }
const Invade & ClientInvade::model() const{ return model_; }
bool ClientInvade::requestedNewGame() const{ return requestedNewGame_; }

Side ClientInvade::side() const { return side_; }

void ClientInvade::name(const QString &name){
	QJsonObject p;
	p["name"] = name;

	sendMessage("name", p);
}

void ClientInvade::endPhase(){
	QJsonObject p;

	sendMessage("endPhase", p);
}

void ClientInvade::swapDice(const DiceType d1, const DiceType d2){
	QJsonObject p;
	p["d1"] = static_cast<int>(d1);
	p["d2"] = static_cast<int>(d2);

	sendMessage("swapDice", p);
}

void ClientInvade::chooseEffect(Effect effect, UnitType elite){
	QJsonObject p;
	p["effect"] = static_cast<int>(effect);
	p["elite"] = static_cast<int>(elite.id());

	sendMessage("chooseEffect", p);
}

void ClientInvade::move(const Position origin, const Position dest){
	QJsonObject p;
	p["origin"] = pos2str(origin);
	p["dest"] = pos2str(dest);

	sendMessage("move", p);
}

void ClientInvade::addUnit(const Position position, const UnitType type){
	QJsonObject p;
	p["position"] = pos2str(position);
	p["type"] = static_cast<int>(type.id());

	sendMessage("addUnit", p);
}

void ClientInvade::moveCommander(const Position origin, const Position dest){
	QJsonObject p;
	p["origin"] = pos2str(origin);
	p["dest"] = pos2str(dest);

	sendMessage("moveCommander", p);
}

void ClientInvade::attack(const Position origin, const Position dest, bool bombshell){
	QJsonObject p;
	p["origin"] = pos2str(origin);
	p["dest"] = pos2str(dest);
	p["bombshell"] = bombshell;

	sendMessage("attack", p);
}

void ClientInvade::newGame(bool ok){
	QJsonObject p;
	p["ok"] = ok;

	sendMessage("newGame", p);
}

void ClientInvade::connectToHost(const QString & hostName, quint16 port){
	if( !stable_ ){
		connection_.connectToHost(hostName, port);
	}
}

void ClientInvade::readyRead(){
	readOrder(qobject_cast<QTcpSocket *>(sender()));
}

void ClientInvade::lostConnection(){
	stable_ = false;
}

void ClientInvade::newConnection(){

}

void ClientInvade::readOrder(QTcpSocket *clientConnection){
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

	readOrder(clientConnection);
}

void ClientInvade::sendMessage(QString method, QJsonObject parameters){
	QJsonObject o;
	o["method"] = method;
	o["parameters"] = parameters;
	QJsonDocument d{o};

	qDebug() << method << parameters;

	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);

	out << (quint16)0;
	out << d.toJson( QJsonDocument::JsonFormat::Compact );
	out.device()->seek(0);
	out << (quint16)(block.size() - sizeof(quint16));

	connection_.write(block);
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
	}else if( method == "requestNewGame" ){
		receiveRequestNewGame(json["parameters"].toObject());
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

void ClientInvade::receiveRequestNewGame(QJsonObject){
	requestedNewGame_ = true;
	notifierChangement();
	requestedNewGame_ = false;
}
