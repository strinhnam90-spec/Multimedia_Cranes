#ifndef AUDIOPLAYERWIDGET_H
#define AUDIOPLAYERWIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QDir>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class AudioPlayerWidget; }
QT_END_NAMESPACE

class AudioPlayerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AudioPlayerWidget(QWidget *parent = nullptr);
    ~AudioPlayerWidget();

private slots:
    void on_playPauseButton_clicked();
    void on_stopButton_clicked();
    void on_nextButton_clicked();
    void on_prevButton_clicked();
    void on_playlistWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_progressSlider_sliderMoved(int position);

    void on_positionChanged(qint64 position);
    void on_durationChanged(qint64 duration);
    void on_mediaStatusChanged(QMediaPlayer::MediaStatus status);


private:
    Ui::AudioPlayerWidget *ui;
    QMediaPlayer *m_player;
    QAudioOutput *m_audioOutput;
    QList<QUrl> m_playlist;
    int m_currentIndex;

    void loadPlaylist();
};

#endif // AUDIOPLAYERWIDGET_H
