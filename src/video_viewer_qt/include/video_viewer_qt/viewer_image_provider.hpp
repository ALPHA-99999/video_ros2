#pragma once

#include <QQuickImageProvider>

class ViewerBackend;

class ViewerImageProvider : public QQuickImageProvider {
public:
    explicit ViewerImageProvider(ViewerBackend *backend);

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

private:
    ViewerBackend *backend_ = nullptr;
};
