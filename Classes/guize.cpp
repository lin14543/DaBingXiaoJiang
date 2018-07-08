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

	Sprite *guize = Sprite::create("guize.jpg");//括号里面是图片的路径
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
	auto scene = Scene::create();//创建一个自释放的场景对象
	scene->addChild(HelloWorld::create());//把创建的画面层添加到场景中
	Director::getInstance()->replaceScene(TransitionFlipAngular::create(.5, scene));//运用导演类来进行切换场景 */
	Director::getInstance()->popScene();
}