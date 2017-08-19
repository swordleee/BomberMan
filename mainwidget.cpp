#include "mainwidget.h"
#include "ui_mainwidget.h"
#include<QPainter>
#include<QDebug>
#include<QKeyEvent>
#include<ctime>
#include<QMessageBox>


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    this->move(200,100);
    setFixedSize(750,510);
    setWindowTitle("炸弹人");
    setWindowIcon(QPixmap(":/new/image/2.png"));
    //初始化二维数组
    //sv=(int *)malloc(sizeof(sv));
    memset(sv,0,sizeof(sv));
    positionOfStone(sv);

    memset(brick,0,sizeof(brick)); 
    //随机产生50块砖5个怪物
    srand((unsigned int)time(NULL));
    //从砖中随机挑出一块放置门
    int doorpoint=rand()%50;
    int bx,by;
    for(int i=0;i<55;i++)
    {
        bx=rand()%23+1;
        by=rand()%15+1;
        //判断此处有没有人或者砖
        if(IsOk(man,sv,brick,bx,by)==false)
        {
            i--;
        }else
        {
            if(i<50)
                brick[by][bx]=1;
            else
            {
                Monster m(bx*30,by*30);
                vm.push_back(m);
            }
        }
        if(i==doorpoint)
        {
            door.setX(bx);
            door.setY(by);
        }
    }


    qDebug()<<"door "<<door.x()<<"  "<<door.y();

    //怪移动
    qt1=new QTimer(this);
    qt1->start(300);
    connect(qt1,&QTimer::timeout,
            [=]()
    {
        MonsterIsMove();
        MonsterOfDeath();
        update();

    });

     qt=new QTimer(this);
     connect(qt,&QTimer::timeout,
             [=]()
     {
         while(qb.size()!=0)
         {
             auto it=qb.begin();
             for(;it!=qb.end();it++)
             {
                 if(it->bState==8)
                 {
                     qb.erase(it);
                     it++;
                     break;
                 }
                 else
                 {
                     it->bState++;
                 }
             }
             if(it==qb.end())
             {
                 break;
             }
         }
         if(qb.size()==0)
         {
             if(man.isLive==false||man.isWin==true)
             {
                 qt->stop();
             }
         }else
         {
             update();
         }
     });
}

//怪移动
void MainWidget::MonsterIsMove()
{
    if(vm.empty()==true||man.isWin==true)
    {
        qt1->stop();
    }
    //怪改变位置
    for(auto it=vm.begin();it!=vm.end();it++)
    {
        int st=it->state;
        int x=it->mx;
        int y=it->my;
        st=rand()%10;
        if(st==0)//向上
        {
            it->state=st;
            y-=15;
        }
        else if(st==1)//向下
        {
            it->state=st;
            y+=15;
        }
        else if(st==2)//向左
        {
            it->state=st;
            x-=15;
        }
        else if(st==3)//向右
        {
            it->state=st;
            x+=15;
        }
        else
        {
            switch (it->state) {
            case 0:
               y-=15;
                break;
            case 1:
               y+=15;
                break;
            case 2:
               x-=15;
                break;
            case 3:
               x+=15;
                break;
            default:
                break;
            }
        }
        if(MonsterOfSpace(x,y,it->state)==false)
        {
            it--;
        }
        else
        {
            it->mx=x;
            it->my=y;

            if(it->mx>=man.mx&&it->mx<=man.mx+30&&
                it->my>=man.my&&it->my<=man.my+30)
            {
                man.isLive=false;
                qt1->stop();
            }
        }
    }

}
//怪物移动范围
bool MainWidget::MonsterOfSpace(int x,int y,int st)
{
    //怪物处于不同状态下
   if(st==0)//向上
    {
        if(x%30==15)//当处于格子中间时不能上下移动
        {
            //qDebug()<<"1";
            return false;
        }
        if(sv[y/30][x/30]==1)
        {
           // qDebug()<<"2";
            return false;
        }
        if(brick[y/30][x/30]==1)
        {
            //qDebug()<<"3";
            return false;
        }
    }else if(st==1)//向下
    {
        if(x%30==15)//当处于格子中间时不能上下移动
        {
            //qDebug()<<"4";
            return false;
        }
        if(sv[(y+15)/30][x/30]==1)
        {
           // qDebug()<<"5";
            return false;
        }
        if(brick[(y+15)/30][x/30]==1)
        {
            //qDebug()<<"6";
            return false;
        }
    }else if(st==2)//向左
    {
        if(y%30==15)//当处于格子中间时不能左右移动
        {
            //qDebug()<<"7";
            return false;
        }
        if(sv[y/30][x/30]==1)
        {
            //qDebug()<<"8";
            return false;
        }
        if(brick[y/30][x/30]==1)
        {
            //qDebug()<<"9";
            return false;
        }

    }else if(st==3)//向右
    {
        if(y%30==15)//当处于格子中间时不能左右移动
        {
            //qDebug()<<"10";
            return false;
        }
        if(sv[y/30][(x+15)/30]==1)

        {
            //qDebug()<<"11";
            return false;
        }
        if(brick[y/30][(x+15)/30]==1)
        {
            //qDebug()<<"12";
            return false;
        }
    }else
    {
        qDebug()<<"参数有误";
    }
    return true;
}


