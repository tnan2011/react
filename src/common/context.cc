#include "include/context.hpp"
#include "../utils/utils.hpp"
#include "QtCore/qdir.h"
#include "QtCore/qfileinfo.h"
#include "QtCore/qobject.h"
#include "QtCore/qstringliteral.h"
#include "QtWidgets/qcombobox.h"
#include "QtWidgets/qdialog.h"
#include "QtWidgets/qfiledialog.h"
#include "QtWidgets/qmainwindow.h"
#include "QtWidgets/qmessagebox.h"
#include "QtWidgets/qpushbutton.h"
#include "include/message.hpp"
#include "include/signal.hpp"
#include "include/state.hpp"
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include "include/process.hpp"
#include <iterator>

using namespace std;
using namespace Reaction::Common;
using namespace Reaction::Utils;

void Context::setOpenFileContext(QPushButton *button, Signal *signal,
                                 QMainWindow *windows, QComboBox *comboBox,
                                 State *state) {
  QObject::connect(button, &QPushButton::clicked, signal, [=]() {
    QString filePath = QFileDialog::getOpenFileName(windows, "Choose boot file",
                                                    QDir::homePath(),
                                                    "Boot File (*.img *.iso)");

    if (!filePath.isEmpty()) {
      QFileInfo fileInfo(filePath);
      QString fileName = fileInfo.fileName();
      comboBox->clear();
      comboBox->addItem(fileName);

      state->isoFilePath = filePath;
    }
  });
}

void Context::setOpenDeviceContext(QPushButton *button, Signal *signal,
                                   QMainWindow *windows, QComboBox *comboBox,
                                   State *state) {

  QObject::connect(button, &QPushButton::clicked, signal, [=]() {
    class Utils *utils = new class Utils();
    utils->showOpenDiskDialog(windows, state);

    if (!state->deviceName.isEmpty()) {
      comboBox->clear();
      QString diskInfo = QStringLiteral("%1 | %2")
                             .arg(state->deviceName)
                             .arg(state->devicePath);
      comboBox->addItem(diskInfo);
    }
    utils->reloadDiskInfo(state);
    delete utils;
  });
}

void Context::setReloadDiskContext(QPushButton *button, Signal *signal,
                                   QComboBox *comboBox, State *state) {
  QObject::connect(button, &QPushButton::clicked, signal, [=]() {
    class Utils *utils = new class Utils();
    utils->reloadDiskInfo(state);

    comboBox->clear();
    if (!state->deviceMap.isEmpty()) {
      for (auto it = state->deviceMap.constBegin();
           it != state->deviceMap.constEnd(); it++) {
        QString fmtText = QStringLiteral("%1 %2").arg(it.key()).arg(it.value());

        comboBox->addItem(fmtText);
      }
    }
    delete utils;
  });
}

void Context::getCurrentItemContext(QComboBox *comboBox, Signal *signal,
                                    State *state) {
  int currentIndex = comboBox->currentIndex();

  if (currentIndex >= comboBox->currentIndex() &&
      currentIndex < state->deviceMap.size()) {
    auto it = next(state->deviceMap.constBegin(), currentIndex);
    state->deviceName = it.key();
    state->devicePath = it.value();
  }

  QObject::connect(comboBox, &QComboBox::currentIndexChanged,
                   [comboBox, state](int index) {
                     if (index >= 0 && index < state->deviceMap.size()) {
                       auto it = next(state->deviceMap.constBegin(), index);
                       state->deviceName = it.key();
                       state->devicePath = it.value();
                     }
                   });
}

void Context::autoDetectDevice(QMainWindow *windows, QComboBox *comboBox,
                               State *state) {
  class Utils *utils = new class Utils();
  utils->reloadDiskInfo(state);

  comboBox->clear();
  if (state->deviceMap.isEmpty()) {
    comboBox->addItem("No device found");
    state->deviceName.clear();
    state->devicePath.clear();
  } else {
    for (auto it = state->deviceMap.constBegin();
         it != state->deviceMap.constEnd(); it++) {
      QString fmtText = QStringLiteral("%1 %2").arg(it.key()).arg(it.value());
      comboBox->addItem(fmtText);

      int currentIndex = comboBox->currentIndex();

      if (currentIndex >= comboBox->currentIndex() &&
          currentIndex < state->deviceMap.size()) {
        auto it = next(state->deviceMap.constBegin(), currentIndex);

        state->deviceName = it.key();
        state->devicePath = it.value();
      }

      QObject::connect(comboBox, &QComboBox::currentIndexChanged,
                       [comboBox, state](int index) {
                         if (index >= 0 && index < state->deviceMap.size()) {
                           auto it = next(state->deviceMap.constBegin(), index);
                           state->deviceName = it.key();
                           state->devicePath = it.value();
                         }
                       });
    }
    comboBox->setCurrentIndex(0);
  }
}

void Context::setStartContext(QPushButton *button, QMainWindow *windows,
                              Signal *signal, State *state) {
  QObject::connect(button, &QPushButton::clicked, [=]() {
    if (state->deviceName.isEmpty() || state->devicePath.isEmpty()) {
      QMessageBox::information(windows, "Infomation", DEVICE_NOT_FOUND);
      return;
    }

    if (!QFileInfo::exists(state->devicePath)) {
      QMessageBox::information(windows, "Infomation", DEVICE_PATH_NOT_FOUND);
      return;
    }
 
    if (state->devicePath.isEmpty() || !QFileInfo().exists(state->isoFilePath)) {
      QMessageBox::information(windows, "Infomation", ISO_PATH_NOT_FOUND);
      return;
    }

    Process process = Process();
    process.spawnProcess(windows, {"./reaction-cli", "gui-format-mbr-fat32", state->devicePath});
  });
}
