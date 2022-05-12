#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget mainWindow;

    auto* labelImage = new QLabel;
    
    auto* sliderBlure = new QSlider(Qt::Horizontal);
    sliderBlure->setRange(0, 10);
    sliderBlure->setTickPosition(QSlider::TicksBelow);
    sliderBlure->setTickInterval(2);
    sliderBlure->setValue(0);
    QObject::connect(sliderBlure, &QSlider::valueChanged, [labelImage](const int value) {
        auto* blur = new QGraphicsBlurEffect;
        blur->setBlurRadius(value);
        labelImage->setGraphicsEffect(blur);

        });

    auto* buttonOpen = new QPushButton("& Open");
    QObject::connect(buttonOpen, &QPushButton::clicked, [labelImage]() {
        QString filePath = QFileDialog::getOpenFileName(nullptr,
                                                        "open image file",
                                                        "",
                                                        "jpg files (*.jpg)");

        QPixmap pix;
        pix.load(filePath);

        labelImage->setPixmap(pix.scaled(
                                            labelImage->width(),
                                            labelImage->height(),
                                            Qt::KeepAspectRatio));

        });

    auto* vBox = new QVBoxLayout(&mainWindow);
    vBox->addWidget(labelImage);
    vBox->addWidget(sliderBlure);
    vBox->addWidget(buttonOpen);

    mainWindow.resize(800, 800);
    mainWindow.show();
    return a.exec();
}
