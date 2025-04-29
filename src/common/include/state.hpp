#ifndef STATE_HPP
#define STATE_HPP
#include "QtCore/qhashfunctions.h"
#include "QtCore/qmap.h"
#include <QtCore/QString>
#include <QtCore/QStringList>

namespace Reaction::Common {
    class State {
        public:
            QString isoFilePath;
            QString deviceName;
            QString devicePath;

            QMap<QString, QString> deviceMap;
    };
}

#endif // STATE_HPP
