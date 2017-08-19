#include "monster.h"

Monster::Monster()
{

}
Monster::Monster(int x, int y)
{
    this->mx=x;
    this->my=y;
    isLive=true;
    state=0;
}
