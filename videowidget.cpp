// features/video/videowidget.cpp
#include "videowidget.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QVideoWidget>
#include <QFileDialog>
#include <QPushButton>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QStyle>

VideoWidget::VideoWidget(QWidget* parent) : QWidget(parent),
    player_(new QMediaPlayer(this)),
    videoOut_(new QVideoWidget(this)),
    audioOut_(new QAudioOutput(this)),
    btnOpen_(new QPushButton("Chọn video", this)),
    btnPlayPause_(new QPushButton("Phát", this)),
    btnBack10_(new QPushButton("« 10s", this)),
    btnFwd10_(new QPushButton("10s »", this)),
    sliderPos_(new QSlider(Qt::Horizontal, this)) {

    player_->setVideoOutput(videoOut_);
    player_->setAudioOutput(audioOut_);
    setupUi();
    connectSignals();
}

void VideoWidget::setupUi() {
    auto controls = new QHBoxLayout;
    controls->addWidget(btnOpen_);
    controls->addWidget(btnBack10_);
    controls->addWidget(btnPlayPause_);
    controls->addWidget(btnFwd10_);

    auto layout = new QVBoxLayout;
    layout->addWidget(videoOut_, 1);
    layout->addWidget(sliderPos_);
    layout->addLayout(controls);
    setLayout(layout);
}

void VideoWidget::connectSignals() {
    connect(btnOpen_, &QPushButton::clicked, this, [this]{
        QString f = QFileDialog::getOpenFileName(this, "Chọn video", QString(),
                                                 "Video (*.mp4 *.avi *.mkv *.mov *.wmv)");
        if(!f.isEmpty()) {
            player_->setSource(QUrl::fromLocalFile(f));
            player_->play();
            updatePlayButton(true);
        }
    });
    connect(btnPlayPause_, &QPushButton::clicked, this, [this]{
        if(player_->playbackState() == QMediaPlayer::PlayingState) {
            player_->pause();
            updatePlayButton(false);
        } else {
            player_->play();
            updatePlayButton(true);
        }
    });
    connect(btnBack10_, &QPushButton::clicked, this, [this]{
        qint64 pos = player_->position();
        player_->setPosition(std::max<qint64>(0, pos - 10000));
    });
    connect(btnFwd10_, &QPushButton::clicked, this, [this]{
        player_->setPosition(player_->position() + 10000);
    });
    connect(player_, &QMediaPlayer::positionChanged, this, [this](qint64 p){
        sliderPos_->setValue(static_cast<int>(p));
    });
    connect(player_, &QMediaPlayer::durationChanged, this, [this](qint64 d){
        sliderPos_->setRange(0, static_cast<int>(d));
    });
    connect(sliderPos_, &QSlider::sliderReleased, this, [this]{
        player_->setPosition(sliderPos_->value());
    });
}

void VideoWidget::updatePlayButton(bool playing) {
    btnPlayPause_->setText(playing ? "Tạm dừng" : "Phát");
}