bool MainWidget::IsOk(Man man, int (*sv)[25],int (*brick)[25],int x,int y)
{
    if((x==man.mx/30&&y==man.my/30)||
            sv[y][x]==1||
            brick[y][x]==1)
    {
        return false;
    }
   // qDebug()<<"x "<<x<<"  y "<<y<<"stone "<<sv[y][x];
    return true;
}

MainWidget::~MainWidget()
{
    delete ui;

}

//绘图事件
void MainWidget::paintEvent(QPaintEvent *)
{
    //为image赋值
    bg.paintBackground(image,man,sv,brick,qb,door,vm);
    QPainter p(this);
    p.drawImage(0,0,image);
    //判断玩家是否还活着
    //qDebug()<<"player state"<<man.isLive<<"  "<<qb.size();
    if(man.isLive==false&&qb.size()==0)
    {
        int res=QMessageBox::information(NULL,"Game Over!",
                                         "<center><h1>很遗憾你输了！</h1></center>",
                                         QMessageBox::Yes,QMessageBox::No);
        if(res==QMessageBox::Yes)
        {
            this->close();
        }else
        {
            this->close();
        }
    }
    //qDebug()<<"isWin  "<<man.isWin;
    if(man.isWin==true)
    {

        int res2=QMessageBox::information(NULL,"Game Over!",
                             "<center><h1>恭喜你获得胜利！</h1></center>",
                                         QMessageBox::Yes,QMessageBox::No);
        if(res2==QMessageBox::Yes)
        {
            this->close();
        }else
        {
            this->close();
        }
    }


}
//键盘按下事件
void MainWidget::keyPressEvent(QKeyEvent *e)
{
    if(man.isLive==false||man.isWin==true)
    {
        return;
    }

    if(e->key()==Qt::Key_Down)
    {
        if(man.state>=0&&man.state<3)
        {
            man.state=(man.state+1)%3;
        }else
        {
            man.state=0;
        }
        //判断的时候以为的最下边为基准先多加15 判断后再减去
        man.my+=15;
        if(playerIsMove(man,sv,brick)==false)
        {
            man.my-=15;
            return;
        }

    }
    else if(e->key()==Qt::Key_Up)
    {
        if(man.state>=3&&man.state<6)
        {
            man.state=(man.state+1)%3+3;
        }else
        {
            man.state=3;
        }
        man.my-=15;
        if(playerIsMove(man,sv,brick)==false)
        {
            man.my+=15;
            return;
        }

    }else if(e->key()==Qt::Key_Left)
    {
        if(man.state>=6&&man.state<9)
        {
            man.state=(man.state+1)%3+6;
        }else
        {
            man.state=6;
        }
        man.mx-=15;
        if(playerIsMove(man,sv,brick)==false)
        {
            man.mx+=15;
            return;
        }

    }else if(e->key()==Qt::Key_Right)
    {
        if(man.state>=9&&man.state<12)
        {
            man.state=(man.state+1)%3+9;
        }else
        {
            man.state=9;
        }
        man.mx+=15;
        if(playerIsMove(man,sv,brick)==false)
        {
            man.mx-=15;
            return;
        }

    }else if(e->key()==Qt::Key_Space)//按下空格键放下炸弹
    {
        int bx=man.mx,by=man.my;
        if(bx%30==15)
        {
            bx+=15;
        }
        if(by%30==15)
        {
            by+=15;
        }
        //创建炸弹 并把炸弹添加进一个vector中
        Boom b(bx,by,0);
        qb.push_back(b);
        //创建完炸弹就启动定时器
        qt->start(350);

    }else
    {
        qDebug()<<"无效按键";
        return;
    }
    //qDebug()<<man.state<<"  "<<man.mx<<" "<<man.my<<endl;
    update();
}

