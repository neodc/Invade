#include "invadeui.h"
#include "ui_invadeui.h"

InvadeUI::InvadeUI(Invade *invade, QWidget *parent) : QMainWindow(parent), invade_{invade}, ui(new Ui::InvadeUI){
	ui->setupUi(this);


	connect(ui->Next_, &QPushButton::clicked, this, &InvadeUI::nextPhase);
	connect(ui->actionQuit, &QAction::triggered, this, &InvadeUI::quit);
	connect(ui->actionNew_Game, &QAction::triggered, this, &InvadeUI::newGame);

	invade_->attacher(this);
	rafraichir(invade_);
}

void InvadeUI::nextPhase(){
	invade_->endPhase();
}

void InvadeUI::quit(){
	delete invade_;
	exit(0);
}

void InvadeUI::swapDice(){

}

void InvadeUI::choseEffect(){

}

void InvadeUI::move(){

}

void InvadeUI::moveCommender(){

}

void InvadeUI::attack(){

}

void InvadeUI::newGame(){
	//invade_->begin();
}

void InvadeUI::rafraichir(SujetDObservation *){
	QString laGrille;
	QLayoutItem *child;
	//Player p{invade_->player(invade_->current())};
	Player p {invade_->constPlayer(invade_->current())};
	while ((child = ui->Board_->takeAt(0)) != 0){
		delete child->widget();
	}
	for(unsigned i = 0; i < invade_->board().dimensions().x; i++){
		for(unsigned j = 0; j < invade_->board().dimensions().y; j++){
			if (!invade_->board().isCaseEmpty(Position{i,j})){
				switch (invade_->board().unitAt(Position{i,j}).type().id()) {
					case 0:
						laGrille.append("N");
						break;
					case 1:
						laGrille.append("A");
						break;
					case 2:
						laGrille.append("B");
						break;
					case 3:
						laGrille.append("C");
						break;
					default:
						break;
				}
			}else{
				laGrille.append("X");
			}
			ui->Board_->addWidget(new QLabel(laGrille),i,j);
			laGrille.clear();
		}
	}
	switch (invade_->phase()) {
		case Phase::NO_PLAYER:
			ui->Phase_->setText("NO_PLAYER");
			break;
		case Phase::PLAYING_DICE:
			ui->Phase_->setText("PLAYING_DICE");
			break;
		case Phase::PLAYING_EFFECT:
			ui->Phase_->setText("EFFECT");
			break;
		case Phase::PLAYING_MOVE:
			ui->Phase_->setText("PLAYING_MOVE");
			break;
		case Phase::PLAYING_COMMANDER:
			ui->Phase_->setText("PLAYING_COMMANDER");
			break;
		case Phase::PLAYING_ATTACK:
			ui->Phase_->setText("PLAYING_ATTACK");
			break;
		case Phase::END:
			ui->Phase_->setText("END");
			break;
		default:
			break;
	}
	ui->ABS_value_->setText(QString::number(p.dice(DiceType::ABS)));
	ui->ATT_value_->setText(QString::number(p.dice(DiceType::ATT)));
	ui->COM_value_->setText(QString::number(p.dice(DiceType::COM)));
	ui->ORD_value_->setText(QString::number(p.dice(DiceType::ORD)));
	ui->EFF_value_->setText(QString::number(p.dice(DiceType::EFF)));
	ui->DEF_value_->setText(QString::number(invade_->constPlayer(!invade_->current()).dice(DiceType::ATT)));
	ui->Soldiers_value_->setText(QString::number(p.unit(UnitType::NORMAL)));
	ui->ELITEA_value_->setText(QString::number(p.unit(UnitType::ELITE_A)));
	ui->ELITEB_value_->setText(QString::number(p.unit(UnitType::ELITE_B)));
	ui->ELITEC_value_->setText(QString::number(p.unit(UnitType::ELITE_C)));


}

InvadeUI::~InvadeUI() noexcept{
	delete ui;
}
