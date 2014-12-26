#include "newgame.h"
#include "ui_newgame.h"
#include "iostream"

newGame::newGame(QWidget *parent) :QDialog(parent), ui(new Ui::newGame){
	ui->setupUi(this);

	connect(ui->JoueurNordValue, &QLineEdit::textEdited, this, &newGame::setP1);
	connect(ui->JoueurSudValue, &QLineEdit::textEdited, this, &newGame::setP2);
}

const std::string newGame::p1() const{
	return p1_;
}

const std::string newGame::p2() const{
	return p2_;
}

void newGame::setP1(){
	p1_ = ui->JoueurNordValue->text().toStdString();
}

void newGame::setP2(){
	p2_ = ui->JoueurSudValue->text().toStdString();
}

newGame::~newGame(){
	delete ui;
}
