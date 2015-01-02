#include "invadeui.h"
#include "ui_invadeui.h"

#include <QMessageBox>

InvadeUI::InvadeUI(QString name, QString host, int port, QWidget *parent) : QMainWindow(parent), ui(new Ui::InvadeUI){
	ui->setupUi(this);

	invade_.connectToHost(host, port);

	TileLabel * label;

	for(unsigned i = 0; i < invade_.model().board().dimensions().x; i++){
		for(unsigned j = 0; j < invade_.model().board().dimensions().y; j++){
			label = new TileLabel();
			ui->Board_->addWidget(label,j,i);
			connect(label, &TileLabel::leftClicked, this, &InvadeUI::unitAction);
			connect(label, &TileLabel::rightClicked, this, &InvadeUI::rightUnitAction);
		}
	}
	ui->statusBar->addWidget(&nbActions_);
	ui->statusBar->addWidget(&warning_);

	COM = new DiceLabel(DiceType::COM, 48);
	ABS = new DiceLabel(DiceType::ABS, 48);
	ORD = new DiceLabel(DiceType::ORD, 48);
	EFF = new DiceLabel(DiceType::EFF, 48);
	ATT = new DiceLabel(DiceType::ATT, 48);
//	DEF = new DiceLabel(DiceType::ATT, 48);
	labelCOM = new QLabel("COM");
	labelABS = new QLabel("ABS");
	labelORD = new QLabel("ORD");
	labelEFF = new QLabel("EFF");
	labelATT = new QLabel("ATT");
//	labelDEF = new QLabel("DEF");
	Arrows = new QLabel(this);
	Arrows->setScaledContents(true);
	Arrows->setMaximumSize(QSize(48, 48));

	Soldier = new EliteLabel(UnitType::NORMAL, 40);
	EliteA = new EliteLabel(UnitType::ELITE_A, 40);
	EliteB = new EliteLabel(UnitType::ELITE_B, 40);
	EliteC = new EliteLabel(UnitType::ELITE_C, 40);

	SoldierValue = new QLabel(this);
	EliteAValue = new QLabel(this);
	EliteBValue = new QLabel(this);
	EliteCValue = new QLabel(this);

	COMenemy = new DiceLabel(DiceType::COM, 32);
	ABSenemy = new DiceLabel(DiceType::ABS, 32);
	ORDenemy = new DiceLabel(DiceType::ORD, 32);
	EFFenemy = new DiceLabel(DiceType::EFF, 32);
	ATTenemy = new DiceLabel(DiceType::ATT, 32);
//	DEFenemy = new DiceLabel(DiceType::ATT, 32);
	labelCOMenemy = new QLabel("COM");
	labelABSenemy = new QLabel("ABS");
	labelORDenemy = new QLabel("ORD");
	labelEFFenemy = new QLabel("EFF");
	labelATTenemy = new QLabel("ATT");
//	labelDEFenemy = new QLabel("DEF");
	ArrowsEnemy = new QLabel(this);
	ArrowsEnemy->setScaledContents(true);
	ArrowsEnemy->setMaximumSize(QSize(32, 32));

	SoldierEnemy = new EliteLabel(UnitType::NORMAL, 27);
	EliteAEnemy = new EliteLabel(UnitType::ELITE_A, 27);
	EliteBEnemy = new EliteLabel(UnitType::ELITE_B, 27);
	EliteCEnemy = new EliteLabel(UnitType::ELITE_C, 27);

	SoldierValueEnemy = new QLabel(this);
	EliteAValueEnemy = new QLabel(this);
	EliteBValueEnemy = new QLabel(this);
	EliteCValueEnemy = new QLabel(this);

	noEffect = new EffectLabel(Effect::NO_EFFECT, "No effect");
	increasedMovement = new EffectLabel(Effect::INCREASED_MOVEMENT, "Increase movements");
	incrementSoldier = new EffectLabel(Effect::INCREMENT_SOLDIER, "Increment soldier");
	improvedAttack = new EffectLabel(Effect::IMPROVED_ATTACK, "Improve attacks");
	changeSoldier = new EffectLabel(Effect::CHANGE_SOLDIER, "Promote soldier");

	connect(ui->Next_, &QPushButton::clicked, this, &InvadeUI::nextPhase);
	connect(ui->actionQuit, &QAction::triggered, this, &InvadeUI::quit);
	connect(ui->actionNew_Game, &QAction::triggered, this, &InvadeUI::begin);

	connect(COM, &DiceLabel::leftClicked, this, &InvadeUI::swapDice);
	connect(ABS, &DiceLabel::leftClicked, this, &InvadeUI::swapDice);
	connect(ORD, &DiceLabel::leftClicked, this, &InvadeUI::swapDice);
	connect(EFF, &DiceLabel::leftClicked, this, &InvadeUI::swapDice);
	connect(ATT, &DiceLabel::leftClicked, this, &InvadeUI::swapDice);

	connect(Soldier, &EliteLabel::clicked, this, &InvadeUI::selectUnit);
	connect(EliteA, &EliteLabel::clicked, this, &InvadeUI::selectUnit);
	connect(EliteB, &EliteLabel::clicked, this, &InvadeUI::selectUnit);
	connect(EliteC, &EliteLabel::clicked, this, &InvadeUI::selectUnit);

	connect(noEffect, &EffectLabel::clicked, this, &InvadeUI::chooseEffect);
	connect(increasedMovement, &EffectLabel::clicked, this, &InvadeUI::chooseEffect);
	connect(incrementSoldier, &EffectLabel::clicked, this, &InvadeUI::chooseEffect);
	connect(improvedAttack, &EffectLabel::clicked, this, &InvadeUI::chooseEffect);
	connect(changeSoldier, &EffectLabel::clicked, this, &InvadeUI::chooseEffect);


	ui->diceLayout->addWidget(COM, 1, 1);
	ui->diceLayout->addWidget(ABS, 2, 0);
	ui->diceLayout->addWidget(ORD, 2, 2);
	ui->diceLayout->addWidget(EFF, 3, 0);
	ui->diceLayout->addWidget(ATT, 3, 2);
//	ui->diceLayout->addWidget(DEF, 0, 1, 4, 1);
	ui->diceLayout->addWidget(Arrows, 2, 1);

	ui->diceLayout->addWidget(labelCOM, 0, 1);
	ui->diceLayout->addWidget(labelABS, 1, 0);
	ui->diceLayout->addWidget(labelORD, 1, 2);
	ui->diceLayout->addWidget(labelEFF, 4, 0);
	ui->diceLayout->addWidget(labelATT, 4, 2);
//	ui->diceLayout->addWidget(labelDEF, 0, 0, 4, 1);
	labelCOM->setAlignment(Qt::AlignCenter | Qt::AlignBottom);
	labelABS->setAlignment(Qt::AlignCenter| Qt::AlignBottom);
	labelORD->setAlignment(Qt::AlignCenter| Qt::AlignBottom);
	labelEFF->setAlignment(Qt::AlignCenter| Qt::AlignTop);
	labelATT->setAlignment(Qt::AlignCenter| Qt::AlignTop);
//	labelDEF->setAlignment(Qt::AlignCenter| Qt::AlignHCenter);
//	DEF->setAlignment(Qt::AlignCenter| Qt::AlignHCenter);

	ui->pawnLayout->addWidget(Soldier, 0, 0);
	ui->pawnLayout->addWidget(SoldierValue, 0, 1);
	ui->pawnLayout->addWidget(EliteA, 1, 0);
	ui->pawnLayout->addWidget(EliteAValue, 1, 1);
	ui->pawnLayout->addWidget(EliteB, 2, 0);
	ui->pawnLayout->addWidget(EliteBValue, 2, 1);
	ui->pawnLayout->addWidget(EliteC, 3, 0);
	ui->pawnLayout->addWidget(EliteCValue, 3, 1);
/*	Soldier->setAlignment(Qt::AlignCenter);
	SoldierValue->setAlignment(Qt::AlignCenter);
	EliteA->setAlignment(Qt::AlignCenter);
	EliteAValue->setAlignment(Qt::AlignCenter);
	EliteB->setAlignment(Qt::AlignCenter);
	EliteBValue->setAlignment(Qt::AlignCenter);
	EliteC->setAlignment(Qt::AlignCenter);
	EliteCValue->setAlignment(Qt::AlignCenter);*/

	ui->diceEnemyLayout->addWidget(COMenemy, 1, 1);
	ui->diceEnemyLayout->addWidget(ABSenemy, 2, 0);
	ui->diceEnemyLayout->addWidget(ORDenemy, 2, 2);
	ui->diceEnemyLayout->addWidget(EFFenemy, 3, 0);
	ui->diceEnemyLayout->addWidget(ATTenemy, 3, 2);
//	ui->diceEnemyLayout->addWidget(DEFenemy, 0, 1);
	ui->diceEnemyLayout->addWidget(ArrowsEnemy, 2, 1);

	ui->diceEnemyLayout->addWidget(labelCOMenemy, 0, 1);
	ui->diceEnemyLayout->addWidget(labelABSenemy, 1, 0);
	ui->diceEnemyLayout->addWidget(labelORDenemy, 1, 2);
	ui->diceEnemyLayout->addWidget(labelEFFenemy, 4, 0);
	ui->diceEnemyLayout->addWidget(labelATTenemy, 4, 2);
//	ui->diceEnemyLayout->addWidget(labelDEFenemy, 0, 0);
	labelCOMenemy->setAlignment(Qt::AlignCenter | Qt::AlignBottom);
	labelABSenemy->setAlignment(Qt::AlignCenter| Qt::AlignBottom);
	labelORDenemy->setAlignment(Qt::AlignCenter| Qt::AlignBottom);
	labelEFFenemy->setAlignment(Qt::AlignCenter| Qt::AlignTop);
	labelATTenemy->setAlignment(Qt::AlignCenter| Qt::AlignTop);
//	labelDEFenemy->setAlignment(Qt::AlignCenter| Qt::AlignHCenter);

	ui->pawnEnemyLayout->addWidget(SoldierEnemy, 0, 0);
	ui->pawnEnemyLayout->addWidget(SoldierValueEnemy, 0, 1);
	ui->pawnEnemyLayout->addWidget(EliteAEnemy, 1, 0);
	ui->pawnEnemyLayout->addWidget(EliteAValueEnemy, 1, 1);
	ui->pawnEnemyLayout->addWidget(EliteBEnemy, 0, 2);
	ui->pawnEnemyLayout->addWidget(EliteBValueEnemy, 0, 3);
	ui->pawnEnemyLayout->addWidget(EliteCEnemy, 1, 2);
	ui->pawnEnemyLayout->addWidget(EliteCValueEnemy, 1, 3);

	ui->effectLayout->addWidget(noEffect, 0, 0);
	ui->effectLayout->addWidget(increasedMovement, 1, 0);
	ui->effectLayout->addWidget(incrementSoldier, 2, 0);
	ui->effectLayout->addWidget(improvedAttack, 3, 0);
	ui->effectLayout->addWidget(changeSoldier, 4, 0);

	invade_.attacher(this);
	invade_.name(name);
	rafraichir(nullptr);
}

