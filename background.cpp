#include "background.h"
#include<QPainter>
#include<QDebug>

Background::Background()
{

}
void Background::paintBackground(QImage &ima,Man &man,int (*sv)[25],
int (*brick)[25],QVector<Boom> qb,QPoint door,QVector<Monster> vm)
{
    //qDebug()<<"background";
    //背景图
    QImage image(750,510,QImage::Format_ARGB32);
    //画在image中
    QPainter p(&image);
    p.drawPixmap(0,0,750,510,QPixmap(":/new/image/background.jpg"));

    //画门
    if((brick[door.y()][door.x()])==0)
    {
        p.drawPixmap(door.x()*30,door.y()*30,30,30,QPixmap(":/new/image/door_t.jpg"));
    }
    //画砖
    for(int i=0;i<17;i++)
    {
        for(int j=0;j<25;j++)
        {
            if(brick[i][j]==1)
            {
                p.drawPixmap(j*30,i*30,QPixmap(":/new/image/brick.jpg"));
            }
            if(sv[i][j]==1)
            {
                p.drawPixmap(j*30,i*30,30,30,QPixmap(":/new/image/stone.jpg"));
            }
        }
    }
    //画玩家
    //qDebug()<<man.state<<"  "<<man.mx<<" "<<man.my<<endl;
    switch (man.state)
    {
    case 0:
        p.drawPixmap(man.mx,man.my,QPixmap(":/new/image/player_s1.jpg"));
        break;
    case 1:
        p.drawPixmap(man.mx,man.my,QPixmap(":/new/image/player_s2.jpg"));
        break;
    case 2:
        p.drawPixmap(man.mx,man.my,QPixmap(":/new/image/player_s3.jpg"));
        break;
    case 3:
        p.drawPixmap(man.mx,man.my,QPixmap(":/new/image/player_w1.jpg"));
        break;
    case 4:
        p.drawPixmap(man.mx,man.my,QPixmap(":/new/image/player_w2.jpg"));
        break;
    case 5:
        p.drawPixmap(man.mx,man.my,QPixmap(":/new/image/player_w3.jpg"));
        break;
    case 6:
        p.drawPixmap(man.mx,man.my,QPixmap(":/new/image/player_a1.jpg"));
        break;
    case 7:
        p.drawPixmap(man.mx,man.my,QPixmap(":/new/image/player_a2.jpg"));
        break;
    case 8:
        p.drawPixmap(man.mx,man.my,QPixmap(":/new/image/player_a3.jpg"));
        break;
    case 9:
        p.drawPixmap(man.mx,man.my,QPixmap(":/new/image/player_d1.jpg"));
        break;
    case 10:
        p.drawPixmap(man.mx,man.my,QPixmap(":/new/image/player_d2.jpg"));
        break;
    case 11:
        p.drawPixmap(man.mx,man.my,QPixmap(":/new/image/player_d3.jpg"));
        break;
    default:
        break;
    }
    //画炸弹
    for(auto it=qb.begin();it!=qb.end();it++)
    {
        int xl=it->x-30;
        int xr=it->x+30;
        int yu=it->y-30;
        int yd=it->y+30;
        switch (it->bState) {
        case 0:
            p.drawPixmap(it->x,it->y,30,30,QPixmap(":/new/image/bomb_burning1.jpg"));
            break;
        case 1:
            p.drawPixmap(it->x,it->y,30,30,QPixmap(":/new/image/bomb_burning2.jpg"));
            break;
        case 2:
            p.drawPixmap(it->x,it->y,30,30,QPixmap(":/new/image/bomb_burning3.jpg"));
            break;
        case 3:
            p.drawPixmap(it->x,it->y,30,30,QPixmap(":/new/image/bomb_mid_1.jpg"));
            if(sv[it->y/30][xl/30]!=1)
            {
                p.drawPixmap(xl,it->y,30,30,QPixmap(":/new/image/bomb_side_a_1.jpg"));
            }
            if(sv[it->y/30][xr/30]!=1)
            {
                p.drawPixmap(xr,it->y,30,30,QPixmap(":/new/image/bomb_side_d_1.jpg"));
            }
            if(sv[yu/30][it->x/30]!=1)
            {
                p.drawPixmap(it->x,yu,30,30,QPixmap(":/new/image/bomb_side_w_1.jpg"));
            }
            if(sv[yd/30][it->x/30]!=1)
            {
                p.drawPixmap(it->x,yd,30,30,QPixmap(":/new/image/bomb_side_s_1.jpg"));
            }
            //砖销毁
            if(brick[it->y/30][xl/30]==1)
                brick[it->y/30][xl/30]=0;
            if(brick[it->y/30][xr/30]==1)
                brick[it->y/30][xr/30]=0;
            if(brick[yu/30][it->x/30]==1)
                brick[yu/30][it->x/30]=0;
            if(brick[yd/30][it->x/30]==1)
                brick[yd/30][it->x/30]=0;
            //判断玩家是否死亡
            if(man.mx%30==15)
            {
                if((it->y==man.my)&&(xl==man.mx+15))
                    man.isLive=false;
                if((it->y==man.my)&&(xr==man.mx-15))
                    man.isLive=false;
            }else
            {
                if((it->y==man.my)&&xl==man.mx)
                    man.isLive=false;
                if((it->y==man.my)&&xr==man.mx)
                    man.isLive=false;
            }
            if(man.my%30==15)
            {
                if(yu==man.my+15&&it->x==man.mx)
                    man.isLive=false;
                if(yd==man.my-15&&it->x==man.mx)
                    man.isLive=false;
            }else
            {
                if(yu==man.my&&it->x==man.mx)
                    man.isLive=false;
                if(yd==man.my&&it->x==man.mx)
                    man.isLive=false;
            }

            break;
        case 4:
            p.drawPixmap(it->x,it->y,30,30,QPixmap(":/new/image/bomb_mid_2.jpg"));
            if(sv[it->y/30][xl/30]!=1)
            {
                p.drawPixmap(xl,it->y,30,30,QPixmap(":/new/image/bomb_side_a_2.jpg"));
            }
            if(sv[it->y/30][xr/30]!=1)
            {
                p.drawPixmap(xr,it->y,30,30,QPixmap(":/new/image/bomb_side_d_2.jpg"));
            }
            if(sv[yu/30][it->x/30]!=1)
            {
                p.drawPixmap(it->x,yu,30,30,QPixmap(":/new/image/bomb_side_w_2.jpg"));
            }
            if(sv[yd/30][it->x/30]!=1)
            {
                p.drawPixmap(it->x,yd,30,30,QPixmap(":/new/image/bomb_side_s_2.jpg"));
            }
            //判断玩家是否死亡
            if(man.mx%30==15)
            {
                if((it->y==man.my)&&(xl==man.mx+15))
                    man.isLive=false;
                if((it->y==man.my)&&(xr==man.mx-15))
                    man.isLive=false;
            }else
            {
                if((it->y==man.my)&&xl==man.mx)
                    man.isLive=false;
                if((it->y==man.my)&&xr==man.mx)
                    man.isLive=false;
            }
            if(man.my%30==15)
            {
                if(yu==man.my+15&&it->x==man.mx)
                    man.isLive=false;
                if(yd==man.my-15&&it->x==man.mx)
                    man.isLive=false;
            }else
            {
                if(yu==man.my&&it->x==man.mx)
                    man.isLive=false;
                if(yd==man.my&&it->x==man.mx)
                    man.isLive=false;
            }
            break;
        case 5:
            p.drawPixmap(it->x,it->y,30,30,QPixmap(":/new/image/bomb_mid_3.jpg"));
            if(sv[it->y/30][xl/30]!=1)
            {
                p.drawPixmap(xl,it->y,30,30,QPixmap(":/new/image/bomb_side_a_3.jpg"));
            }
            if(sv[it->y/30][xr/30]!=1)
            {
                p.drawPixmap(xr,it->y,30,30,QPixmap(":/new/image/bomb_side_d_3.jpg"));
            }
            if(sv[yu/30][it->x/30]!=1)
            {
                p.drawPixmap(it->x,yu,30,30,QPixmap(":/new/image/bomb_side_w_3.jpg"));
            }
            if(sv[yd/30][it->x/30]!=1)
            {
                p.drawPixmap(it->x,yd,30,30,QPixmap(":/new/image/bomb_side_s_3.jpg"));
            }
            //判断玩家是否死亡
            if(man.mx%30==15)
            {
                if((it->y==man.my)&&(xl==man.mx+15))
                    man.isLive=false;
                if((it->y==man.my)&&(xr==man.mx-15))
                    man.isLive=false;
            }else
            {
                if((it->y==man.my)&&xl==man.mx)
                    man.isLive=false;
                if((it->y==man.my)&&xr==man.mx)
                    man.isLive=false;
            }
            if(man.my%30==15)
            {
                if(yu==man.my+15&&it->x==man.mx)
                    man.isLive=false;
                if(yd==man.my-15&&it->x==man.mx)
                    man.isLive=false;
            }else
            {
                if(yu==man.my&&it->x==man.mx)
                    man.isLive=false;
                if(yd==man.my&&it->x==man.mx)
                    man.isLive=false;
            }
            break;
        case 6:
            p.drawPixmap(it->x,it->y,30,30,QPixmap(":/new/image/bomb_mid_4.jpg"));
            if(sv[it->y/30][xl/30]!=1)
            {
                p.drawPixmap(xl,it->y,30,30,QPixmap(":/new/image/bomb_side_a_4.jpg"));
            }
            if(sv[it->y/30][xr/30]!=1)
            {
                p.drawPixmap(xr,it->y,30,30,QPixmap(":/new/image/bomb_side_d_4.jpg"));
            }
            if(sv[yu/30][it->x/30]!=1)
            {
                p.drawPixmap(it->x,yu,30,30,QPixmap(":/new/image/bomb_side_w_4.jpg"));
            }
            if(sv[yd/30][it->x/30]!=1)
            {
                p.drawPixmap(it->x,yd,30,30,QPixmap(":/new/image/bomb_side_s_4.jpg"));
            }
            //判断玩家是否死亡
            if(man.mx%30==15)
            {
                if((it->y==man.my)&&(xl==man.mx+15))
                    man.isLive=false;
                if((it->y==man.my)&&(xr==man.mx-15))
                    man.isLive=false;
            }else
            {
                if((it->y==man.my)&&xl==man.mx)
                    man.isLive=false;
                if((it->y==man.my)&&xr==man.mx)
                    man.isLive=false;
            }
            if(man.my%30==15)
            {
                if(yu==man.my+15&&it->x==man.mx)
                    man.isLive=false;
                if(yd==man.my-15&&it->x==man.mx)
                    man.isLive=false;
            }else
            {
                if(yu==man.my&&it->x==man.mx)
                    man.isLive=false;
                if(yd==man.my&&it->x==man.mx)
                    man.isLive=false;
            }
            break;
        case 7:
            p.drawPixmap(it->x,it->y,30,30,QPixmap(":/new/image/bomb_mid_5.jpg"));
            if(sv[it->y/30][xl/30]!=1)
            {
                p.drawPixmap(xl,it->y,30,30,QPixmap(":/new/image/bomb_side_a_5.jpg"));
            }
            if(sv[it->y/30][xr/30]!=1)
            {
                p.drawPixmap(xr,it->y,30,30,QPixmap(":/new/image/bomb_side_d_5.jpg"));
            }
            if(sv[yu/30][it->x/30]!=1)
            {
                p.drawPixmap(it->x,yu,30,30,QPixmap(":/new/image/bomb_side_w_5.jpg"));
            }
            if(sv[yd/30][it->x/30]!=1)
            {
                p.drawPixmap(it->x,yd,30,30,QPixmap(":/new/image/bomb_side_s_5.jpg"));
            }
            //判断玩家是否死亡
            if(man.mx%30==15)
            {
                if((it->y==man.my)&&(xl==man.mx+15))
                    man.isLive=false;
                if((it->y==man.my)&&(xr==man.mx-15))
                    man.isLive=false;
            }else
            {
                if((it->y==man.my)&&xl==man.mx)
                    man.isLive=false;
                if((it->y==man.my)&&xr==man.mx)
                    man.isLive=false;
            }
            if(man.my%30==15)
            {
                if(yu==man.my+15&&it->x==man.mx)
                    man.isLive=false;
                if(yd==man.my-15&&it->x==man.mx)
                    man.isLive=false;
            }else
            {
                if(yu==man.my&&it->x==man.mx)
                    man.isLive=false;
                if(yd==man.my&&it->x==man.mx)
                    man.isLive=false;
            }
            break;

        default:
            break;
        }
    }

    //画怪物
    for(auto it=vm.begin();it!=vm.end();it++)
    {
         p.drawPixmap(it->mx,it->my,30,30,QPixmap(":/new/image/monster.png"));
    }

    ima=image;
}
