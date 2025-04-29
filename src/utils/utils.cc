#include "utils.hpp"
#include "QtCore/qcontainerfwd.h"
#include "QtCore/qdebug.h"
#include "QtCore/qdir.h"
#include "QtCore/qfiledevice.h"
#include "QtCore/qfileinfo.h"
#include "QtCore/qmap.h"
#include "QtCore/qobject.h"
#include "QtCore/qstringliteral.h"
#include "QtGui/qwindowdefs.h"
#include "QtWidgets/qboxlayout.h"
#include "QtWidgets/qdialog.h"
#include <QtWidgets/QVBoxLayout>
#include "QtWidgets/qdialogbuttonbox.h"
#include "QtWidgets/qlistwidget.h"
#include "QtWidgets/qwidget.h"
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QApplication>
#include <QtGui/QScreen>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtCore/QStorageInfo>
#include "../common/include/state.hpp"
#include <libudev.h>

using namespace Reaction::Utils;
using namespace Reaction::Common;

void Utils::moveCenter(QWidget *window) {
    if(!window)
        return;

    QScreen *screen = QApplication::primaryScreen();
    if(!screen)
        return;

    QRect screenGeometry = screen->geometry();

    int x_point = (screenGeometry.width() - window->width() ) / 2;
    int y_point = (screenGeometry.height() - window->height()) / 2;

    window->move(x_point, y_point);
}

QString Utils::getDevicePath(const QString &device) {
    struct udev *udev = udev_new();
    if(!udev)
        return "Unknown Device Path";

    struct udev_device *udev_device = udev_device_new_from_subsystem_sysname(udev, "block", device.toStdString().c_str());

    const char *devNode = udev_device_get_devnode(udev_device);
    QString deviceAbsolutePath = devNode ? QString(devNode) : "Unknown Device Path";

    udev_device_unref(udev_device);
    udev_unref(udev);

    return deviceAbsolutePath;
}

void Utils::showOpenDiskDialog(QWidget *window, State *state) {
    QDialog dialog(window);
    dialog.setWindowTitle("Device Selection");
    dialog.setFixedSize(600, 300);

    QVBoxLayout boxLayout(&dialog);
    QListWidget listWidget(&dialog);
    QDialogButtonBox dialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);

    QDir dir("/sys/block");
    QStringList stringList = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    QMap<QString, QString> deviceMap;
    for(const QString &device : stringList ) {
       QString modelPath = "/sys/block/" + device + "/device/model";
       QString devicePath = "/sys/block/" + device;

       QFile fileModel(modelPath);
       QString defaultDeviceName = device;

       if(fileModel.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream textStream(&fileModel);
            defaultDeviceName += " | " + textStream.readLine().trimmed();
            fileModel.close();
       }
       QString deviceAbsolutePath = getDevicePath(device);
       QString diskInfo = QStringLiteral("%1 | %2").arg(defaultDeviceName).arg(deviceAbsolutePath);

       listWidget.addItem(diskInfo);
       deviceMap[diskInfo] = device;
    }
    boxLayout.addWidget(&listWidget);
    boxLayout.addWidget(&dialogButtonBox);

    QObject::connect(&dialogButtonBox, &QDialogButtonBox::accepted, [&]() {
        if(listWidget.currentItem()) {
            QString selectedItem = listWidget.currentItem()->text();
            state->deviceName = deviceMap[selectedItem];

            state->devicePath = getDevicePath(state->deviceName);
            dialog.accept();
        }
    });

    QObject::connect(&dialogButtonBox, &QDialogButtonBox::rejected, [&]() {
        dialog.reject();
    });

   dialog.exec();
}

void Utils::reloadDiskInfo(State *state) {
    QDir dir("/sys/block");
    QStringList stringList = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    QString deviceAbsolutePath;
    QString defaultDeviceName;

    state->deviceMap.clear();
    for(const QString &device : stringList ) {
       QString modelPath = "/sys/block/" + device + "/device/model";
       QString devicePath = "/sys/block/" + device;

       QFile fileModel(modelPath);
       defaultDeviceName = device;

       if(fileModel.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream textStream(&fileModel);
            defaultDeviceName += " | " + textStream.readLine().trimmed();
            fileModel.close();
       }
       deviceAbsolutePath = getDevicePath(device);

       state->deviceMap[defaultDeviceName] = deviceAbsolutePath;
    }
}
