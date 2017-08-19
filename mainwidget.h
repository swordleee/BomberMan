#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include"background.h"
#include"man.h"
#include"boom.h"
#include"monster.h"
#include <QWidget>
#include<QVector>
#include<QTimer>
#include<QPoint>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

    //绘图事件
    void paintEvent(QPaintEvent *event);
    //鼠标按下事件
    void keyPressEvent(QKeyEvent *event);
    //钢砖的位置
    void positionOfStone(int (*sv)[25]);
    //玩家活动范围
    bool playerIsMove(Man &man,int (*sv)[25],int (*brick)[25]);
    //砖是否能放
    bool IsOk(Man man, int (*sv)[25],int (*brick)[25],int x,int y);
    //怪移动
    void MonsterIsMove();
    //怪物活动区域
    bool MonsterOfSpace(int x,int y,int st);
    //炸弹是否炸死怪物
    void MonsterOfDeath();

private:
    Ui::MainWidget *ui;

    QImage image;
    Background bg;//背景对象
    Man man;//玩家对象
    int sv[17][25];//定义一个钢砖二维数组
    int brick[17][25];//定义墙的二维数组
    QVector<Boom> qb;//创建一个炸弹队列
    QTimer *qt;//创建一个定时器
    QPoint door;//定义一个门
    QVector<Monster> vm;//怪物数组
    QTimer *qt1;//创建一个怪物定时器
};

#endif // MAINWIDGET_H
