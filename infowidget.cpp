// features/infowidget.cpp
#include "infowidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>

InfoWidget::InfoWidget(QWidget* parent) : QWidget(parent) {
    auto lay = new QVBoxLayout;
    auto lbl = new QLabel("Sản phẩm của sinh viên FPT Cranes.\n");
    lbl->setWordWrap(true);
    lay->addWidget(lbl);

    // Display map of Vietnam
    // Note: Image must be placed in a folder named "images" in the build directory.
    // Example: build/Desktop_Qt_...-Debug/images/vietnam_map.png
    auto mapLabel = new QLabel;
    QPixmap map(":/images/vietnam_map.jpg"); // Assuming images are in a resource file
    mapLabel->setPixmap(map.scaled(400, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    mapLabel->setAlignment(Qt::AlignCenter);
    lay->addWidget(mapLabel);

    lay->addStretch(1);
    setLayout(lay);
}
