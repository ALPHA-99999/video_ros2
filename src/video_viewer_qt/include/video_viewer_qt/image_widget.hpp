#pragma once

#include <QImage>
#include <QMutex>
#include <QWidget>

class ImageWidget : public QWidget {
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = nullptr);
    void setImage(const QImage &image);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QMutex mutex_;
    QImage image_;
};