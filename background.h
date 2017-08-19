#ifndef BACKGROUND_H
#define BACKGROUND_H

#include"man.h"
#include"boom.h"
#include"monster.h"
#include<QImage>
#include<QVector>
#include<QPoint>

class Background
{
public:
    Background();

    void paintBackground(QImage &ima,Man &man,int (*sv)[25],int (*brick)[25],
                        QVector<Boom> qb,QPoint door,QVector<Monster> vm);


};

#endif // BACKGROUND_H
