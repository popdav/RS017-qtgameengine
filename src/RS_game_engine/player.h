#ifndef PLAYER_H
#define PLAYER_H

#include "gamecomponent.h"
#include <QPixmap>
#include <QToolBox>
#include <QLineEdit>
#include <QPushButton>


class Player : public GameComponent
{
    Q_OBJECT
public:
    Player(qreal x, qreal y, qreal width, qreal height, QString look,
           QToolBox* componentInfo,QList<QLineEdit*> playerInfo, QPushButton* playerUpdate);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void advance(int step) override;
    void move(qreal delta_x, qreal delta_y);
    qreal getHeight();
    qreal getWidth();

private slots:
    void pbApply() override;

private:
    QPixmap look;
    QToolBox* componentInfo;
    QList<QLineEdit*> playerInfo;
    QPushButton* playerUpdate;

};

#endif // PLAYER_H
