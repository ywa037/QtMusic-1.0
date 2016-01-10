#include "topbar.h"
#include "UI/ToolWidget/imagebutton.h"
#include "UI/ToolWidget/mymenu.h"
#include "UI/ToolWidget/skinmenu.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QtWidgets/QWidgetAction>

TopBar::TopBar(QWidget *parent) : QWidget(parent)
{
/*
      QPalette palette;//调色板
      palette.setColor(QPalette::Background, QColor(18, 0, 169));//设置调色板参数为背景色，RGB颜色为深蓝色
      this->setAutoFillBackground(true);//将组件的背景设为可调
      this->setPalette(palette);//将调色板应用于组件
*/
    this->setAttribute(Qt::WA_TranslucentBackground, true);//设置透明:窗体标题栏不透明,背景透明
    this->setFixedHeight(51);

    logoLabel = new LogoLabel;
    QPixmap pix(":/icons/res/icons/app_icon.gif");
    QSize size(45, 34);//将图标缩小
    logoLabel->setPixmap(pix.scaled(size, Qt::KeepAspectRatio));

    QWidget *leftWidget = new QWidget;
    leftWidget->setFixedHeight(51);
    QHBoxLayout *leftLayout = new QHBoxLayout(leftWidget);
    leftLayout->addWidget(logoLabel);
    leftLayout->setMargin(5);
    leftLayout->setSpacing(0);//设置按钮间的间距为0

    //皮肤按钮
    skinButton = new ImageButton(":/icons/res/icons/skinbutton_icon.png");
    MyMenu *skinMenu = new MyMenu(this);
    connect(skinButton, SIGNAL(clicked()), skinMenu,SLOT(menuVisiable()));
    SkinMenu *skinItem = new SkinMenu(this);
    connect(skinItem, SIGNAL(changeSkin(QString)), this, SIGNAL(setBackgroud(QString)));
    QWidgetAction *skin1 = new QWidgetAction(this);
    skin1->setDefaultWidget(skinItem);
    skinMenu->addAction(skin1);

    //菜单按钮相关设置
    menuButton = new ImageButton(":/icons/res/icons/menubutton_icon.png");
    MyMenu *menu = new MyMenu(this);
    QAction *aboutUs = new QAction("关于", menu);
    QAction *quit = new QAction("退出软件", menu);
    connect(aboutUs, SIGNAL(triggered()), this, SIGNAL(aboutQtMusic()));
    connect(quit, SIGNAL(triggered(bool)), this, SIGNAL(quit()));

    menu->addAction(aboutUs);
    menu->addAction(quit);
    connect(menuButton, SIGNAL(clicked()), menu, SLOT(menuVisiable()));

    //最小化按钮相关设置
    hideButton = new ImageButton(":/icons/res/icons/hidebutton_icon.png");
    connect(hideButton, SIGNAL(clicked()), this, SIGNAL(setMinSize()));

    //最大化按钮相关设置
    maxButton = new ImageButton(":/icons/res/icons/maxbutton_icon.png");
    connect(maxButton, SIGNAL(clicked()), this, SIGNAL(setMaxSize()));

    //关闭按钮相关设置
    closeButton = new ImageButton(":/icons/res/icons/closebutton_icon.png");
    connect(closeButton, SIGNAL(clicked()), this, SIGNAL(closeWindow()));

    //通过水平布局将三个按钮组合起来
    QWidget *rightWidget = new QWidget;
    rightWidget->setFixedHeight(51);
    rightWidget->setMouseTracking(true);//鼠标跟踪
    QHBoxLayout *rightLayout = new QHBoxLayout(rightWidget);
    rightLayout->addWidget(skinButton);
    rightLayout->addWidget(menuButton);
    rightLayout->addWidget(hideButton);
    rightLayout->addWidget(maxButton);
    rightLayout->addWidget(closeButton);
    //rightLayout->addStretch();
    rightLayout->setMargin(3);
    rightLayout->setSpacing(3);//设置按钮间的间距为0

    //将按钮布局加入主布局中，而且靠左靠顶显示
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(leftWidget);
    mainLayout->addStretch();
    mainLayout->addWidget(rightWidget, 0, Qt::AlignRight | Qt::AlignTop);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    this->setLayout(mainLayout);

    dealMouse();
}

void TopBar::mouseDoubleClickEvent(QMouseEvent *)
{
    emit setMaxSize();
}

void TopBar::dealMouse()
{
    connect(logoLabel, SIGNAL(mouseEnter()), this, SIGNAL(mouseEnter()));
    connect(skinButton, SIGNAL(mouseEnter()), this, SIGNAL(mouseEnter()));
    connect(menuButton, SIGNAL(mouseEnter()), this, SIGNAL(mouseEnter()));
    connect(hideButton, SIGNAL(mouseEnter()), this, SIGNAL(mouseEnter()));
    connect(maxButton, SIGNAL(mouseEnter()), this, SIGNAL(mouseEnter()));
    connect(closeButton, SIGNAL(mouseEnter()), this, SIGNAL(mouseEnter()));
}

LogoLabel::LogoLabel(QWidget *parent)
    : QLabel(parent)
{
}

void LogoLabel::enterEvent(QEvent *e)//鼠标进入事件
{
    emit mouseEnter();
}