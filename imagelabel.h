// imagelabel.h
#pragma once
#include <QLabel>
#include <QPixmap>

class ImageLabel : public QLabel {
    Q_OBJECT
public:
    explicit ImageLabel(QWidget* parent = nullptr);
    void setPixmap(const QPixmap& pixmap);

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    QPixmap pixmap_;
};
