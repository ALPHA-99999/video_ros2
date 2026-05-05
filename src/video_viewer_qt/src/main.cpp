#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QUrl>
#include <QTimer>

#include <rclcpp/rclcpp.hpp>

#include "video_viewer_qt/viewer_backend.hpp"
#include "video_viewer_qt/viewer_image_provider.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    rclcpp::init(argc, argv);

    ViewerBackend backend;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("viewer", &backend);
    engine.addImageProvider("viewer", new ViewerImageProvider(&backend));
    engine.load(QUrl(QStringLiteral("qrc:/qml/Main.qml")));
    if (engine.rootObjects().isEmpty()) {
        rclcpp::shutdown();
        return 1;
    }

    QTimer spin_timer;
    QObject::connect(&spin_timer, &QTimer::timeout, [&]() {
        if (!rclcpp::ok()) {
            app.quit();
            return;
        }
        rclcpp::spin_some(backend.node());
    });
    spin_timer.start(5);

    const int rc = app.exec();
    rclcpp::shutdown();
    return rc;
}