void InvadeUI::nextPhase(){
	if (invade_.model().phase() == Phase::PLAYING_EFFECT && invade_.model().effects().empty()){
		invade_.chooseEffect(Effect::NO_EFFECT);
	}
	invade_.endPhase();
	PosTmp = Position{100,100};
	DiceTmp = NULL;
}

void InvadeUI::quit(){
	exit(0);
}

void InvadeUI::swapDice(){
	QWidget * Widget = qobject_cast<QWidget*>(sender());
	if (!Widget || invade_.model().current() != invade_.side()){
	   return;
	}

	if (DiceTmp == NULL){
		DiceTmp = dynamic_cast<DiceLabel*>(Widget);
	}else{
		DiceLabel * sender = dynamic_cast<DiceLabel*>(Widget);
		invade_.swapDice(DiceTmp->type(),sender->type());
		DiceTmp = NULL;
	}
	rafraichir(nullptr);
}

void InvadeUI::chooseEffect(){
	QWidget * Widget = qobject_cast<QWidget*>(sender());
	if (!Widget){
	   return;
	}
	EffectLabel * sender = dynamic_cast<EffectLabel*>(Widget);
	invade_.chooseEffect(sender->type(), selectedUnitType);
}

void InvadeUI::begin(){
	invade_.newGame(); // TODO ajouter un message ?
}


