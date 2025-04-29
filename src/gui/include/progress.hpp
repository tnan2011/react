#ifndef PROGRESS_HPP
#define PROGRESS_HPP
#include <QtWidgets/QWidget>
#include <QtCore/QString>
#include <QtWidgets/QProgressBar>

namespace Reaction::Gui {
    class GuiProgress {
        public:
            QProgressBar *setProgressBar(QWidget *widget, const QString &text,
                                         const int loc_x, const int loc_y,
                                         const int width, const int height);
    };
}

#endif // PROGRESS_HPP
