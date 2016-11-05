#include "UserWindow.hpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    UserWindow user_window;
    return app.exec();
}
