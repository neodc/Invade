#ifndef TILELABEL_H
#define TILELABEL_H

#include <QLabel>
#include "view/images.h"

class TileLabel : public QLabel
{

Q_OBJECT

public:
	explicit TileLabel( const QString& text ="", QWidget * parent = 0 );
	~TileLabel();

signals:
	void clicked();

protected:
	void mousePressEvent ( QMouseEvent * ) ;
};


#endif // TILELABEL_H
