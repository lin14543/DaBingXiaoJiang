#ifndef _MYSCENE_H_
#define _MYSCENE_H_

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "guize.h"
//#include "CCMenuItem.h"

USING_NS_CC;
struct node
{
	int value, id;//valueΪ0��idΪ1��18�ǽ���valueΪ1��idΪ0��1���Ǳ���valueΪ2��idΪ0�ǿ�
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
	bool selected;//����Ƿ�ѡ������
	int  TurnBing;


	void select(int x, int y);
	int abs(int x, int y);
	bool getPos(Point p,int &x,int &y);//�жϸõ��Ƿ���λ��
	bool Judge(Point p);//�ж�
	bool JudgeWin();
	bool JudgeKill(int x1, int y1, int x2, int y2);
	void move(int x, int y);
	virtual void ccTouchesBegan(Touch *touch, Event *event);//����ж�
	void GameAgain(Ref *pSender);
	void GameBack(Ref *pSender);
	void menuMusicToggleCallback(Ref *pSender);
	CREATE_FUNC(MyScene);
};

#endif