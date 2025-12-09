// imagelabel.cpp
#include "imagelabel.h"

ImageLabel::ImageLabel(QWidget* parent) : QLabel(parent) {
    setAlignment(Qt::AlignCenter);
}

void ImageLabel::setPixmap(const QPixmap& pixmap) {
    pixmap_ = pixmap;
    QLabel::setPixmap(pixmap_.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void ImageLabel::resizeEvent(QResizeEvent* event) {
    if (!pixmap_.isNull()) {
        QLabel::setPixmap(pixmap_.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    QLabel::resizeEvent(event);
}
