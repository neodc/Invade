#ifndef TILELABEL_H
#define TILELABEL_H

#include <QLabel>
#include <QMouseEvent>
#include "view/images.h"

class TileLabel : public QLabel
{

Q_OBJECT

public:
	explicit TileLabel(QWidget * parent = 0 );
	~TileLabel();

signals:
	void leftClicked();
	void rightClicked();

protected:
	void mousePressEvent ( QMouseEvent * event) ;
};


#endif // TILELABEL_H
