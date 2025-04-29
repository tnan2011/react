#ifndef SIGNAL_HPP
#define SIGNAL_HPP
#include "QtCore/qobject.h"
#include "QtCore/qtmetamacros.h"

namespace Reaction::Common {
    class Signal : public QObject {
        Q_OBJECT
        public:
             Signal(QObject *object) : QObject(object) {}
    };
}

#endif // SIGNAL_HPP
