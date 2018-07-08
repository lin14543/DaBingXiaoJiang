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
    //��ȡ�����ֻ�������Ļ�ߴ�
    Size visibleSize = Director::getInstance()->getVisibleSize(); 
    //��ȡ�ֻ�������ԭ������� 
    Point origin = Director::getInstance()->getVisibleOrigin();


    //����һ����ͼ��İ�ť
	//��������menuCloseCallback�����˳���Ϸ 
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


	//����һ����ͼ��İ�ť
	//��������menuCloseCallback�����˳���Ϸ 
	auto closeItem2 = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	//���ð�ť����ʾλ��
	//��ʾ�ڿ�����Ļ�����½� 
	closeItem2->setPosition(Point(origin.x + visibleSize.width - closeItem2->getContentSize().width / 2,
		origin.y + closeItem2->getContentSize().height / 2));

	
    //����һ�����ͷŵĲ˵� 
	auto menu = Menu::create(closeItem, closeItem1, closeItem2, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    
    //����һ����ʾ"Hello World"���ֵ�Label
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
	auto scene = Scene::create();//����һ�����ͷŵĳ�������
	scene->addChild(MyScene::create());//�Ѵ����Ļ������ӵ�������
	Director::getInstance()->pushScene(TransitionFlipAngular::create(.5, scene));//���õ������������л����� 
}

void HelloWorld::GameRule(Ref* pSender)
{
	auto scene1 = Scene::create();//����һ�����ͷŵĳ�������
	scene1->addChild(MyRule::create());//�Ѵ����Ļ������ӵ�������
	Director::getInstance()->pushScene(TransitionFlipAngular::create(.5, scene1));//���õ������������л����� 
}

//�˳���ť�¼�	
void HelloWorld::menuCloseCallback(Ref* pSender)
{
//����wp8����winrtƽ̨��ʱ��
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
//����Director
    Director::getInstance()->end();
//����iosƽ̨��ʱ���˳�
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
