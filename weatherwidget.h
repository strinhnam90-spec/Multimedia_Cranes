// features/weather/weatherwidget.h
#pragma once
#include <QWidget>
#include "imagelabel.h" // Include the new header
class QLineEdit;
class QPushButton;
class QNetworkAccessManager;

class WeatherWidget : public QWidget {
    Q_OBJECT
public:
    explicit WeatherWidget(QWidget* parent = nullptr);
private:
    QLineEdit* apiKeyEdit_;
    QLineEdit* cityEdit_;
    QPushButton* btnFetch_;
    QLabel* lblResult_;
    ImageLabel* lblEmotion_; // Change the type to ImageLabel*
    QNetworkAccessManager* nam_;
    void setupUi();
    void fetchWeather();
};
