// app/mainwindow.h
#pragma once
#include <QMainWindow>
#include <QStackedWidget>
#include <QToolBar>
#include <QAction>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
private:
    QStackedWidget* stack_;
    QToolBar* bottomBar_;
    QAction* actVideo_;
    QAction* actMap_;
    QAction* actNews_;
    QAction* actWeather_;
    QAction* actInfo_;
    QAction* actAudio_;
};