void InvadeUI::selectUnit(){
	QWidget * Widget = qobject_cast<QWidget*>(sender());
	if (!Widget){
	   return;
	}
	EliteLabel * sender = dynamic_cast<EliteLabel*>(Widget);
	selectedUnitType = sender->type().type();
	rafraichir(nullptr);
}

void InvadeUI::unitAction(){
	QWidget * Widget = qobject_cast<QWidget*>(sender());
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
	QWidget * Widget = qobject_cast<QWidget*>(sender());
	if (!Widget){
	   return;
	}
	int index = ui->Board_->indexOf(Widget);
	int rowOfButton, columnOfButton, rowSpanOfButton, columnSpanOfButton;
	ui->Board_->getItemPosition(index, &rowOfButton, &columnOfButton, &rowSpanOfButton, &columnSpanOfButton);
	unsigned x = columnOfButton;
	unsigned y = rowOfButton;
	if (invade_.model().phase() == Phase::PLAYING_ATTACK && !invade_.model().board().isCaseEmpty(Position{x,y})){
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
		invade_.attack(PosTmp, sender, bombshell);
		PosTmp = Position{100,100};
	}
}

void InvadeUI::rightAttack(Position sender){
		attack(sender, true);
}

void InvadeUI::refreshStat(){
	bool clientTurn = invade_.model().current() == invade_.side();
	Player p = invade_.model().constPlayer(invade_.side());
	Player o = invade_.model().constPlayer(!invade_.side());
//	QSize sp(clientTurn? 54 : 27, clientTurn? 54 : 27);
//	QSize so(clientTurn? 27 : 54, clientTurn? 27 : 54);

	COM->setEnabled(clientTurn);
	ABS->setEnabled(clientTurn);
	ORD->setEnabled(clientTurn);
	EFF->setEnabled(clientTurn);
//	ATT->setEnabled(clientTurn);
//	DEF->setEnabled(!clientTurn);

	labelCOM->setEnabled(clientTurn);
	labelABS->setEnabled(clientTurn);
	labelORD->setEnabled(clientTurn);
	labelEFF->setEnabled(clientTurn);
//	labelATT->setEnabled(clientTurn);
	labelATT->setText(clientTurn? "ATT" : "DEF");
//	labelDEF->setEnabled(!clientTurn);

	COMenemy->setEnabled(!clientTurn);
	ABSenemy->setEnabled(!clientTurn);
	ORDenemy->setEnabled(!clientTurn);
	EFFenemy->setEnabled(!clientTurn);
//	ATTenemy->setEnabled(!clientTurn);
//	DEFenemy->setEnabled(clientTurn);

	labelCOMenemy->setEnabled(!clientTurn);
	labelABSenemy->setEnabled(!clientTurn);
	labelORDenemy->setEnabled(!clientTurn);
	labelEFFenemy->setEnabled(!clientTurn);
//	labelATTenemy->setEnabled(!clientTurn);
	labelATTenemy->setText(clientTurn? "DEF" : "ATT");
//	labelDEFenemy->setEnabled(clientTurn);

	Arrows->setVisible(clientTurn);
	ArrowsEnemy->setVisible(!clientTurn);

	Soldier->setPixmap(Images::pawn(UnitType::NORMAL, selectedUnitType == UnitType::NORMAL, invade_.side()));
	EliteA->setPixmap(Images::pawn(UnitType::ELITE_A, selectedUnitType == UnitType::ELITE_A, invade_.side()));
	EliteB->setPixmap(Images::pawn(UnitType::ELITE_B, selectedUnitType == UnitType::ELITE_B, invade_.side()));
	EliteC->setPixmap(Images::pawn(UnitType::ELITE_C, selectedUnitType == UnitType::ELITE_C, invade_.side()));

	SoldierValue->setText(QString::number(p.unit(UnitType::NORMAL)));
	EliteAValue->setText(QString::number(p.unit(UnitType::ELITE_A)));
	EliteBValue->setText(QString::number(p.unit(UnitType::ELITE_B)));
	EliteCValue->setText(QString::number(p.unit(UnitType::ELITE_C)));

	SoldierEnemy->setPixmap(Images::pawn(UnitType::NORMAL, false, !invade_.side()));
	EliteAEnemy->setPixmap(Images::pawn(UnitType::ELITE_A, false, !invade_.side()));
	EliteBEnemy->setPixmap(Images::pawn(UnitType::ELITE_B, false, !invade_.side()));
	EliteCEnemy->setPixmap(Images::pawn(UnitType::ELITE_C, false, !invade_.side()));

	SoldierValueEnemy->setText(QString::number(o.unit(UnitType::NORMAL)));
	EliteAValueEnemy->setText(QString::number(o.unit(UnitType::ELITE_A)));
	EliteBValueEnemy->setText(QString::number(o.unit(UnitType::ELITE_B)));
	EliteCValueEnemy->setText(QString::number(o.unit(UnitType::ELITE_C)));

/*	Soldier->setMaximumSize(sp);
	EliteA->setMaximumSize(sp);
	EliteB->setMaximumSize(sp);
	EliteC->setMaximumSize(sp);

	SoldierEnemy->setMaximumSize(so);
	EliteAEnemy->setMaximumSize(so);
	EliteBEnemy->setMaximumSize(so);
	EliteCEnemy->setMaximumSize(so);*/

//	if(clientTurn){
	//	connect(ATT, &DiceLabel::leftClicked, this, &InvadeUI::swapDice);
		COM->setPixmap(Images::dice(p.dice(DiceType::COM), DiceTmp == COM));
		ABS->setPixmap(Images::dice(p.dice(DiceType::ABS), DiceTmp == ABS));
		ORD->setPixmap(Images::dice(p.dice(DiceType::ORD), DiceTmp == ORD));
		EFF->setPixmap(Images::dice(p.dice(DiceType::EFF), DiceTmp == EFF));
		ATT->setPixmap(Images::dice(p.dice(DiceType::ATT), DiceTmp == ATT));
//		ATTenemy->setPixmap(Images::dice(o.dice(DiceType::ATT)));
		Arrows->setPixmap(Images::effArrows(p.dice(DiceType::EFF)));
//	} else {
	//	disconnect(ATT, 0, 0, 0);
		COMenemy->setPixmap(Images::dice(o.dice(DiceType::COM)));
		ABSenemy->setPixmap(Images::dice(o.dice(DiceType::ABS)));
		ORDenemy->setPixmap(Images::dice(o.dice(DiceType::ORD)));
		EFFenemy->setPixmap(Images::dice(o.dice(DiceType::EFF)));
		ATTenemy->setPixmap(Images::dice(o.dice(DiceType::ATT)));
//		ATT->setPixmap(Images::dice(p.dice(DiceType::ATT)));
		ArrowsEnemy->setPixmap(Images::effArrows(o.dice(DiceType::EFF)));
//	}
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
		ui->centralWidget->setVisible(false);
		warning_.setText("Waiting for opponent");
		return;
	}else{
		ui->centralWidget->setVisible(true);
		warning_.setText("");
	}
	ui->Next_->setEnabled(invade_.model().current() == invade_.side());
	ui->Base_->setTitle(QString::fromStdString(invade_.model().constPlayer(invade_.side()).name()));
	ui->Enemy_->setTitle(QString::fromStdString(invade_.model().constPlayer(!invade_.side()).name()));
	Player p {invade_.model().constPlayer(invade_.model().current())};
	TileLabel * tile;
	bool check = false;

	for(unsigned i = 0; i < invade_.model().board().dimensions().x; i++){
		for(unsigned j = 0; j < invade_.model().board().dimensions().y; j++){
			if(PosTmp != Position{100, 100}){
				check = (	(invade_.model().phase() == Phase::PLAYING_MOVE && invade_.model().canMove(PosTmp, Position{i,j}))
						||	(invade_.model().phase() == Phase::PLAYING_COMMANDER && invade_.model().canMoveCommander(PosTmp, Position{i,j}))
						||	(invade_.model().phase() == Phase::PLAYING_ATTACK && invade_.model().canAttack(PosTmp, Position{i,j}))
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

	ui->PhaseDice_->setEnabled(false);
	ui->PhaseEffect_->setEnabled(false);
	ui->PhaseMove_->setEnabled(false);
	ui->PhaseAttack_->setEnabled(false);
	ui->PhaseEnd_->setEnabled(false);

	switch (invade_.model().phase()) {
		case Phase::NO_PLAYER:
			nbActions_.setText("");
			break;
		case Phase::PLAYING_DICE:
			ui->PhaseDice_->setEnabled(true);
			nbActions_.setText("");
			break;
		case Phase::PLAYING_EFFECT:
			ui->PhaseEffect_->setEnabled(true);
			nbActions_.setText("");
			break;
		case Phase::PLAYING_MOVE:
			ui->PhaseMove_->setEnabled(true);
			ui->PhaseMove_->setText("Move Soldiers >");
			nbActions_.setText(QString("Remaining actions : %1").arg(invade_.model().nbActions()));
			break;
		case Phase::PLAYING_COMMANDER:
			ui->PhaseMove_->setEnabled(true);
			ui->PhaseMove_->setText("Move Soldiers (Commander) >");
			nbActions_.setText(QString("Remaining actions : %1").arg(invade_.model().nbActions()));
			break;
		case Phase::PLAYING_ATTACK:
			ui->PhaseAttack_->setEnabled(true);
			nbActions_.setText(QString("Remaining actions : %1").arg(invade_.model().nbActions()));
			break;
		case Phase::END:
			ui->PhaseEnd_->setEnabled(true);
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
	refreshStat();

	QFont font("Bavaria");
	font.setBold(invade_.model().canChooseEffect(Effect::NO_EFFECT, selectedUnitType) || invade_.model().hasEffect(Effect::NO_EFFECT));
	noEffect->setFont(font);
	font.setBold(invade_.model().canChooseEffect(Effect::INCREASED_MOVEMENT, selectedUnitType) || invade_.model().hasEffect(Effect::INCREASED_MOVEMENT));
	increasedMovement->setFont(font);
	font.setBold(invade_.model().canChooseEffect(Effect::INCREMENT_SOLDIER, selectedUnitType) || invade_.model().hasEffect(Effect::INCREMENT_SOLDIER));
	incrementSoldier->setFont(font);
	font.setBold(invade_.model().canChooseEffect(Effect::IMPROVED_ATTACK, selectedUnitType) || invade_.model().hasEffect(Effect::IMPROVED_ATTACK));
	improvedAttack->setFont(font);
	font.setBold(invade_.model().canChooseEffect(Effect::CHANGE_SOLDIER, selectedUnitType) || invade_.model().hasEffect(Effect::CHANGE_SOLDIER));
	changeSoldier->setFont(font);

	QPalette greenPalette;
	QPalette blackPalette;
	greenPalette.setColor(QPalette::WindowText,Qt::green);
	//blackPalette.setColor(QPalette::WindowText,Qt::DefaultContextMenu);

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
