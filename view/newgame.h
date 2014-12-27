#ifndef NEWGAME_H
#define NEWGAME_H

#include <QDialog>
#include <string>

namespace Ui {
class newGame;
}

class newGame : public QDialog{
	Q_OBJECT
	std::string p1_;
	std::string p2_;

public:
	explicit newGame(QWidget *parent = 0);
	const std::string p1() const;
	const std::string p2() const;
	void setP1();
	void setP2();
	~newGame();

private:
	Ui::newGame *ui;
};

#endif // NEWGAME_H
