#ifndef DICELABEL_H
#define DICELABEL_H

#include <QLabel>
#include "../model/dicetype.h"

class DiceLabel : public QLabel{

Q_OBJECT
DiceType type_;

public:
	explicit DiceLabel( DiceType type, const QString& text ="", QWidget * parent = 0 );
	void setType(DiceType type);
	DiceType type();
	void setImage(unsigned value, bool selected = false);
	void setImageSelected(QString path);
	~DiceLabel();

signals:
	void clicked();

protected:
	void mousePressEvent ( QMouseEvent * ) ;
};


#endif // DICELABEL_H
