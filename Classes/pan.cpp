#include "pan.h"
#include "SimpleAudioEngine.h"


using namespace CocosDenshion;
USING_NS_CC;
Scene* MyScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MyScene::create();
	scene->addChild(layer);
	return scene;
}
/*
Scene* MyScene::create()
{
	MyScene* pRet = new MyScene();

	if (pRet)
	{
		if (pRet->init())
		{
			pRet->autorelease();
		}
		else
		{
			pRet->release();
			return NULL;
		}
	}
	else
	{
		return NULL;
	}

	return pRet;
}

*/
bool MyScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	//预加载背景音乐
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("MyMusic/firework.mp3");
	

	Sprite *bj = Sprite::create("bj.png");//括号里面是图片的路径
	bj->setPosition(Point(400, 261));
	addChild(bj);

	Sprite *qipan = Sprite::create("__qipan.png");//括号里面是图片的路径
	qipan->setPosition(Point(280,261));
	addChild(qipan);


	bing[0] = Sprite::create("bing.png");//括号里面是图片的路径
	bing[0]->setPosition(Point(70 + 2 * 84, 471 - 5 * 84));
	addChild(bing[0]);

	bing[1] = Sprite::create("bing.png");//括号里面是图片的路径
	bing[1]->setPosition(Point(70 + 3 * 84, 471 - 5 * 84));
	addChild(bing[1]);

	Sprite *an = Sprite::create("an.png");//括号里面是图片的路径
	an->setPosition(Point(620, 190));
	addChild(an);

	auto closeItem= MenuItemImage::create(
		"xin.png",
		"xin1.png",
		CC_CALLBACK_1(MyScene::GameAgain, this));

	closeItem->setPosition(Point(620,410));

	auto closeItem1 = MenuItemImage::create(
		"fan.png",
		"fan1.png",
		CC_CALLBACK_1(MyScene::GameBack, this));

	closeItem1->setPosition(Point(620, 300));


	auto musicOnMenuItem = MenuItemImage::create(
		"on.png",
		"on.png");
	auto musicOffMenuItem = MenuItemImage::create(
		
		"off.png",
		"off.png");
	auto musicToggleMenuItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(MyScene::menuMusicToggleCallback, this),
		musicOffMenuItem,
		musicOnMenuItem,
		NULL);
	musicToggleMenuItem->setPosition(Point(618, 194));

	auto menu = Menu::create(closeItem, closeItem1, musicToggleMenuItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
	for (int i = 1; i <= 6; i++)
	{
		for (int j = 1; j <= 6; j++)
		{
			vis[i][j].id = 0;
			vis[i][j].value = 2;
		}

	}
	for (int i = 0; i < 18; i++)
		pos[i] = Sprite::create("jiang.png");
	for (int i = 1,k=0, x = 70; i <= 6; i++, x += 84)
	{
		for (int j = 1, y = 471; j <= 3; j++, y -= 84)
		{
			//pos[k] = Sprite::create("jiang.png");
			pos[k]->setPosition(Point(x, y));
			addChild(pos[k]);
			vis[i][7 -j].id = k++;
			vis[i][7 - j].value = 0;
		}
	}
	num_jiang = 18;//记录将的数量
	TurnBing = 1;//是否该兵走
	selected = false;//是否选择了棋子
	vis[3][1].value = vis[4][1].value = 1;
	vis[3][1].id = 0, vis[4][1].id = 1;

	//设置选择框 
	selectSprite = Sprite::create("selected.png");
	this->addChild(selectSprite);
	selectSprite->setVisible(false);
	selectSprite->setPosition(Point(70,471));
//	selectSprite->setZOrder(1000);

//	vis[6][1].id = vis[6][3].id = vis[6][2].id = 0;
//	vis[6][1].value = vis[6][2].value = vis[6][3].value = 2;
	for (int i = 1; i <= 6;i++)
	for (int j = 1; j <= 6; j++)
		log("%d %d %d %d", i, j, vis[i][j].value, vis[i][j].id);

	//注册触摸事件
	auto listeren = EventListenerTouchOneByOne::create();
	
	listeren->onTouchBegan = [=](Touch *touch, Event *even)
	{
		this->ccTouchesBegan(touch, even);
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listeren, this);

	return true;
	
}

void MyScene::ccTouchesBegan(Touch *touch, Event *event)
{

	Point p = touch->getLocationInView();

	int x, y;//触摸点下标（vis）
	if (!getPos(p,x,y))//如果没点在交点
	{
		return ;
	}
	log("%d %d %d %d", x, y,vis[x][y].id,vis[x][y].value);
	if (false == selected)
	{
		if (vis[x][y].value == TurnBing)
			select(x, y);
		return;
	}
	else 
	{
		if (x == selected_x&&y == selected_y)
		{
			selectSprite->setVisible(false);
			selected = false;
		}
		else
			move(x, y);
	}
	return ;
}

void MyScene::select(int x1, int y1)//点击并记录
{
	selected_x = x1;
	selected_y = y1;
	this->selected = true;
	selectSprite->setVisible(true);
	selectSprite->setPosition(Point(70 + (x1 - 1) * 84, 471 - (6-y1) * 84));
}

