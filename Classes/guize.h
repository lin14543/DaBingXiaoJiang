#ifndef _MyScene_H_
#define _MyScene_H_

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "guize.h"
#include "pan.h"
USING_NS_CC;

class MyRule :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void Back(Ref *pSender);
	CREATE_FUNC(MyRule);
};

#endif