// app/mainwindow.cpp
#include "mainwindow.h"
#include <QStatusBar>

#include "videowidget.h"
#include "mapwidget.h"
#include "newswidget.h"
#include "weatherwidget.h"
#include "infowidget.h"
#include "audioplayerwidget.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), stack_(new QStackedWidget(this)) {
    setWindowTitle("Qt Multi Feature App");
    setCentralWidget(stack_);

    bottomBar_ = new QToolBar(this);
    bottomBar_->setMovable(false);
    addToolBar(Qt::BottomToolBarArea, bottomBar_);

    actVideo_   = new QAction("Video", this);
    actMap_     = new QAction("Bản đồ", this);
    actNews_    = new QAction("Tin tức", this);
    actWeather_ = new QAction("Thời tiết", this);
    actInfo_    = new QAction("Giới thiệu", this);
    actAudio_   = new QAction("Âm nhạc", this);

    bottomBar_->addAction(actVideo_);
    bottomBar_->addAction(actMap_);
    bottomBar_->addAction(actNews_);
    bottomBar_->addAction(actWeather_);
    bottomBar_->addAction(actInfo_);
    bottomBar_->addAction(actAudio_);

    stack_->addWidget(new VideoWidget(this));    // index 0
    stack_->addWidget(new MapWidget(this));      // index 1
    stack_->addWidget(new NewsWidget(this));     // index 2
    stack_->addWidget(new WeatherWidget(this));  // index 3
    stack_->addWidget(new InfoWidget(this));     // index 4
    stack_->addWidget(new AudioPlayerWidget(this)); // index 5

    connect(actVideo_,   &QAction::triggered, this, [this]{ stack_->setCurrentIndex(0); });
    connect(actMap_,     &QAction::triggered, this, [this]{ stack_->setCurrentIndex(1); });
    connect(actNews_,    &QAction::triggered, this, [this]{ stack_->setCurrentIndex(2); });
    connect(actWeather_, &QAction::triggered, this, [this]{ stack_->setCurrentIndex(3); });
    connect(actInfo_,    &QAction::triggered, this, [this]{ stack_->setCurrentIndex(4); });
    connect(actAudio_,   &QAction::triggered, this, [this]{ stack_->setCurrentIndex(5); });

    statusBar()->showMessage("Application FPT Cranes");
}
