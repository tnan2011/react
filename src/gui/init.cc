#include "init.hpp"
#include "QtWidgets/qcombobox.h"
#include "QtWidgets/qlabel.h"
#include "QtWidgets/qprogressbar.h"
#include "QtWidgets/qpushbutton.h"
#include "include/buttons.hpp"
#include "include/dropbox.hpp"
#include "include/label.hpp"
#include "include/progress.hpp"

using namespace Reaction::Gui;

void InitUI::setup(MainWindow *window, Signal *signal, State *state, Context *context) {
    GuiLabel *guiLabel = new GuiLabel();
    QLabel *deviceSelect = guiLabel->setLabel(window, "Device Selection:", 10, 30, 100, 30);
    QLabel *bootFileSelect = guiLabel->setLabel(window, "Boot File Selection:", 10, 100, 100, 30);
    QLabel *partitionSelect = guiLabel->setLabel(window, "Partition Selection:", 10, 170, 100, 30);
    QLabel *fileSystemSelect = guiLabel->setLabel(window, "File System Selection:", 10, 240 , 100, 30);

    GuiLabelUtils *guiLabelUtils = new GuiLabelUtils();
    guiLabelUtils->setLabelFixedSize(deviceSelect, 12);
    guiLabelUtils->setLabelFixedSize(bootFileSelect, 12);
    guiLabelUtils->setLabelFixedSize(partitionSelect, 12);
    guiLabelUtils->setLabelFixedSize(fileSystemSelect, 12);

    GuiDropbox *guiDropbox = new GuiDropbox();
    QComboBox *deviceList = guiDropbox->setComboBox(window, "No device found", 10, 60, 280, 30);
    deviceList->setObjectName("deviceListObject");
    static_cast<Gui::GuiDropboxStyle*>(deviceList)->setTransparent(true);

    QComboBox *bootSelctionList = guiDropbox->setComboBox(window, "No boot file", 10, 130, 280, 30);
    static_cast<Gui::GuiDropboxStyle*>(bootSelctionList)->setTransparent(true);

    vector<QString> partitionSelectionList = {"MBR", "GPT"};
    vector<QString> fileSystemList = {"FAT32", "ETX4" };

    QComboBox *selectPartition = guiDropbox->setMultiComboBox(window, partitionSelectionList, 10, 200,  280, 30);
    QComboBox *selectFileSystem = guiDropbox->setMultiComboBox(window, fileSystemList, 10, 270, 280, 30);
    static_cast<Gui::GuiDropboxStyle*>(selectPartition)->setTransparent(true);
    static_cast<Gui::GuiDropboxStyle*>(selectFileSystem)->setTransparent(true);

    GuiButtons *guiButtons = new GuiButtons();

    QPushButton *reloadDiskButton = guiButtons->setButtons(window, "Device not found? Reload", 360, 60, 200, 30);
    QPushButton *openDeviceButton = guiButtons->setButtons(window, "Choose device manually",600, 60, 200, 30);
    QPushButton *openBootFileButton  = guiButtons->setButtons(window, "Choose boot file", 360, 130, 200, 30);
    QPushButton *startButton = guiButtons->setButtons(window, "Start now", 10, 340, 280, 30);

    GuiProgress *guiProgress = new GuiProgress();
    QProgressBar *progressBar = guiProgress->setProgressBar(window, "Nothing to show..", 350, 340, 250, 30);

    context->getCurrentItemContext(deviceList, signal, state);
    context->setOpenFileContext(openBootFileButton, signal, window, bootSelctionList, state);
    context->setOpenDeviceContext(openDeviceButton, signal, window, deviceList, state);
    context->setReloadDiskContext(reloadDiskButton, signal, deviceList, state);
    context->setStartContext(startButton, window, signal, state);
}
