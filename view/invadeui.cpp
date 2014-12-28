#include "invadeui.h"
#include "ui_invadeui.h"

InvadeUI::InvadeUI(Invade *invade, QWidget *parent) : QMainWindow(parent), invade_{invade}, ui(new Ui::InvadeUI){
	ui->setupUi(this);

	TileLabel * label;
	for(unsigned i = 0; i < invade_->board().dimensions().x; i++){
		for(unsigned j = 0; j < invade_->board().dimensions().y; j++){
			label = new TileLabel("");
			ui->Board_->addWidget(label,j,i);
			connect(label, &TileLabel::clicked, this, &InvadeUI::UnitAction);
		}
	}

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

	Soldier = new EliteLabel(UnitType::NORMAL, Images::pawn());
	EliteA = new EliteLabel(UnitType::ELITE_A, Images::pawn(UnitType::ELITE_A));
	EliteB = new EliteLabel(UnitType::ELITE_B, Images::pawn(UnitType::ELITE_B));
	EliteC = new EliteLabel(UnitType::ELITE_C, Images::pawn(UnitType::ELITE_C));

	SoldierValue = new QLabel(this);
	EliteAValue = new QLabel(this);
	EliteBValue = new QLabel(this);
	EliteCValue = new QLabel(this);
	EffectLabel * noEffect = new EffectLabel(Effect::NO_EFFECT, "No effect");
	EffectLabel * increasedMovement = new EffectLabel(Effect::INCREASED_MOVEMENT, "Increased movement");
	EffectLabel * incrementSoldier = new EffectLabel(Effect::INCREMENT_SOLDIER, "Increment soldier");
	EffectLabel * improvedAttack = new EffectLabel(Effect::IMPROVED_ATTACK, "Improved attack");
	EffectLabel * changeSoldier = new EffectLabel(Effect::CHANGE_SOLDIER, "Change soldier");

	BombShell = new QCheckBox(this);
	BombShell->setText("BombShell");

	connect(ui->Next_, &QPushButton::clicked, this, &InvadeUI::nextPhase);
	connect(ui->actionQuit, &QAction::triggered, this, &InvadeUI::quit);
	connect(ui->actionNew_Game, &QAction::triggered, this, &InvadeUI::begin);

	connect(COM, &DiceLabel::clicked, this, &InvadeUI::swapDice);
	connect(ATT, &DiceLabel::clicked, this, &InvadeUI::swapDice);
	connect(EFF, &DiceLabel::clicked, this, &InvadeUI::swapDice);
	connect(ABS, &DiceLabel::clicked, this, &InvadeUI::swapDice);
	connect(ORD, &DiceLabel::clicked, this, &InvadeUI::swapDice);

	connect(Soldier, &EliteLabel::clicked, this, &InvadeUI::selectUnit);
	connect(EliteA, &EliteLabel::clicked, this, &InvadeUI::selectUnit);
	connect(EliteB, &EliteLabel::clicked, this, &InvadeUI::selectUnit);
	connect(EliteC, &EliteLabel::clicked, this, &InvadeUI::selectUnit);

	connect(noEffect, &EffectLabel::clicked, this, &InvadeUI::chooseEffect);
	connect(increasedMovement, &EffectLabel::clicked, this, &InvadeUI::chooseEffect);
	connect(incrementSoldier, &EffectLabel::clicked, this, &InvadeUI::chooseEffect);
	connect(improvedAttack, &EffectLabel::clicked, this, &InvadeUI::chooseEffect);
	connect(changeSoldier, &EffectLabel::clicked, this, &InvadeUI::chooseEffect);

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

	ui->effectLayout->addWidget(BombShell, 0, 1);

	invade_->attacher(this);
	rafraichir(invade_);
}

