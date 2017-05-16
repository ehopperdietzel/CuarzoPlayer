#ifndef ALBUM_H
#define ALBUM_H

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include "croplabel.h"
#include "opbutton.h"
#include "albumsong.h"
#include "pix.h"
#include "json.hpp"


using json = nlohmann::json;

extern QString blue;

class Album:public QWidget
{
    Q_OBJECT
public:
    Album(int _id, json _data);
    Pix p;
    int id;
    json data;
    QWidget *artWorkFrame = new QWidget();
    QWidget *artWorkBottomFrame = new QWidget();
    QWidget *nameFrame = new QWidget();
    QWidget *rightFrame = new QWidget();
    QWidget *songsFrame= new QWidget();
    QFrame *infoFrame = new QFrame();

    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight,this);
    QBoxLayout *artWorkLayout = new QBoxLayout(QBoxLayout::TopToBottom,artWorkFrame);
    QBoxLayout *artWorkBottomLayout = new QBoxLayout(QBoxLayout::LeftToRight,artWorkBottomFrame);
    QBoxLayout *songsLayout = new QBoxLayout(QBoxLayout::TopToBottom,songsFrame);

    QBoxLayout *rightLayout = new QBoxLayout(QBoxLayout::TopToBottom,rightFrame);
    QBoxLayout *infoLayout = new QBoxLayout(QBoxLayout::LeftToRight,infoFrame);
    QBoxLayout *nameLayout = new QBoxLayout(QBoxLayout::TopToBottom,nameFrame);

    QLabel *artWork = new QLabel();
    CropLabel *albumName;
    CropLabel *albumInfo;
    QLabel *songsNumber = new QLabel();

    OpButton *shuffle = new OpButton(":res/img/shuffle.svg",20,20,blue);
    OpButton *more = new OpButton(":res/img/more.svg",20,20,blue);
    OpButton *sync = new OpButton(":res/img/sync-border.svg",20,20,blue);

    AlbumSong *songs[2048] = {nullptr};

signals:
    void songSelected(int);
    void songPlayed(json);

public slots:
    void sendSelectedSong(int);
    void sendPlayedSong(json);
    void setData(json);


};



#endif // ALBUM_H