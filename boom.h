#ifndef BOOM_H
#define BOOM_H

#include<QTimer>


class Boom
{
public:
    Boom();
    Boom(int x,int y,int bState);

public:
    int bState;
    int x;
    int y;
};

#endif // BOOM_H
