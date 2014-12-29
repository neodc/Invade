#include "serverinvade.h"
#include "ui_serverinvade.h"

#include <QMessageBox>
#include <QTcpSocket>
#include <QDebug>
#include <QJsonDocument>

ServerInvade::ServerInvade(int port, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ServerInvade),
	blockSize_{0}{

	ui->setupUi(this);

	tcpServer_ = new QTcpServer(this);
	if (!tcpServer_->listen(QHostAddress::Any, port)) {
		ui->label->setText( tr("Unable to start the server: %1.").arg(tcpServer_->errorString()) );
		return;
	}

	ui->label->setText( tr("The server is running on port %1").arg(tcpServer_->serverPort()) );

	connect(tcpServer_, &QTcpServer::newConnection, this, &ServerInvade::newConnection);

	model_.attacher(this);
}

ServerInvade::~ServerInvade(){
	delete ui;
}

void ServerInvade::rafraichir(SujetDObservation *){
	QJsonObject o;
	QJsonObject param;

	model_.write(o);

	param["invade"] = o;

	for( const std::pair<const Side, QTcpSocket*>& c : clients_ ){
		param["side"] = static_cast<int>(c.first);
		sendMessage("refresh", param, c.second);
	}
}

void ServerInvade::newConnection(){
	QTcpSocket *clientConnection = tcpServer_->nextPendingConnection();

	if( clients_.empty() ){
		clients_[Side::NORTH] = clientConnection;
	}else if( clients_.size() == 1 ){
		clients_[Side::SOUTH] = clientConnection;
	}else{
		sendError("No place left.", clientConnection);
		return;
	}

	connect(clientConnection, &QTcpSocket::disconnected, this, &ServerInvade::lostConnection);
	connect(clientConnection, &QTcpSocket::readyRead, this, &ServerInvade::readyRead);
	rafraichir(&model_);
}

void ServerInvade::lostConnection(){
	for( const std::pair<const Side, QTcpSocket*>& c : clients_ ){
		sendError("Client disconnected", c.second);
	}

	clients_.clear();
	model_.reset();
}

void ServerInvade::readyRead(){

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

	for( const std::pair<const Side, QTcpSocket*>& c : clients_ ){
		if( c.second == clientConnection ){
			receiveOrder(d.object(), c.first);
			return;
		}
	}

}

void ServerInvade::sendMessage(QString method, QJsonObject parameters, QTcpSocket * client){
	QJsonObject o;
	o["method"] = method;
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

void ServerInvade::receiveOrder(QJsonObject json, Side side){

	if( !isOrderValid(json) ){
		return;
	}

	if( model_.phase() != Phase::NO_PLAYER && model_.phase() != Phase::END && side != model_.current() ){
		return;
	}

	QString method = json["method"].toString();
	QJsonObject parameters = json["parameters"].toObject();
	if( method == "name" ){
		if( !parameters["name"].isString() || model_.phase() != Phase::NO_PLAYER ){
			return;
		}
		names_[side] = parameters["name"].toString().toStdString();

		if( names_.size() == 2 ){
			model_.begin(names_[Side::NORTH], names_[Side::SOUTH]);
		}
	}else if( method == "endPhase" ){
		model_.endPhase();
	}else if( method == "swapDice" ){
		if( !parameters["d1"].isDouble() || !parameters["d2"].isDouble() ){
			return;
		}
		model_.swapDice( static_cast<DiceType>(parameters["d1"].toInt()), static_cast<DiceType>(parameters["d2"].toInt()) );
	}else if( method == "chooseEffect" ){
		if( !parameters["effect"].isDouble() ){
			return;
		}

		if( parameters["elite"].isDouble() ){
			model_.chooseEffect(static_cast<Effect>(parameters["effect"].toInt()), UnitType::fromId(parameters["effect"].toInt()));
		}else{
			model_.chooseEffect(static_cast<Effect>(parameters["effect"].toInt()));
		}
	}else if( method == "move" ){
		if( !parameters["origin"].isString() || !parameters["dest"].isString() ){
			return;
		}

		model_.move( str2pos(parameters["origin"].toString()), str2pos(parameters["dest"].toString()) );
	}else if( method == "addUnit" ){
		if( !parameters["position"].isString() || !parameters["type"].isDouble() ){
			return;
		}

		model_.addUnit( str2pos(parameters["position"].toString()), UnitType::fromId( parameters["type"].toInt() ) );

	}else if( method == "moveCommander" ){
		if( !parameters["origin"].isString() || !parameters["dest"].isString() ){
			return;
		}

		model_.moveCommander( str2pos(parameters["origin"].toString()), str2pos(parameters["dest"].toString()) );
	}else if( method == "attack" ){
		if( !parameters["origin"].isString() || !parameters["dest"].isString() ){
			return;
		}

		if( parameters["bombshell"].isBool() ){
			model_.attack( str2pos(parameters["origin"].toString()), str2pos(parameters["dest"].toString()), parameters["bombshell"].toBool() );
		}else{
			model_.attack( str2pos(parameters["origin"].toString()), str2pos(parameters["dest"].toString()) );
		}
	}

}
