#include "invadeui.h"
#include "ui_invadeui.h"

#include <QMessageBox>

InvadeUI::InvadeUI(QString name, QString host, int port, QWidget *parent) : QMainWindow(parent), ui(new Ui::InvadeUI){
	ui->setupUi(this);

	invade_.connectToHost(host, port);

	TileLabel * label;

	for(unsigned i = 0; i < invade_.model().board().dimensions().x; i++){
		for(unsigned j = 0; j < invade_.model().board().dimensions().y; j++){
			label = new TileLabel("");
			ui->Board_->addWidget(label,j,i);
			connect(label, &TileLabel::leftClicked, this, &InvadeUI::unitAction);
			connect(label, &TileLabel::rightClicked, this, &InvadeUI::rightUnitAction);
		}
	}
	ui->statusBar->addWidget(&nbActions_);

	QLabel * labelCOM = new QLabel("COM");
	QLabel * labelABS = new QLabel("ABS");
	QLabel * labelORD = new QLabel("ORD");
	QLabel * labelEFF = new QLabel("EFF");
	QLabel * labelATT = new QLabel("ATT");
	QLabel * labelDEF = new QLabel("DEF");
	labelCOM->setAlignment(Qt::AlignCenter | Qt::AlignBottom);
	labelABS->setAlignment(Qt::AlignCenter| Qt::AlignBottom);
	labelORD->setAlignment(Qt::AlignCenter| Qt::AlignBottom);
	labelEFF->setAlignment(Qt::AlignCenter| Qt::AlignTop);
	labelATT->setAlignment(Qt::AlignCenter| Qt::AlignTop);
	labelDEF->setAlignment(Qt::AlignCenter| Qt::AlignBottom);

	COM = new DiceLabel(DiceType::COM, "COM");
	ATT = new DiceLabel(DiceType::ATT, "ATT");
	EFF = new DiceLabel(DiceType::EFF, "EFF");
	ABS = new DiceLabel(DiceType::ABS, "ABS");
	ORD = new DiceLabel(DiceType::ORD, "ORD");
	DEF = new DiceLabel(DiceType::ATT, "DEF");
	Arrows = new QLabel(this);
	Arrows->setScaledContents(true);
	Arrows->setMaximumSize(QSize(64, 64));

	Soldier = new EliteLabel(UnitType::NORMAL, Images::pawn());
	EliteA = new EliteLabel(UnitType::ELITE_A, Images::pawn(UnitType::ELITE_A));
	EliteB = new EliteLabel(UnitType::ELITE_B, Images::pawn(UnitType::ELITE_B));
	EliteC = new EliteLabel(UnitType::ELITE_C, Images::pawn(UnitType::ELITE_C));

	SoldierValue = new QLabel(this);
	EliteAValue = new QLabel(this);
	EliteBValue = new QLabel(this);
	EliteCValue = new QLabel(this);

	noEffect = new EffectLabel(Effect::NO_EFFECT, "No effect");
	increasedMovement = new EffectLabel(Effect::INCREASED_MOVEMENT, "Increased movement");
	incrementSoldier = new EffectLabel(Effect::INCREMENT_SOLDIER, "Increment soldier");
	improvedAttack = new EffectLabel(Effect::IMPROVED_ATTACK, "Improved attack");
	changeSoldier = new EffectLabel(Effect::CHANGE_SOLDIER, "Change soldier");

	BombShell = new QCheckBox(this);
	BombShell->setText("BombShell");

	connect(ui->Next_, &QPushButton::clicked, this, &InvadeUI::nextPhase);
	connect(ui->actionQuit, &QAction::triggered, this, &InvadeUI::quit);
	connect(ui->actionNew_Game, &QAction::triggered, this, &InvadeUI::begin);

	connect(COM, &DiceLabel::leftClicked, this, &InvadeUI::swapDice);
	connect(ATT, &DiceLabel::leftClicked, this, &InvadeUI::swapDice);
	connect(EFF, &DiceLabel::leftClicked, this, &InvadeUI::swapDice);
	connect(ABS, &DiceLabel::leftClicked, this, &InvadeUI::swapDice);
	connect(ORD, &DiceLabel::leftClicked, this, &InvadeUI::swapDice);

	connect(Soldier, &EliteLabel::clicked, this, &InvadeUI::selectUnit);
	connect(EliteA, &EliteLabel::clicked, this, &InvadeUI::selectUnit);
	connect(EliteB, &EliteLabel::clicked, this, &InvadeUI::selectUnit);
	connect(EliteC, &EliteLabel::clicked, this, &InvadeUI::selectUnit);

	connect(noEffect, &EffectLabel::clicked, this, &InvadeUI::chooseEffect);
	connect(increasedMovement, &EffectLabel::clicked, this, &InvadeUI::chooseEffect);
	connect(incrementSoldier, &EffectLabel::clicked, this, &InvadeUI::chooseEffect);
	connect(improvedAttack, &EffectLabel::clicked, this, &InvadeUI::chooseEffect);
	connect(changeSoldier, &EffectLabel::clicked, this, &InvadeUI::chooseEffect);

	ui->diceLayout->addWidget(labelCOM, 0, 1);
	ui->diceLayout->addWidget(labelABS, 1, 0);
	ui->diceLayout->addWidget(labelORD, 1, 2);
	ui->diceLayout->addWidget(labelEFF, 5, 0);
	ui->diceLayout->addWidget(labelATT, 5, 2);

	ui->diceLayout->addWidget(COM, 1, 1);
	ui->diceLayout->addWidget(ABS, 2, 0);
	ui->diceLayout->addWidget(ORD, 2, 2);
	ui->diceLayout->addWidget(EFF, 4, 0);
	ui->diceLayout->addWidget(ATT, 4, 2);
	ui->diceLayout->addWidget(Arrows, 2, 1);

	ui->pawnLayout->addWidget(Soldier, 1, 4);
	ui->pawnLayout->addWidget(SoldierValue, 1, 5);
	ui->pawnLayout->addWidget(EliteA, 2, 4);
	ui->pawnLayout->addWidget(EliteAValue, 2, 5);
	ui->pawnLayout->addWidget(EliteB, 3, 4);
	ui->pawnLayout->addWidget(EliteBValue, 3, 5);
	ui->pawnLayout->addWidget(EliteC, 4, 4);
	ui->pawnLayout->addWidget(EliteCValue, 4, 5);

	ui->enemyLayout->addWidget(labelDEF, 0, 0);
	ui->enemyLayout->addWidget(DEF, 0, 1);

	ui->effectLayout->addWidget(noEffect, 0, 0);
	ui->effectLayout->addWidget(increasedMovement, 1, 0);
	ui->effectLayout->addWidget(incrementSoldier, 2, 0);
	ui->effectLayout->addWidget(improvedAttack, 3, 0);
	ui->effectLayout->addWidget(changeSoldier, 4, 0);

	ui->effectLayout->addWidget(BombShell, 0, 1);

	invade_.attacher(this);
	invade_.name(name);
	rafraichir(nullptr);
}

