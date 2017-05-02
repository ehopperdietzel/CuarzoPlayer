#include "opbutton.h"
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QPixmap>
#include <QBitmap>
#include <QPainter>

OpButton::OpButton(QString icon, int width, int height)
{
    setIcon(QIcon(icon));
    setIconSize(QSize(width,height));
    setStyleSheet("OpButton{background:transparent;border:none;}");
    setup();
}
OpButton::OpButton(QString icon, int width, int height, QString color)
{
    setIcon(QIcon(icon));
    setIconSize(QSize(width,height));
    setStyleSheet("OpButton{background:transparent;border:none;}");
    setColor(color);
    setup();
}
OpButton::OpButton(QString txt, QString style)
{
    setText(txt);
    setStyleSheet("OpButton{background:transparent;border:none;"+style+"}");
    setup();
}
OpButton::OpButton(QIcon ico)
{
    setIcon(ico);
    setStyleSheet("OpButton{background:transparent;border:none;}");
    setup();
}

void OpButton::setup(){
    opacity = new QGraphicsOpacityEffect();
    opacity->setOpacity(0.1);
    opacity->setOpacity(1);
    setGraphicsEffect(opacity);
    connect(this,SIGNAL(pressed()),this,SLOT(active()));
    connect(this,SIGNAL(released()),this,SLOT(inactive()));
}

void OpButton::active(){
    animation = new QPropertyAnimation(this, "opacityLevel");
    animation->setDuration(100);
    animation->setStartValue(1);
    animation->setEndValue(0.5);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void OpButton::inactive(){
    animation = new QPropertyAnimation(this, "opacityLevel");
    animation->setDuration(100);
    animation->setStartValue(0.5);
    animation->setEndValue(1);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    connect(animation,SIGNAL(finished()),this,SLOT(reset()));
}

void OpButton::reset(){
    this->opacity = new QGraphicsOpacityEffect();
    this->opacity->setOpacity(1);
    this->setGraphicsEffect(opacity);
}

void OpButton::setColor(QString color){
    QPixmap m = icon().pixmap(icon().actualSize(QSize(128, 128)));
    QPixmap newPix(m.size());
    newPix.fill(Qt::transparent);
    QBitmap mask = m.createMaskFromColor(Qt::black,Qt::MaskOutColor);
    QPainter p(&newPix);
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    p.setRenderHint(QPainter::Antialiasing);
    p.setBackgroundMode(Qt::TransparentMode);
    p.setPen(QColor(color));
    p.drawPixmap(newPix.rect(),mask,m.rect());
    p.end();
    setIcon(QIcon(newPix));
}
