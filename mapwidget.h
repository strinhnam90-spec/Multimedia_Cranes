// features/mapwidget.h
#pragma once
#include <QWidget>
class QLabel;
class QPushButton;
class QNetworkAccessManager;

class MapWidget : public QWidget {
    Q_OBJECT
public:
    explicit MapWidget(QWidget* parent = nullptr);
private:
    QLabel* lblMap_;
    QPushButton* btnZoomIn_;
    QPushButton* btnZoomOut_;
    int zoomLevel_;
    QNetworkAccessManager* nam_;
    void loadMap();
};
