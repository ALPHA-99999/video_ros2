#include <QApplication>
#include <QTimer>

#include <rclcpp/rclcpp.hpp>

#include "video_viewer_qt/viewer_window.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    rclcpp::init(argc, argv);

    ViewerWindow window;
    window.show();

    QTimer spinTimer;
    QObject::connect(&spinTimer, &QTimer::timeout, [&]() {
        if (!rclcpp::ok()) {
            app.quit();
            return;
        }
        rclcpp::spin_some(window.node());
    });
    spinTimer.start(5);

    const int rc = app.exec();
    rclcpp::shutdown();
    return rc;
}