//判断玩家活动范围  是否进门
bool MainWidget::playerIsMove(Man &man, int (*sv)[25],int (*brick)[25])
{
    //判断玩家是否进门
    //qDebug()<<man.mx<<"#"<<door.x()*30<<"--"<<man.my<<"#"<<door.y()*30;
   if((man.mx==door.x()*30)&&(man.my==door.y()*30))
   {
       man.isWin=true;
   }

    //人处于不同状态下
   if(man.state>=0&&man.state<3)//向下
    {
        if(man.mx%30==15)//当处于格子中间时不能上下移动
        {
            //qDebug()<<"1";
            return false;
        }
        if(sv[(man.my+15)/30][man.mx/30]==1)
        {
           // qDebug()<<"2";
            return false;
        }
        if(brick[(man.my+15)/30][man.mx/30]==1)
        {
            //qDebug()<<"3";
            return false;
        }
        //炸弹位置
        for(auto it=qb.begin();it!=qb.end();it++)
        {
            if(it->x==man.mx&&it->y==(man.my+15))
            {
                return false;
            }
        }
    }else if(man.state<6)//向上
    {
        if(man.mx%30==15)//当处于格子中间时不能上下移动
        {
            //qDebug()<<"4";
            return false;
        }
        if(sv[man.my/30][man.mx/30]==1)
        {
           // qDebug()<<"5";
            return false;
        }
        if(brick[man.my/30][man.mx/30]==1)
        {
            //qDebug()<<"6";
            return false;
        }
        //炸弹位置
        for(auto it=qb.begin();it!=qb.end();it++)
        {
            if(it->x==man.mx&&it->y==man.my-15)
            {
                return false;
            }
        }
    }else if(man.state<9)//向左
    {
        if(man.my%30==15)//当处于格子中间时不能左右移动
        {
            //qDebug()<<"7";
            return false;
        }
        if(sv[man.my/30][man.mx/30]==1)
        {
            //qDebug()<<"8";
            return false;
        }
        if(brick[man.my/30][man.mx/30]==1)
        {
            //qDebug()<<"9";
            return false;
        }
        //炸弹位置
        for(auto it=qb.begin();it!=qb.end();it++)
        {
            if(it->x==man.mx-15&&it->y==man.my)
            {
                return false;
            }
        }

    }else if(man.state<12)//向右
    {
        if(man.my%30==15)//当处于格子中间时不能左右移动
        {
            //qDebug()<<"10";
            return false;
        }
        if(sv[man.my/30][(man.mx+15)/30]==1)

        {
            //qDebug()<<"11";
            return false;
        }
        if(brick[man.my/30][(man.mx+15)/30]==1)
        {
            //qDebug()<<"12";
            return false;
        }
        //炸弹位置
        for(auto it=qb.begin();it!=qb.end();it++)
        {
            if(it->x==(man.mx+15)&&it->y==man.my)
            {
                return false;
            }
        }
    }else
    {
        qDebug()<<"参数有误";
    }
    return true;
}



//为钢砖赋值
void MainWidget::positionOfStone(int (*sv)[25])
{
    for(int i=0;i<25;i++)
    {
        for(int j=0;j<17;j++)
        {
            if(i==0||i==24||j==0||j==16)
            {
                //将有钢砖的位置置为1
                sv[j][i]=1;
            }
        }
    }
    for(int i=2;i<25;i+=2)
    {
        for(int j=2;j<16;j+=2)
        {
            sv[j][i]=1;
        }
    }

}

//炸弹是否炸死怪
void MainWidget::MonsterOfDeath()
{
    for(auto it=qb.begin();it!=qb.end();it++)
    {
        if(it->bState>2)
        {
            //判断怪是否炸死
            while(1)
            {
                auto it1=vm.begin();
                for(;it1!=vm.end();it1++)
                {
                    if(it1->mx>=it->x-30&&it1->mx<=it->x+30&&
                            it1->my<=it->y+30&&it1->my>=it->y-30)
                    {
                        it1->isLive=false;
                        vm.erase(it1);
                        break;
                    }
                }
                if(it1==vm.end())
                {
                    break;
                }
            }

        }
    }

}

