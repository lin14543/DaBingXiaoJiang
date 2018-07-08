#ifndef _MYSCENE_H_
#define _MYSCENE_H_

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "guize.h"
//#include "CCMenuItem.h"

USING_NS_CC;
struct node
{
	int value, id;//value为0，id为1到18是将，value为1，id为0到1，是兵，value为2，id为0是空
};


class MyScene :public cocos2d::Layer
{
public:
	node vis[7][7];
	int num_jiang;
	Sprite* pos[18];
	Sprite* bing[2];
	Sprite* selectSprite;
	static cocos2d::Scene* createScene();
	virtual bool init();
	int selected_x;
	int selected_y;
	bool selected;//标记是否选中棋子
	int  TurnBing;


	void select(int x, int y);
	int abs(int x, int y);
	bool getPos(Point p,int &x,int &y);//判断该点是否点对位置
	bool Judge(Point p);//判断
	bool JudgeWin();
	bool JudgeKill(int x1, int y1, int x2, int y2);
	void move(int x, int y);
	virtual void ccTouchesBegan(Touch *touch, Event *event);//点击判定
	void GameAgain(Ref *pSender);
	void GameBack(Ref *pSender);
	void menuMusicToggleCallback(Ref *pSender);
	CREATE_FUNC(MyScene);
};

#endif