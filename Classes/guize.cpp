#include "guize.h"
USING_NS_CC;
Scene* MyRule::createScene()
{
	auto scene1 = Scene::create();
	auto layer = MyRule::create();
	scene1->addChild(layer);
	return scene1;
}
bool MyRule::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Sprite *guize = Sprite::create("guize.jpg");//����������ͼƬ��·��
	guize->setPosition(Point(400, 261));
	addChild(guize);

	
	auto closeItem = MenuItemImage::create(
		"back.png",
		"back1.png",
		CC_CALLBACK_1(MyRule::Back, this));

	closeItem->setPosition(Point(300,35));

	auto menu = Menu::create(closeItem,NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);

}
void MyRule::Back(Ref* pSender)
{
	/*
	auto scene = Scene::create();//����һ�����ͷŵĳ�������
	scene->addChild(HelloWorld::create());//�Ѵ����Ļ������ӵ�������
	Director::getInstance()->replaceScene(TransitionFlipAngular::create(.5, scene));//���õ������������л����� */
	Director::getInstance()->popScene();
}