#include "video_viewer_qt/viewer_image_provider.hpp"

#include "video_viewer_qt/viewer_backend.hpp"

ViewerImageProvider::ViewerImageProvider(ViewerBackend *backend)
    : QQuickImageProvider(QQuickImageProvider::Image),
      backend_(backend)
{
}

QImage ViewerImageProvider::requestImage(const QString &, QSize *size, const QSize &requestedSize)
{
    if (!backend_) {
        return {};
    }

    QImage image = backend_->latestImage();
    if (image.isNull()) {
        return {};
    }

    if (requestedSize.isValid() && requestedSize != image.size()) {
        image = image.scaled(requestedSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    if (size) {
        *size = image.size();
    }
    return image;
}
