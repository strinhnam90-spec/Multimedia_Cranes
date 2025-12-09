// features/weather/weatherwidget.cpp
#include "weatherwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPixmap>

WeatherWidget::WeatherWidget(QWidget* parent) : QWidget(parent),
    apiKeyEdit_(new QLineEdit(this)),
    cityEdit_(new QLineEdit(this)),
    btnFetch_(new QPushButton("Lấy thời tiết", this)),
    lblResult_(new QLabel(this)),
    lblEmotion_(new ImageLabel(this)),
    nam_(new QNetworkAccessManager(this)) {
    setupUi();
    connect(btnFetch_, &QPushButton::clicked, this, &WeatherWidget::fetchWeather);
}

void WeatherWidget::setupUi() {
    apiKeyEdit_->setPlaceholderText("API key OpenWeatherMap");
    cityEdit_->setPlaceholderText("Thành phố (vd: Hanoi,VN)");
    cityEdit_->setText("Hanoi,VN");
    lblResult_->setWordWrap(true);

    auto top = new QHBoxLayout;
    top->addWidget(apiKeyEdit_, 1);
    top->addWidget(cityEdit_, 1);
    top->addWidget(btnFetch_);

    auto lay = new QVBoxLayout;
    lay->addLayout(top);
    lay->addWidget(lblResult_);
    lay->addWidget(lblEmotion_, 1); // Add stretch factor to make the image expand
    setLayout(lay);
}

void WeatherWidget::fetchWeather() {
    lblResult_->setText("Đang tải...");
    lblEmotion_->clear(); // Clear the emotion icon
    const QString key = apiKeyEdit_->text().trimmed();
    const QString city = cityEdit_->text().trimmed();
    QUrl url(QString("https://api.openweathermap.org/data/2.5/weather?q=%1&appid=%2&units=metric&lang=vi")
                 .arg(city, key));
    auto reply = nam_->get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, this, [this, reply]{
        if(reply->error() != QNetworkReply::NoError) {
            lblResult_->setText("Lỗi: " + reply->errorString());
            reply->deleteLater();
            return;
        }
        const auto doc = QJsonDocument::fromJson(reply->readAll());
        const auto obj = doc.object();
        const auto main = obj["main"].toObject();
        const auto weatherArr = obj["weather"].toArray();
        const QString desc = weatherArr.isEmpty() ? "" : weatherArr[0].toObject()["description"].toString();
        double temp = main["temp"].toDouble();
        double feels = main["feels_like"].toDouble();
        int humid = main["humidity"].toInt();
        lblResult_->setText(QString("Nhiệt độ: %1°C\nCảm giác như: %2°C\nĐộ ẩm: %3%%\nMô tả: %4")
                                .arg(temp).arg(feels).arg(humid).arg(desc));

        // Display emotion icon based on temperature
        // Note: Images must be placed in a folder named "images" in the build directory.
        // Example: build/Desktop_Qt_...-Debug/images/smile.png
        QPixmap pixmap;
        if (temp > 20 && temp < 30) {
            pixmap.load(":/images/autumn.jpg");
        } else if (temp >= 30 ) {
            pixmap.load(":/images/summer.jpg");
        } else if (temp <= 20 ) {
            pixmap.load(":/images/winter.webp");
        }

        if (!pixmap.isNull()) {
            lblEmotion_->setPixmap(pixmap);
        } else {
            lblEmotion_->clear();
        }

        reply->deleteLater();
    });
}