void InvadeUI::nextPhase(){
	invade_.endPhase();
	PosTmp = Position{100,100};
	DiceTmp = NULL;
	BombShell->setChecked(false);
}

void InvadeUI::quit(){
	exit(0);
}

void InvadeUI::swapDice(){
	QWidget *Widget = qobject_cast<QWidget*>(sender());
	if (!Widget){
	   return;
	}
	int index = ui->diceLayout->indexOf(Widget);
	int rowOfButton, columnOfButton, rowSpanOfButton, columnSpanOfButton;
	ui->diceLayout->getItemPosition(index, &rowOfButton, &columnOfButton, &rowSpanOfButton, &columnSpanOfButton);

	if (DiceTmp == NULL){
		DiceTmp = dynamic_cast<DiceLabel*>(ui->diceLayout->itemAt(index)->widget());
	}else{
		DiceLabel *tmp = dynamic_cast<DiceLabel*>(ui->diceLayout->itemAt(index)->widget());
		invade_.swapDice(DiceTmp->type(),tmp->type());
		DiceTmp = NULL;
	}
	rafraichir(nullptr);
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
		invade_.chooseEffect(tmp->type(), selectedUnitType);
	}
}

void InvadeUI::begin(){
	invade_.newGame(); // TODO ajouter un message ?
}


void InvadeUI::selectUnit(){
	QWidget *Widget = qobject_cast<QWidget*>(sender());
	if (!Widget){
	   return;
	}
	int index = ui->pawnLayout->indexOf(Widget);
	int rowOfButton, columnOfButton, rowSpanOfButton, columnSpanOfButton;
	ui->pawnLayout->getItemPosition(index, &rowOfButton, &columnOfButton, &rowSpanOfButton, &columnSpanOfButton);
	EliteLabel * tmp = dynamic_cast<EliteLabel*>(ui->pawnLayout->itemAt(index)->widget());
	selectedUnitType = tmp->type().type();
	rafraichir(nullptr);
}

