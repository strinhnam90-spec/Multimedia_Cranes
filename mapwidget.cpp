// features/mapwidget.cpp
#include "mapwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>

MapWidget::MapWidget(QWidget* parent) : QWidget(parent),
    lblMap_(new QLabel(this)),
    btnZoomIn_(new QPushButton("+", this)),
    btnZoomOut_(new QPushButton("-", this)),
    zoomLevel_(12),
    nam_(new QNetworkAccessManager(this)) {

    lblMap_->setAlignment(Qt::AlignCenter);

    auto buttons = new QHBoxLayout;
    buttons->addWidget(btnZoomOut_);
    buttons->addWidget(btnZoomIn_);

    auto lay = new QVBoxLayout;
    lay->addLayout(buttons);
    lay->addWidget(lblMap_, 1);
    setLayout(lay);

    connect(btnZoomIn_, &QPushButton::clicked, this, [this]{ zoomLevel_++; loadMap(); });
    connect(btnZoomOut_, &QPushButton::clicked, this, [this]{ zoomLevel_--; loadMap(); });

    loadMap();
}

void MapWidget::loadMap() {
    // Hà Nội: lat=21.0278, lon=105.8342
    QString url = QString("https://staticmap.openstreetmap.de/staticmap.php?center=21.0278,105.8342&zoom=%1&size=600x400&maptype=mapnik")
                      .arg(zoomLevel_);
    QNetworkReply* reply = nam_->get(QNetworkRequest(QUrl(url)));
    connect(reply, &QNetworkReply::finished, this, [this, reply]{
        if(reply->error() == QNetworkReply::NoError) {
            QPixmap pix;
            pix.loadFromData(reply->readAll());
            lblMap_->setPixmap(pix.scaled(lblMap_->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            lblMap_->setText("Lỗi tải bản đồ: " + reply->errorString());
        }
        reply->deleteLater();
    });
}
