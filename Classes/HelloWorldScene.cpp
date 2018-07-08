#include "HelloWorldScene.h"


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    //获取整个手机可视屏幕尺寸
    Size visibleSize = Director::getInstance()->getVisibleSize(); 
    //获取手机可视屏原点的坐标 
    Point origin = Director::getInstance()->getVisibleOrigin();


    //创建一个带图标的按钮
	//点击后调用menuCloseCallback方法退出游戏 
    auto closeItem = MenuItemImage::create(
											"kaishi.png",
                                           "kaishi1.png",
                                           CC_CALLBACK_1(HelloWorld::GameShow, this)); 

	closeItem->setPosition(Point(400, 320));

	auto closeItem1= MenuItemImage::create(
		"guize.png",
		"guize1.png",
		CC_CALLBACK_1(HelloWorld::GameRule, this));

	closeItem1->setPosition(Point(410, 200));


	//创建一个带图标的按钮
	//点击后调用menuCloseCallback方法退出游戏 
	auto closeItem2 = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	//设置按钮的显示位置
	//显示在可视屏幕的右下角 
	closeItem2->setPosition(Point(origin.x + visibleSize.width - closeItem2->getContentSize().width / 2,
		origin.y + closeItem2->getContentSize().height / 2));

	
    //创建一个可释放的菜单 
	auto menu = Menu::create(closeItem, closeItem1, closeItem2, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    
    //创建一个显示"Hello World"文字的Label
    auto label = LabelTTF::create("Little Big Soldier", "Arial", 24);
    
     //position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);


	auto bg = Sprite::create("_jiemian.png");
	bg->setPosition(Point(400,261));
	//bg->setContentSize(Size(11,16));
	addChild(bg);

	
    return true;
}


void HelloWorld::GameShow(Ref* pSender)
{
	auto scene = Scene::create();//创建一个自释放的场景对象
	scene->addChild(MyScene::create());//把创建的画面层添加到场景中
	Director::getInstance()->pushScene(TransitionFlipAngular::create(.5, scene));//运用导演类来进行切换场景 
}

void HelloWorld::GameRule(Ref* pSender)
{
	auto scene1 = Scene::create();//创建一个自释放的场景对象
	scene1->addChild(MyRule::create());//把创建的画面层添加到场景中
	Director::getInstance()->pushScene(TransitionFlipAngular::create(.5, scene1));//运用导演类来进行切换场景 
}

//退出按钮事件	
void HelloWorld::menuCloseCallback(Ref* pSender)
{
//当是wp8或者winrt平台的时候
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
//结束Director
    Director::getInstance()->end();
//当是ios平台的时候退出
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