bool MyScene::getPos(Point p, int &x, int &y)
{
	for (x = 1; x <= 6; x++)
	{
		for (y = 1; y <= 6; y++)
		{
			if (abs(70+(x-1)*84,p.x)<30 &&abs(471-(6-y)*84,533-p.y)<30)
				return true;
		}
	}
	return false;
}


void MyScene::move(int x, int y)
{
	MoveTo *mt = MoveTo::create(0.2, Point(70 + (x - 1) * 84, 533-(471 - (y - 1) * 84)));//移动
	if (vis[selected_x][selected_y].value == vis[x][y].value)//如果点击同种类型的棋子
	{
		select(x, y);
		return;
	}
	if (vis[x][y].value == 2 && (((abs(selected_x, x) == 1 && abs(selected_y, y) == 0) || (abs(selected_x, x) == 0 && abs(selected_y, y) == 1))))//可以移动
	{
		selected = false;
		selectSprite->setVisible(false);
		switch (vis[selected_x][selected_y].value)
		{
		case 1:bing[vis[selected_x][selected_y].id]->runAction(mt);
			vis[x][y].value = 1;
			vis[x][y].id = vis[selected_x][selected_y].id;
			break;
		case 0:pos[vis[selected_x][selected_y].id]->runAction(mt);
			vis[x][y].value = 0;
			vis[x][y].id = vis[selected_x][selected_y].id;
			break;
		}
		vis[selected_x][selected_y].value = 2;
		vis[selected_x][selected_y].id = 0;
		TurnBing = !TurnBing;
		if (JudgeWin())
			GameAgain(this);
		return;
	}
	else if(vis[selected_x][selected_y].value == 1 && vis[x][y].value == 0 && JudgeKill(selected_x, selected_y, x, y))//吃子
	{
		selected = false;
		selectSprite->setVisible(false);
		removeChild(pos[vis[x][y].id]);
		bing[vis[selected_x][selected_y].id]->runAction(mt);
		vis[x][y].value = 1;
		vis[x][y].id = vis[selected_x][selected_y].id;
		vis[selected_x][selected_y].value = 2;
		vis[selected_x][selected_y].id = 0;
		TurnBing = !TurnBing;
		num_jiang--;
		if (JudgeWin())
			GameAgain(this);
		return;
	}
	else
		return;
}

bool MyScene::JudgeWin()//判断输赢
{
	int i, j;
	if (!num_jiang)
	{
		MessageBox("Bing is succeessfully", "Alert");
		return true;
	}
	for ( i = 1; i <= 6; i++)
	{
		for ( j = 1; j <= 6; j++)
		{
			if (vis[i][j].value == 1 && (vis[i - 1][j].value == 2 || vis[i + 1][j].value == 2 || vis[i][j + 1].value == 2 || vis[i][j - 1].value == 2))
				break;
		}
		if (j <=6)
			break;
	}
	if (i > 6 && j > 6)
	{
		MessageBox("Jiang is succeessfully", "Alert");
		return true;
	}
	return false;
}

bool MyScene::JudgeKill(int x1, int y1, int x2, int y2)
{
	if (x1 - x2 == 2 && abs(y1, y2) == 0 && vis[x2 + 1][y1].value == 2)
		return true;
	if (x2 - x1 == 2 && abs(y1, y2) == 0 && vis[x1 + 1][y1].value == 2)
		return true;
	if (y1 - y2 == 2 && abs(x1, x2) == 0 && vis[x1][y2 + 1].value == 2)
		return true;
	if (y2 - y1 == 2 && abs(x1, x2) == 0 && vis[x1][y1 + 1].value == 2)
		return true;
	return false;
}

int MyScene::abs(int x, int y)
{
	return x > y ? x - y : y - x;
}

void MyScene::GameAgain(Ref* pSender)
{
	auto scene = Scene::create();//创建一个自释放的场景对象
	scene->addChild(MyScene::create());//把创建的画面层添加到场景中
	Director::getInstance()->replaceScene(TransitionFadeDown::create(.5, scene));//运用导演类来进行切换场景 
	/*
	this->removeAllChildren();
	this->init();*/
}

void MyScene::GameBack(Ref* pSender)
{
	
	auto scene = Scene::create();//创建一个自释放的场景对象
	scene->addChild(HelloWorld::create());//把创建的画面层添加到场景中
	Director::getInstance()->replaceScene(TransitionFadeDown::create(.5, scene));//运用导演类来进行切换场景 
	/*
	Director::getInstance()->popScene();*/
}

   void MyScene::menuMusicToggleCallback(Ref* pSender)
{
	auto musicToggleMenuItem = (MenuItemToggle*)pSender;
	log("musicToggleMenuItem %d", musicToggleMenuItem->getSelectedIndex());

	if (musicToggleMenuItem->getSelectedIndex() == 1) {//选中状态Off -> On                 
		SimpleAudioEngine::getInstance()->playBackgroundMusic("MyMusic/firework.mp3");
	}
	else {
		SimpleAudioEngine::getInstance()->stopBackgroundMusic("MyMusic/firework.mp3");
	}
}
