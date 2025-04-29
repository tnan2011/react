#ifndef UTILS_HPP
#define UTILS_HPP
#include "QtCore/qobject.h"
#include "../common/include/state.hpp"
#include "QtWidgets/qwidget.h"
#include <QtWidgets/QWidget>

using namespace Reaction::Common;

namespace Reaction::Utils {
    class Utils {
        public:
            void moveCenter(QWidget *window);
            QString getDevicePath(const QString &device);
            void showOpenDiskDialog(QWidget *window, State *state);
            void reloadDiskInfo(State *state);
    };
}

#endif // UTILS_HPP
