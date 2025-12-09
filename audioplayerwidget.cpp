#include "audioplayerwidget.h"
#include "ui_audioplayerwidget.h"

#include <QDir>
#include <QFileInfo>

AudioPlayerWidget::AudioPlayerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioPlayerWidget),
    m_player(new QMediaPlayer(this)),
    m_audioOutput(new QAudioOutput(this)),
    m_currentIndex(-1)
{
    ui->setupUi(this);

    m_player->setAudioOutput(m_audioOutput);

    connect(m_player, &QMediaPlayer::positionChanged, this, &AudioPlayerWidget::on_positionChanged);
    connect(m_player, &QMediaPlayer::durationChanged, this, &AudioPlayerWidget::on_durationChanged);
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &AudioPlayerWidget::on_mediaStatusChanged);

    loadPlaylist();
}

AudioPlayerWidget::~AudioPlayerWidget()
{
    delete ui;
}

void AudioPlayerWidget::loadPlaylist()
{
    QDir audioDir(QCoreApplication::applicationDirPath() + "/../../audio");
    if (!audioDir.exists()) {
        // Create the directory if it doesn't exist
        audioDir.mkpath(".");
        ui->currentTrackLabel->setText("Audio directory created. Please add MP3 files.");
        return;
    }

    QStringList nameFilters;
    nameFilters << "*.mp3";
    QFileInfoList fileList = audioDir.entryInfoList(nameFilters, QDir::Files | QDir::Readable);

    ui->playlistWidget->clear();
    m_playlist.clear();

    for (const QFileInfo &fileInfo : fileList) {
        m_playlist.append(QUrl::fromLocalFile(fileInfo.absoluteFilePath()));
        ui->playlistWidget->addItem(fileInfo.fileName());
    }

    if (m_playlist.isEmpty()) {
        ui->currentTrackLabel->setText("No MP3 files found in the 'audio' directory.");
    }
}

void AudioPlayerWidget::on_playPauseButton_clicked()
{
    if (m_player->playbackState() == QMediaPlayer::PlayingState) {
        m_player->pause();
        ui->playPauseButton->setText("Play");
    } else {
        if (m_currentIndex == -1 && !m_playlist.isEmpty()) {
            m_currentIndex = 0;
            ui->playlistWidget->setCurrentRow(m_currentIndex);
            m_player->setSource(m_playlist.at(m_currentIndex));
        }
         if (m_currentIndex != -1) {
            m_player->play();
            ui->playPauseButton->setText("Pause");
        }
    }
}

void AudioPlayerWidget::on_stopButton_clicked()
{
    m_player->stop();
    ui->playPauseButton->setText("Play");
}

void AudioPlayerWidget::on_nextButton_clicked()
{
    if (m_playlist.isEmpty()) return;

    m_currentIndex = (m_currentIndex + 1) % m_playlist.size();
    ui->playlistWidget->setCurrentRow(m_currentIndex);
    m_player->setSource(m_playlist.at(m_currentIndex));
    m_player->play();
    ui->playPauseButton->setText("Pause");
}

void AudioPlayerWidget::on_prevButton_clicked()
{
    if (m_playlist.isEmpty()) return;

    m_currentIndex = (m_currentIndex - 1 + m_playlist.size()) % m_playlist.size();
    ui->playlistWidget->setCurrentRow(m_currentIndex);
    m_player->setSource(m_playlist.at(m_currentIndex));
    m_player->play();
    ui->playPauseButton->setText("Pause");
}

void AudioPlayerWidget::on_playlistWidget_itemDoubleClicked(QListWidgetItem *item)
{
    int index = ui->playlistWidget->row(item);
    if (index != -1) {
        m_currentIndex = index;
        m_player->setSource(m_playlist.at(m_currentIndex));
        m_player->play();
        ui->playPauseButton->setText("Pause");
    }
}

void AudioPlayerWidget::on_progressSlider_sliderMoved(int position)
{
    m_player->setPosition(position);
}

void AudioPlayerWidget::on_positionChanged(qint64 position)
{
    ui->progressSlider->setValue(position);
}

void AudioPlayerWidget::on_durationChanged(qint64 duration)
{
    ui->progressSlider->setRange(0, duration);
}

void AudioPlayerWidget::on_mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia) {
        on_nextButton_clicked(); // Autoplay next song
    } else if (status == QMediaPlayer::LoadedMedia) {
        ui->currentTrackLabel->setText(QFileInfo(m_player->source().toLocalFile()).fileName());
    } else if (status == QMediaPlayer::InvalidMedia) {
        ui->currentTrackLabel->setText("Error: Cannot play file.");
    }
}
