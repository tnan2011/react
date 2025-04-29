#include <QtWidgets/QApplication>
#include "mainWindow.hpp"

using namespace Reaction;

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    MainWindow window;

    window.show();
    return application.exec();
}
