#include "../mainWindow.hpp"
#include "../common/include/props.hpp"
#include "../utils/utils.hpp"
#include "../common/include/context.hpp"
#include "QtCore/qobject.h"
#include <QtWidgets/QWidget>
#include <QtCore/QString>
#include "QtWidgets/qcombobox.h"
#include "QtWidgets/qmainwindow.h"
#include "init.hpp"
#include <QtWidgets/QMainWindow>

using namespace std;
using namespace Reaction;
using namespace Reaction::Utils;
using namespace Reaction::Common;
using namespace Reaction::Gui;

MainWindow::MainWindow(QWidget *window) : QMainWindow(window) {
    props = new AppProps();
    props->application_name = "reaction!";
    props->application_version = "1.0.0";

    QString title_fmt = QString().asprintf("%s %s", 
        props->application_name, 
        props->application_version);

    setWindowTitle(title_fmt);
    setFixedSize(800, 600);
    utils = new class Utils();
    utils->moveCenter(this);
    
    signal = new Signal(this);
    state = new State();
    context = new Context();

    InitUI *init = new InitUI();
    init->setup(this, signal, state, context);
}

void MainWindow::showEvent(QShowEvent *event) {
    context->autoDetectDevice(this, findChild<QComboBox*>("deviceListObject"), state);
    QMainWindow::showEvent(event);
}

MainWindow::~MainWindow() {
    delete props;
    delete utils;
    delete signal;
    delete context;
    delete state;
}