void InvadeUI::unitAction(){
	QWidget *Widget = qobject_cast<QWidget*>(sender());
	if (!Widget){
	   return;
	}
	int index = ui->Board_->indexOf(Widget);
	int rowOfButton, columnOfButton, rowSpanOfButton, columnSpanOfButton;
	ui->Board_->getItemPosition(index, &rowOfButton, &columnOfButton, &rowSpanOfButton, &columnSpanOfButton);
	unsigned x = columnOfButton;
	unsigned y = rowOfButton;
	if (invade_.model().phase() == Phase::PLAYING_MOVE){
		move(Position{x,y});
	}else if (invade_.model().phase() == Phase::PLAYING_COMMANDER){
		moveCommander(Position{x,y});
	}else if (invade_.model().phase() == Phase::PLAYING_ATTACK){
		attack(Position{x,y});
	}
	rafraichir(nullptr);
}

void InvadeUI::rightUnitAction(){
	QWidget *Widget = qobject_cast<QWidget*>(sender());
	if (!Widget){
	   return;
	}
	int index = ui->Board_->indexOf(Widget);
	int rowOfButton, columnOfButton, rowSpanOfButton, columnSpanOfButton;
	ui->Board_->getItemPosition(index, &rowOfButton, &columnOfButton, &rowSpanOfButton, &columnSpanOfButton);
	unsigned x = columnOfButton;
	unsigned y = rowOfButton;
	if (invade_.model().phase() == Phase::PLAYING_ATTACK){
		rightAttack(Position{x,y});
	}
	rafraichir(nullptr);
}

void InvadeUI::move(Position sender){
	if (invade_.model().board().isCaseEmpty(sender) && (PosTmp.x == 100)){
		if ((sender.y == 15 && (invade_.model().current() == Side::SOUTH))
				|| (sender.y == 0 && (invade_.model().current() == Side::NORTH))){
			invade_.addUnit(sender, selectedUnitType);
		}
	}else{
		if (PosTmp.x == 100/* && invade_.model().board().unitAt(sender).enable()*/){
			PosTmp = sender;
		}else{
			invade_.move(PosTmp, sender);
			PosTmp = Position{100,100};
		}
	}
}

void InvadeUI::moveCommander(Position sender){
	if (PosTmp.x == 100){
		PosTmp = sender;
	}else{
		invade_.moveCommander(PosTmp, sender);
		PosTmp = Position{100,100};
	}
}

void InvadeUI::attack(Position sender, bool bombshell){
	if (PosTmp.x == 100){
		PosTmp = sender;
	}else{
		invade_.attack(PosTmp, sender, BombShell->isChecked());
		PosTmp = Position{100,100};
	}
}

void InvadeUI::rightAttack(Position sender){
		attack(sender, invade_.model().board().unitAt(sender).bombshell() > 0);
}

