#include "video_viewer_qt/image_widget.hpp"

#include <QMutexLocker>
#include <QPainter>

ImageWidget::ImageWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(640, 360);
}

void ImageWidget::setImage(const QImage &image)
{
    {
        QMutexLocker locker(&mutex_);
        image_ = image.copy();
    }
    update();
}

void ImageWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);

    QImage local;
    {
        QMutexLocker locker(&mutex_);
        local = image_;
    }
    if (local.isNull()) {
        return;
    }

    const QImage scaled = local.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    const QPoint topLeft((width() - scaled.width()) / 2, (height() - scaled.height()) / 2);
    painter.drawImage(topLeft, scaled);
}