void InvadeUI::nextPhase(){
	invade_->endPhase();
	PosTmp = Position{100,100};
	DiceTmp = NULL;
	BombShell->setChecked(false);
	//TODO debugger le dé de defence
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

void InvadeUI::chooseEffect(){
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

void InvadeUI::begin(){
	newGame game{this};
	game.setWindowTitle("New Game");
	int retour = game.exec();

	if (retour == QDialog::Rejected) return;

	invade_->begin(game.p1(), game.p2());

	selectedUnitType = UnitType::NORMAL;
	PosTmp = Position{100,100};
	DiceTmp = NULL;
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
	rafraichir(invade_);
}

void InvadeUI::UnitAction(){
	QWidget *Widget = qobject_cast<QWidget*>(sender());
	if (!Widget){
	   return;
	}
	int index = ui->Board_->indexOf(Widget);
	int rowOfButton, columnOfButton, rowSpanOfButton, columnSpanOfButton;
	ui->Board_->getItemPosition(index, &rowOfButton, &columnOfButton, &rowSpanOfButton, &columnSpanOfButton);
	unsigned x = columnOfButton;
	unsigned y = rowOfButton;
	if (invade_->phase() == Phase::PLAYING_MOVE){
		move(Position{x,y});
	}else if (invade_->phase() == Phase::PLAYING_COMMANDER){
		moveCommander(Position{x,y});
	}else if (invade_->phase() == Phase::PLAYING_ATTACK){
		attack(Position{x,y});
	}
	rafraichir(invade_);
}

void InvadeUI::move(Position sender){
	if (invade_->board().isCaseEmpty(sender) && (PosTmp.x == 100)){
		if ((sender.y == 15 && (invade_->current() == Side::SOUTH))
				|| (sender.y == 0 && (invade_->current() == Side::NORTH))){
			invade_->addUnit(sender, selectedUnitType);
		}
	}else{
		if (PosTmp.x == 100){
			PosTmp = sender;
		}else{
			invade_->move(PosTmp, sender);
			PosTmp = Position{100,100};
		}
	}
}

void InvadeUI::moveCommander(Position sender){
	if (PosTmp.x == 100){
		PosTmp = sender;
	}else{
		invade_->moveCommander(PosTmp, sender);
		PosTmp = Position{100,100};
	}
	//TODO Faire en sorte que ca marche
}

void InvadeUI::attack(Position sender){
	if (PosTmp.x == 100){
		PosTmp = sender;
	}else{
		invade_->attack(PosTmp, sender, BombShell->isChecked());
		PosTmp = Position{100,100};
	}
	//TODO tester BombShell
}

void InvadeUI::rafraichir(SujetDObservation *){
	Player p {invade_->constPlayer(invade_->current())};
	TileLabel * label;

	for(unsigned i = 0; i < invade_->board().dimensions().x; i++){
		for(unsigned j = 0; j < invade_->board().dimensions().y; j++){
			label = dynamic_cast<TileLabel*>(ui->Board_->itemAtPosition(j,i)->widget());
			if (!invade_->board().isCaseEmpty(Position{i,j})){
				UnitType tmp = invade_->board().unitAt(Position{i,j}).type();
				bool selected = Position{i,j} == PosTmp;
				bool damaged = invade_->board().unitAt(Position{i,j}).hp() < invade_->board().unitAt(Position{i,j}).type().hpMax();
				if (tmp == UnitType::NORMAL){
					label->setPixmap(Images::pawn(UnitType::NORMAL, selected, damaged, invade_->board().unitAt(Position{i,j}).side()));
				}else if (tmp == UnitType::ELITE_A){
					label->setPixmap(Images::pawn(UnitType::ELITE_A, selected, damaged, invade_->board().unitAt(Position{i,j}).side()));
				}else if (tmp == UnitType::ELITE_B){
					label->setPixmap(Images::pawn(UnitType::ELITE_B, selected, damaged, invade_->board().unitAt(Position{i,j}).side()));
				}else if (tmp == UnitType::ELITE_C){
					label->setPixmap(Images::pawn(UnitType::ELITE_C, selected, damaged, invade_->board().unitAt(Position{i,j}).side()));
				}
			}else{
				label->setPixmap(Images::tile());
			}
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
/*	ORD->setImage(p.dice(DiceType::ORD), DiceTmp == ORD);
	ABS->setImage(p.dice(DiceType::ABS), DiceTmp == ABS);
	ATT->setImage(p.dice(DiceType::ATT), DiceTmp == ATT);
	COM->setImage(p.dice(DiceType::COM), DiceTmp == COM);
	EFF->setImage(p.dice(DiceType::EFF), DiceTmp == EFF);
	DEF->setImage(invade_->constPlayer(!invade_->current()).dice(DiceType::ATT));
*/
	ORD->setPixmap(Images::dice(p.dice(DiceType::ORD), DiceTmp == ORD));
	ABS->setPixmap(Images::dice(p.dice(DiceType::ABS), DiceTmp == ABS));
	ATT->setPixmap(Images::dice(p.dice(DiceType::ATT), DiceTmp == ATT));
	COM->setPixmap(Images::dice(p.dice(DiceType::COM), DiceTmp == COM));
	EFF->setPixmap(Images::dice(p.dice(DiceType::EFF), DiceTmp == EFF));
	DEF->setPixmap(Images::dice(invade_->constPlayer(!invade_->current()).dice(DiceType::ATT)));

	Soldier->setPixmap(Images::pawn(UnitType::NORMAL, selectedUnitType == UnitType::NORMAL));
	EliteA->setPixmap(Images::pawn(UnitType::ELITE_A, selectedUnitType == UnitType::ELITE_A));
	EliteB->setPixmap(Images::pawn(UnitType::ELITE_B, selectedUnitType == UnitType::ELITE_B));
	EliteC->setPixmap(Images::pawn(UnitType::ELITE_C, selectedUnitType == UnitType::ELITE_C));

	SoldierValue->setText(QString::number(p.unit(UnitType::NORMAL)));
	EliteAValue->setText(QString::number(p.unit(UnitType::ELITE_A)));
	EliteBValue->setText(QString::number(p.unit(UnitType::ELITE_B)));
	EliteCValue->setText(QString::number(p.unit(UnitType::ELITE_C)));

	//TODO afficher pv unit?
}

InvadeUI::~InvadeUI() noexcept{
	QLayoutItem *child;
	while ((child = ui->Board_->takeAt(0)) != 0){
		delete child->widget();
	}
	while ((child = ui->statLayout->takeAt(0)) != 0){
		delete child->widget();
	}
	while ((child = ui->effectLayout->takeAt(0)) != 0){
		delete child->widget();
	}
	delete ui;
}
