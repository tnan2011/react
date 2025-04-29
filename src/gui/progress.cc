#include "include/progress.hpp"
#include "QtWidgets/qprogressbar.h"
#include <QtCore/QString>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QWidget>

using namespace Reaction::Gui;

QProgressBar *GuiProgress::setProgressBar(QWidget *widget, const QString &text,
                                          const int loc_x, const int loc_y,
                                          const int width, const int height) {
    QProgressBar *progressBar = new QProgressBar(widget);
    progressBar->setGeometry(loc_x, loc_y, width, height);
    progressBar->setValue(0);
    progressBar->setFormat(text);
    progressBar->setStyleSheet(R"(
        QProgressBar {
            text-align: center;
        }

        QProgressBar::chunk {
            background-color: #4CAF50;
            width: 1px;
        }
    )");
    
    return progressBar;
}
