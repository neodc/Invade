#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>

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


#endif // CLICKABLELABEL_H
