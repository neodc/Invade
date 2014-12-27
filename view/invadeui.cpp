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

	EliteLabel * Soldier = new EliteLabel(UnitType::NORMAL, "Soldiers");
	EliteLabel * EliteA = new EliteLabel(UnitType::ELITE_A, "EliteA");
	EliteLabel * EliteB = new EliteLabel(UnitType::ELITE_B, "EliteB");
	EliteLabel * EliteC = new EliteLabel(UnitType::ELITE_C, "EliteC");
	SoldierValue = new QLabel(this);
	EliteAValue = new QLabel(this);
	EliteBValue = new QLabel(this);
	EliteCValue = new QLabel(this);
	EffectLabel * noEffect = new EffectLabel(Effect::NO_EFFECT, "No effect");
	EffectLabel * increasedMovement = new EffectLabel(Effect::INCREASED_MOVEMENT, "Increased movement");
	EffectLabel * incrementSoldier = new EffectLabel(Effect::INCREMENT_SOLDIER, "Increment soldier");
	EffectLabel * improvedAttack = new EffectLabel(Effect::IMPROVED_ATTACK, "Improved attack");
	EffectLabel * changeSoldier = new EffectLabel(Effect::CHANGE_SOLDIER, "Change soldier");

	connect(COM, &DiceLabel::clicked, this, &InvadeUI::swapDice);
	connect(ATT, &DiceLabel::clicked, this, &InvadeUI::swapDice);
	connect(EFF, &DiceLabel::clicked, this, &InvadeUI::swapDice);
	connect(ABS, &DiceLabel::clicked, this, &InvadeUI::swapDice);
	connect(ORD, &DiceLabel::clicked, this, &InvadeUI::swapDice);

	connect(Soldier, &EliteLabel::clicked, this, &InvadeUI::selectUnit);
	connect(EliteA, &EliteLabel::clicked, this, &InvadeUI::selectUnit);
	connect(EliteB, &EliteLabel::clicked, this, &InvadeUI::selectUnit);
	connect(EliteC, &EliteLabel::clicked, this, &InvadeUI::selectUnit);

	connect(noEffect, &EffectLabel::clicked, this, &InvadeUI::choseEffect);
	connect(increasedMovement, &EffectLabel::clicked, this, &InvadeUI::choseEffect);
	connect(incrementSoldier, &EffectLabel::clicked, this, &InvadeUI::choseEffect);
	connect(improvedAttack, &EffectLabel::clicked, this, &InvadeUI::choseEffect);
	connect(changeSoldier, &EffectLabel::clicked, this, &InvadeUI::choseEffect);


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

	ui->statLayout->addWidget(Soldier, 0, 2);
	ui->statLayout->addWidget(SoldierValue, 1, 2);
	ui->statLayout->addWidget(EliteA, 0, 3);
	ui->statLayout->addWidget(EliteAValue, 1, 3);
	ui->statLayout->addWidget(EliteB, 2, 2);
	ui->statLayout->addWidget(EliteBValue, 3, 2);
	ui->statLayout->addWidget(EliteC, 2, 3);
	ui->statLayout->addWidget(EliteCValue, 3, 3);

	ui->effectLayout->addWidget(noEffect, 0, 0);
	ui->effectLayout->addWidget(increasedMovement, 1, 0);
	ui->effectLayout->addWidget(incrementSoldier, 2, 0);
	ui->effectLayout->addWidget(improvedAttack, 3, 0);
	ui->effectLayout->addWidget(changeSoldier, 4, 0);

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
	QWidget *Widget = qobject_cast<QWidget*>(sender());
	if (!Widget){
	   return;
	}
	int index = ui->effectLayout->indexOf(Widget);
	int rowOfButton, columnOfButton, rowSpanOfButton, columnSpanOfButton;
	ui->effectLayout->getItemPosition(index, &rowOfButton, &columnOfButton, &rowSpanOfButton, &columnSpanOfButton);
	EffectLabel * tmp = dynamic_cast<EffectLabel*>(ui->effectLayout->itemAt(index)->widget());
	if (!(tmp->type() == Effect::CHANGE_SOLDIER && selectedUnitType == UnitType::NORMAL)){
		invade_->chooseEffect(tmp->type(), selectedUnitType);
	}
}

void InvadeUI::move(){
	QWidget *Widget = qobject_cast<QWidget*>(sender());
	if (!Widget){
	   return;
	}
	int index = ui->Board_->indexOf(Widget);
	int rowOfButton, columnOfButton, rowSpanOfButton, columnSpanOfButton;
	ui->Board_->getItemPosition(index, &rowOfButton, &columnOfButton, &rowSpanOfButton, &columnSpanOfButton);
	unsigned x = columnOfButton;
	unsigned y = rowOfButton;
	if (invade_->board().isCaseEmpty(Position{x,y}) && (PosTmp.x == 100)){
		if ((y == 15 && (invade_->current() == Side::SOUTH))
				|| (y == 0 && (invade_->current() == Side::NORTH))){
			invade_->addUnit(Position{x,y}, selectedUnitType);
		}
	}else{
		if (PosTmp.x == 100){
			PosTmp = Position{x,y};
		}else{
			invade_->move(PosTmp, Position{x,y});
			PosTmp = Position{100,100};
		}
	}
	rafraichir(invade_);
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

void InvadeUI::selectUnit(){
	QWidget *Widget = qobject_cast<QWidget*>(sender());
	if (!Widget){
	   return;
	}
	int index = ui->statLayout->indexOf(Widget);
	int rowOfButton, columnOfButton, rowSpanOfButton, columnSpanOfButton;
	ui->statLayout->getItemPosition(index, &rowOfButton, &columnOfButton, &rowSpanOfButton, &columnSpanOfButton);
	EliteLabel * tmp = dynamic_cast<EliteLabel*>(ui->statLayout->itemAt(index)->widget());
	selectedUnitType = tmp->type().type();
}

void InvadeUI::rafraichir(SujetDObservation *){
	QLayoutItem *child;
	Player p {invade_->constPlayer(invade_->current())};
	ClickableLabel * label;
	while ((child = ui->Board_->takeAt(0)) != 0){
		delete child->widget();
	}

	for(unsigned i = 0; i < invade_->board().dimensions().x; i++){
		for(unsigned j = 0; j < invade_->board().dimensions().y; j++){
			if (!invade_->board().isCaseEmpty(Position{i,j})){
				UnitType tmp = invade_->board().unitAt(Position{i,j}).type();
				if (tmp == UnitType::NORMAL){
					label = new ClickableLabel("N");
				}else if (tmp == UnitType::ELITE_A){
					label = new ClickableLabel("A");
				}else if (tmp == UnitType::ELITE_B){
					label = new ClickableLabel("B");
				}else if (tmp == UnitType::ELITE_C){
					label = new ClickableLabel("C");
				}
			}else{
				label = new ClickableLabel("X");
			}
			ui->Board_->addWidget(label,j,i);
			connect(label, &ClickableLabel::clicked, this, &InvadeUI::move);
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

	SoldierValue->setText(QString::number(p.unit(UnitType::NORMAL)));
	EliteAValue->setText(QString::number(p.unit(UnitType::ELITE_A)));
	EliteBValue->setText(QString::number(p.unit(UnitType::ELITE_B)));
	EliteCValue->setText(QString::number(p.unit(UnitType::ELITE_C)));


}

InvadeUI::~InvadeUI() noexcept{
	delete ui;
}