void InvadeUI::rafraichir(SujetDObservation *){

	if( invade_.requestedNewGame() ){
		int r = QMessageBox::question(
					this,
					"New game",
					"Do you wanna start a new game?",
					QMessageBox::Yes | QMessageBox::No,
					QMessageBox::No
					);

		invade_.newGame( r == QMessageBox::Yes );
	}

	if( invade_.model().phase() == Phase::NO_PLAYER ){
		return; // TODO: manage this case
	}
	ui->Base_->setTitle(QString::fromStdString(invade_.model().constPlayer(invade_.side()).name()));
	ui->Enemy_->setTitle(QString::fromStdString(invade_.model().constPlayer(!invade_.side()).name()));
	Player p {invade_.model().constPlayer(invade_.model().current())};
	TileLabel * tile;
	bool check = false;

	for(unsigned i = 0; i < invade_.model().board().dimensions().x; i++){
		for(unsigned j = 0; j < invade_.model().board().dimensions().y; j++){
			if(PosTmp != Position{100, 100}){
				check = (	(invade_.model().phase() == Phase::PLAYING_MOVE && invade_.model().canMove(PosTmp, Position{i,j}))
						||	(invade_.model().phase() == Phase::PLAYING_COMMANDER) && invade_.model().canMoveCommander(PosTmp, Position{i,j})
						||	(invade_.model().phase() == Phase::PLAYING_ATTACK) && invade_.model().canAttack(PosTmp, Position{i,j}, BombShell->isChecked())
						);
			}
			tile = dynamic_cast<TileLabel*>(ui->Board_->itemAtPosition(j,i)->widget());
			if (!invade_.model().board().isCaseEmpty(Position{i,j})){
				Unit tmp = invade_.model().board().unitAt(Position{i,j});
			//	UnitType tmp = invade_.model().board().unitAt(Position{i,j}).type();
				bool selected = Position{i,j} == PosTmp;
			//	bool damaged = invade_.model().board().unitAt(Position{i,j}).hp() < invade_.model().board().unitAt(Position{i,j}).type().hpMax();
				tile->setPixmap(Images::tile(tmp, check, selected));
			/*	if (tmp == UnitType::NORMAL){
					tile->setPixmap(Images::pawn(tmp, selected);
				}else if (tmp == UnitType::ELITE_A){
					tile->setPixmap(Images::pawn(tmp, selected);
				}else if (tmp == UnitType::ELITE_B){
					tile->setPixmap(Images::pawn(tmp, selected);
				}else if (tmp == UnitType::ELITE_C){
					tile->setPixmap(Images::pawn(tmp, selected);
				}*/
			}else{
				tile->setPixmap(Images::tile(check));
			}
		}
	}

	switch (invade_.model().phase()) {
		case Phase::NO_PLAYER:
			ui->Phase_->setText("NO PLAYER");
			nbActions_.setText("");
			break;
		case Phase::PLAYING_DICE:
			ui->Phase_->setText("PLAYING DICE");
			nbActions_.setText("");
			break;
		case Phase::PLAYING_EFFECT:
			ui->Phase_->setText("EFFECT");
			nbActions_.setText("");
			break;
		case Phase::PLAYING_MOVE:
			ui->Phase_->setText("PLAYING MOVE");
			nbActions_.setText(QString("Remaining actions : %1").arg(invade_.model().nbActions()));
			break;
		case Phase::PLAYING_COMMANDER:
			ui->Phase_->setText("PLAYING COMMANDER");
			nbActions_.setText(QString("Remaining actions : %1").arg(invade_.model().nbActions()));
			break;
		case Phase::PLAYING_ATTACK:
			ui->Phase_->setText("PLAYING ATTACK");
			nbActions_.setText(QString("Remaining actions : %1").arg(invade_.model().nbActions()));
			break;
		case Phase::END:
			ui->Phase_->setText("END");
			nbActions_.setText("");
			break;
		default:
			break;
	}
//	ui->statusBar->addWidget(nbActions_);
/*
	ORD->setPixmap(Images::dice(p.dice(DiceType::ORD), DiceTmp == ORD).scaled(ORD->width(), ORD->height(), Qt::KeepAspectRatio));
	ABS->setPixmap(Images::dice(p.dice(DiceType::ABS), DiceTmp == ABS).scaled(ABS->width(), ABS->height(), Qt::KeepAspectRatio));
	ATT->setPixmap(Images::dice(p.dice(DiceType::ATT), DiceTmp == ATT).scaled(ATT->width(), ATT->height(), Qt::KeepAspectRatio));
	COM->setPixmap(Images::dice(p.dice(DiceType::COM), DiceTmp == COM).scaled(COM->width(), COM->height(), Qt::KeepAspectRatio));
	EFF->setPixmap(Images::dice(p.dice(DiceType::EFF), DiceTmp == EFF).scaled(EFF->width(), EFF->height(), Qt::KeepAspectRatio));
	Arrows->setPixmap(Images::effArrows(p.dice(DiceType::EFF)));

	DEF->setPixmap(Images::dice(invade_.model().constPlayer(!invade_.model().current()).dice(DiceType::ATT)).scaled(DEF->width(), DEF->height(), Qt::KeepAspectRatio));

	Soldier->setPixmap(Images::pawn(UnitType::NORMAL, selectedUnitType == UnitType::NORMAL).scaled(Soldier->width(), Soldier->height(), Qt::KeepAspectRatio));
	EliteA->setPixmap(Images::pawn(UnitType::ELITE_A, selectedUnitType == UnitType::ELITE_A).scaled(EliteA->width(), EliteA->height(), Qt::KeepAspectRatio));
	EliteB->setPixmap(Images::pawn(UnitType::ELITE_B, selectedUnitType == UnitType::ELITE_B).scaled(EliteB->width(), EliteB->height(), Qt::KeepAspectRatio));
	EliteC->setPixmap(Images::pawn(UnitType::ELITE_C, selectedUnitType == UnitType::ELITE_C).scaled(EliteC->width(), EliteC->height(), Qt::KeepAspectRatio));

*/
	ORD->setPixmap(Images::dice(p.dice(DiceType::ORD), DiceTmp == ORD));
	ABS->setPixmap(Images::dice(p.dice(DiceType::ABS), DiceTmp == ABS));
	ATT->setPixmap(Images::dice(p.dice(DiceType::ATT), DiceTmp == ATT));
	COM->setPixmap(Images::dice(p.dice(DiceType::COM), DiceTmp == COM));
	EFF->setPixmap(Images::dice(p.dice(DiceType::EFF), DiceTmp == EFF));
	Arrows->setPixmap(Images::effArrows(p.dice(DiceType::EFF)));
	DEF->setPixmap(Images::dice(invade_.model().constPlayer(!invade_.model().current()).dice(DiceType::ATT)));

	Soldier->setPixmap(Images::pawn(UnitType::NORMAL, selectedUnitType == UnitType::NORMAL, invade_.side()));
	EliteA->setPixmap(Images::pawn(UnitType::ELITE_A, selectedUnitType == UnitType::ELITE_A, invade_.side()));
	EliteB->setPixmap(Images::pawn(UnitType::ELITE_B, selectedUnitType == UnitType::ELITE_B, invade_.side()));
	EliteC->setPixmap(Images::pawn(UnitType::ELITE_C, selectedUnitType == UnitType::ELITE_C, invade_.side()));

	SoldierValue->setText(QString::number(p.unit(UnitType::NORMAL)));
	EliteAValue->setText(QString::number(p.unit(UnitType::ELITE_A)));
	EliteBValue->setText(QString::number(p.unit(UnitType::ELITE_B)));
	EliteCValue->setText(QString::number(p.unit(UnitType::ELITE_C)));

	QFont font("Bavaria");
	font.setBold(invade_.model().canChooseEffect(Effect::NO_EFFECT) || invade_.model().hasEffect(Effect::NO_EFFECT));
	noEffect->setFont(font);
	font.setBold(invade_.model().canChooseEffect(Effect::INCREASED_MOVEMENT) || invade_.model().hasEffect(Effect::INCREASED_MOVEMENT));
	increasedMovement->setFont(font);
	font.setBold(invade_.model().canChooseEffect(Effect::INCREMENT_SOLDIER) || invade_.model().hasEffect(Effect::INCREMENT_SOLDIER));
	incrementSoldier->setFont(font);
	font.setBold(invade_.model().canChooseEffect(Effect::IMPROVED_ATTACK) || invade_.model().hasEffect(Effect::IMPROVED_ATTACK));
	improvedAttack->setFont(font);
	font.setBold(invade_.model().canChooseEffect(Effect::CHANGE_SOLDIER) || invade_.model().hasEffect(Effect::CHANGE_SOLDIER));
	changeSoldier->setFont(font);

	QPalette greenPalette;
	QPalette blackPalette;
	greenPalette.setColor(QPalette::WindowText,Qt::green);
	blackPalette.setColor(QPalette::WindowText,Qt::black);

	invade_.model().hasEffect(Effect::NO_EFFECT)? noEffect->setPalette(greenPalette): noEffect->setPalette(blackPalette);
	invade_.model().hasEffect(Effect::INCREASED_MOVEMENT)? increasedMovement->setPalette(greenPalette): increasedMovement->setPalette(blackPalette);
	invade_.model().hasEffect(Effect::INCREMENT_SOLDIER)? incrementSoldier->setPalette(greenPalette): incrementSoldier->setPalette(blackPalette);
	invade_.model().hasEffect(Effect::IMPROVED_ATTACK)? improvedAttack->setPalette(greenPalette): improvedAttack->setPalette(blackPalette);
	invade_.model().hasEffect(Effect::CHANGE_SOLDIER)? changeSoldier->setPalette(greenPalette): changeSoldier->setPalette(blackPalette);
}

InvadeUI::~InvadeUI() noexcept{
	QLayoutItem *child;
	while ((child = ui->Board_->takeAt(0)) != 0){
		delete child->widget();
	}
	while ((child = ui->diceLayout->takeAt(0)) != 0){
		delete child->widget();
	}
	while ((child = ui->pawnLayout->takeAt(0)) != 0){
		delete child->widget();
	}
	while ((child = ui->enemyLayout->takeAt(0)) != 0){
		delete child->widget();
	}
	while ((child = ui->effectLayout->takeAt(0)) != 0){
		delete child->widget();
	}
	delete ui;
}
