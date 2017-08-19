#ifndef MONSTER_H
#define MONSTER_H


class Monster
{
public:
    Monster();
    Monster(int x,int y);

    int mx;
    int my;

    bool isLive;
    int state;
};

#endif // MONSTER_H
