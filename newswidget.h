// features/news/newswidget.h
#pragma once
#include <QWidget>
class QLineEdit;
class QPushButton;
class QListWidget;
class QNetworkAccessManager;

class NewsWidget : public QWidget {
    Q_OBJECT
public:
    explicit NewsWidget(QWidget* parent = nullptr);
private:
    QLineEdit* apiKeyEdit_;
    QLineEdit* queryEdit_;
    QPushButton* btnSearch_;
    QListWidget* list_;
    QNetworkAccessManager* nam_;
    void setupUi();
    void searchNews();
    void addItem(const QString& title, const QString& desc = QString());
};
