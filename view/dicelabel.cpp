#include "dicelabel.h"

DiceLabel::DiceLabel(DiceType type, const QString& text, QWidget * parent ) : QLabel(parent){
	this->setText(text);
	type_ = type;
	this->setScaledContents(true);
}

DiceLabel::~DiceLabel(){
}


void DiceLabel::setType(DiceType type){
	type_ = type;
}

DiceType DiceLabel::type(){
	return type_;
}

void DiceLabel::setImage(unsigned value, bool selected){
	QString path = ":/new/images/";
	path.append(QString::number(value));
	path.append(".png");
	if (selected){
		setImageSelected(path);
	}else{
		QPixmap image(path);
		setPixmap(image);
	}
}

void DiceLabel::setImageSelected(QString path){
	QImage origin(path);
	QImage *newImage = new QImage(origin.width(), origin.height(), QImage::Format_ARGB32);

	QColor oldColor;
	int r,g,b;

	for(int x=0; x<newImage->width(); x++){
		for(int y=0; y<newImage->height(); y++){
			oldColor = QColor(origin.pixel(x,y));

			r = oldColor.red();
			g = oldColor.green();
			b = oldColor.blue() - 50;

			//we check if the new values are between 0 and 255
			r = qBound(0, r, 255);
			g = qBound(0, g, 255);

			newImage->setPixel(x,y, qRgb(r,g,b));
		}
	}

	QPixmap pix;
	pix.convertFromImage(*newImage);
	setPixmap(pix);
}

void DiceLabel::mousePressEvent ( QMouseEvent * ){
	emit clicked();
}
