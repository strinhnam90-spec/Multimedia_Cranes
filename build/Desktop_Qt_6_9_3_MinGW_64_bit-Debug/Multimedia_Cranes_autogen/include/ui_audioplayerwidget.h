/********************************************************************************
** Form generated from reading UI file 'audioplayerwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUDIOPLAYERWIDGET_H
#define UI_AUDIOPLAYERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AudioPlayerWidget
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *playlistWidget;
    QLabel *currentTrackLabel;
    QSlider *progressSlider;
    QHBoxLayout *horizontalLayout;
    QPushButton *prevButton;
    QPushButton *playPauseButton;
    QPushButton *nextButton;
    QPushButton *stopButton;

    void setupUi(QWidget *AudioPlayerWidget)
    {
        if (AudioPlayerWidget->objectName().isEmpty())
            AudioPlayerWidget->setObjectName("AudioPlayerWidget");
        AudioPlayerWidget->resize(400, 300);
        verticalLayout = new QVBoxLayout(AudioPlayerWidget);
        verticalLayout->setObjectName("verticalLayout");
        playlistWidget = new QListWidget(AudioPlayerWidget);
        playlistWidget->setObjectName("playlistWidget");

        verticalLayout->addWidget(playlistWidget);

        currentTrackLabel = new QLabel(AudioPlayerWidget);
        currentTrackLabel->setObjectName("currentTrackLabel");
        currentTrackLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(currentTrackLabel);

        progressSlider = new QSlider(AudioPlayerWidget);
        progressSlider->setObjectName("progressSlider");
        progressSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(progressSlider);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        prevButton = new QPushButton(AudioPlayerWidget);
        prevButton->setObjectName("prevButton");

        horizontalLayout->addWidget(prevButton);

        playPauseButton = new QPushButton(AudioPlayerWidget);
        playPauseButton->setObjectName("playPauseButton");

        horizontalLayout->addWidget(playPauseButton);

        nextButton = new QPushButton(AudioPlayerWidget);
        nextButton->setObjectName("nextButton");

        horizontalLayout->addWidget(nextButton);

        stopButton = new QPushButton(AudioPlayerWidget);
        stopButton->setObjectName("stopButton");

        horizontalLayout->addWidget(stopButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(AudioPlayerWidget);

        QMetaObject::connectSlotsByName(AudioPlayerWidget);
    } // setupUi

    void retranslateUi(QWidget *AudioPlayerWidget)
    {
        AudioPlayerWidget->setWindowTitle(QCoreApplication::translate("AudioPlayerWidget", "Audio Player", nullptr));
        currentTrackLabel->setText(QCoreApplication::translate("AudioPlayerWidget", "No Track Selected", nullptr));
        prevButton->setText(QCoreApplication::translate("AudioPlayerWidget", "Prev", nullptr));
        playPauseButton->setText(QCoreApplication::translate("AudioPlayerWidget", "Play", nullptr));
        nextButton->setText(QCoreApplication::translate("AudioPlayerWidget", "Next", nullptr));
        stopButton->setText(QCoreApplication::translate("AudioPlayerWidget", "Stop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AudioPlayerWidget: public Ui_AudioPlayerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUDIOPLAYERWIDGET_H
