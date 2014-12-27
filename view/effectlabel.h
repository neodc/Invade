#ifndef EFFECTLABEL_H
#define EFFECTLABEL_H

#include <QLabel>
#include "../model/effect.h"

class EffectLabel : public QLabel{

Q_OBJECT
Effect type_;

public:
	explicit EffectLabel(Effect type, const QString& text ="", QWidget * parent = 0 );
	void setType(Effect type);
	Effect type();
	~EffectLabel();

signals:
	void clicked();

protected:
	void mousePressEvent ( QMouseEvent * ) ;
};


#endif // EFFECTLABEL_H
