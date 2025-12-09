// features/video/videowidget.h
#pragma once
#include <QWidget>
class QMediaPlayer;
class QVideoWidget;
class QAudioOutput;
class QPushButton;
class QSlider;

class VideoWidget : public QWidget {
    Q_OBJECT
public:
    explicit VideoWidget(QWidget* parent = nullptr);
private:
    QMediaPlayer* player_;
    QVideoWidget* videoOut_;
    QAudioOutput* audioOut_;
    QPushButton* btnOpen_;
    QPushButton* btnPlayPause_;
    QPushButton* btnBack10_;
    QPushButton* btnFwd10_;
    QSlider* sliderPos_;
    void setupUi();
    void connectSignals();
    void updatePlayButton(bool playing);
};
