#include "invadeui.h"
#include "ui_invadeui.h"

InvadeUI::InvadeUI(QWidget *parent) : QMainWindow(parent), ui(new Ui::InvadeUI){
	ui->setupUi(this);
}


void InvadeUI::rafraichir(SujetDObservation *){

}

InvadeUI::~InvadeUI() noexcept{
	delete ui;
}
