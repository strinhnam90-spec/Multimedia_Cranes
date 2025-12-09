// features/news/newswidget.cpp
#include "newswidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

NewsWidget::NewsWidget(QWidget* parent) : QWidget(parent),
    apiKeyEdit_(new QLineEdit(this)),
    queryEdit_(new QLineEdit(this)),
    btnSearch_(new QPushButton("Tìm kiếm", this)),
    list_(new QListWidget(this)),
    nam_(new QNetworkAccessManager(this)) {
    setupUi();
    connect(btnSearch_, &QPushButton::clicked, this, &NewsWidget::searchNews);
}

void NewsWidget::setupUi() {
    apiKeyEdit_->setPlaceholderText("Nhập API key (NewsAPI)");
    queryEdit_->setPlaceholderText("Chủ đề (vd: football)");
    queryEdit_->setText("football");
    auto top = new QHBoxLayout;
    top->addWidget(apiKeyEdit_, 1);
    top->addWidget(queryEdit_, 1);
    top->addWidget(btnSearch_);
    auto lay = new QVBoxLayout;
    lay->addLayout(top);
    lay->addWidget(list_, 1);
    setLayout(lay);
}

void NewsWidget::addItem(const QString& title, const QString& desc) {
    auto item = new QListWidgetItem(title);
    if(!desc.isEmpty()) item->setToolTip(desc);
    list_->addItem(item); // The list widget takes ownership of the item.
}

void NewsWidget::searchNews() {
    list_->clear();
    const QString key = apiKeyEdit_->text().trimmed();
    const QString query = queryEdit_->text().trimmed();
    // Demo NewsAPI endpoint (replace with your source)
    // Removed category=sports and language=vi for a more general search
    QUrl url(QString("https://newsapi.org/v2/everything?q=%1&apiKey=%2").arg(query, key));
    auto reply = nam_->get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, this, [this, reply]{
        if(reply->error() != QNetworkReply::NoError) { addItem("Lỗi lấy tin: " + reply->errorString()); reply->deleteLater(); return; }
        const auto doc = QJsonDocument::fromJson(reply->readAll());
        const auto arr = doc.object().value("articles").toArray();
        for(const auto& v : arr) {
            auto o = v.toObject();
            addItem(o.value("title").toString(), o.value("description").toString());
        }
        reply->deleteLater();
    });
}
