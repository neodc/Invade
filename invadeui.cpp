#include "invadeui.h"
#include "ui_invadeui.h"

InvadeUI::InvadeUI(Invade *invade, QWidget *parent) : QMainWindow(parent), invade_{invade}, ui(new Ui::InvadeUI){
	ui->setupUi(this);


	connect(ui->Next_, &QPushButton::clicked, this, &InvadeUI::nextPhase);
	connect(ui->actionQuit, &QAction::triggered, this, &InvadeUI::quit);
	connect(ui->actionNew_Game, &QAction::triggered, this, &InvadeUI::begin);

	QLabel * labelCOM = new QLabel("COM");
	QLabel * labelATT = new QLabel("ATT");
	QLabel * labelEFF = new QLabel("EFF");
	QLabel * labelABS = new QLabel("ABS");
	QLabel * labelORD = new QLabel("ORD");
	QLabel * labelDEF = new QLabel("DEF");
	COM = new DiceLabel(DiceType::COM, "COM");
	ATT = new DiceLabel(DiceType::ATT, "ATT");
	EFF = new DiceLabel(DiceType::EFF, "EFF");
	ABS = new DiceLabel(DiceType::ABS, "ABS");
	ORD = new DiceLabel(DiceType::ORD, "ORD");
	DEF = new DiceLabel(DiceType::ATT, "DEF");
	connect(COM, &DiceLabel::clicked, this, &InvadeUI::swapDice);
	connect(ATT, &DiceLabel::clicked, this, &InvadeUI::swapDice);
	connect(EFF, &DiceLabel::clicked, this, &InvadeUI::swapDice);
	connect(ABS, &DiceLabel::clicked, this, &InvadeUI::swapDice);
	connect(ORD, &DiceLabel::clicked, this, &InvadeUI::swapDice);
	ui->statLayout->addWidget(labelCOM, 0, 0);
	ui->statLayout->addWidget(labelATT, 1, 0);
	ui->statLayout->addWidget(labelEFF, 2, 0);
	ui->statLayout->addWidget(labelABS, 3, 0);
	ui->statLayout->addWidget(labelORD, 4, 0);
	ui->statLayout->addWidget(labelDEF, 5, 0);
	ui->statLayout->addWidget(COM, 0, 1);
	ui->statLayout->addWidget(ATT, 1, 1);
	ui->statLayout->addWidget(EFF, 2, 1);
	ui->statLayout->addWidget(ABS, 3, 1);
	ui->statLayout->addWidget(ORD, 4, 1);
	ui->statLayout->addWidget(DEF, 5, 1);

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
	QWidget *Widget = qobject_cast<QWidget*>(sender());
	if (!Widget){
	   return;
	}
	int index = ui->statLayout->indexOf(Widget);
	int rowOfButton, columnOfButton, rowSpanOfButton, columnSpanOfButton;
	ui->statLayout->getItemPosition(index, &rowOfButton, &columnOfButton, &rowSpanOfButton, &columnSpanOfButton);

	if (DiceTmp == NULL){
		DiceTmp = dynamic_cast<DiceLabel*>(ui->statLayout->itemAt(index)->widget());
	}else{
		DiceLabel *tmp = dynamic_cast<DiceLabel*>(ui->statLayout->itemAt(index)->widget());
		invade_->swapDice(DiceTmp->type(),tmp->type());
		DiceTmp = NULL;
	}
	rafraichir(invade_);
}

void InvadeUI::choseEffect(){

}

void InvadeUI::move(){

}

void InvadeUI::moveCommender(){

}

void InvadeUI::attack(){

}

void InvadeUI::begin(){
	newGame game{this};
	game.setWindowTitle("New Game");
	int retour = game.exec();

	if (retour == QDialog::Rejected) return;

	invade_->begin(game.p1(), game.p2());
	rafraichir(invade_);
}

void InvadeUI::rafraichir(SujetDObservation *){
	QString laGrille;
	QLayoutItem *child;
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
	ORD->setText(QString::number(p.dice(DiceType::ORD)));
	ABS->setText(QString::number(p.dice(DiceType::ABS)));
	ATT->setText(QString::number(p.dice(DiceType::ATT)));
	COM->setText(QString::number(p.dice(DiceType::COM)));
	EFF->setText(QString::number(p.dice(DiceType::EFF)));
	DEF->setText(QString::number(invade_->constPlayer(!invade_->current()).dice(DiceType::ATT)));

	ui->Soldiers_value_->setText(QString::number(p.unit(UnitType::NORMAL)));
	ui->ELITEA_value_->setText(QString::number(p.unit(UnitType::ELITE_A)));
	ui->ELITEB_value_->setText(QString::number(p.unit(UnitType::ELITE_B)));
	ui->ELITEC_value_->setText(QString::number(p.unit(UnitType::ELITE_C)));


}

InvadeUI::~InvadeUI() noexcept{
	delete ui;
}
