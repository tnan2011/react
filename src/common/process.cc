#include "include/process.hpp"
#include "../cmd/sys/include/status.h"
#include "QtCore/qlogging.h"
#include "include/message.hpp"
#include <QtCore/QProcess>
#include <QtCore/QFile>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QWidget>

using namespace Reaction::Common;

int Process::spawnProcess(QWidget *windows, const QStringList &params) { 
    QFile fileProgram = QFile("reaction-cli");

    if(!fileProgram.exists()) {
        QMessageBox::information(windows, "Information", CLI_PROGRAM_PATH_NOT_FOUND);
        return CLI_PATH_NOT_FOUND;
    }

    QProcess process;
    
    process.start("pkexec", params);
    process.waitForFinished();

    QString stderr_o = QString::fromUtf8(process.readAllStandardError());
    qDebug() << stderr_o;

    return SUCCESS;
}
