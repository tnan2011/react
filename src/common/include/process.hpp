#ifndef PROCESS_HPP
#define PROCESS_HPP
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtWidgets/QWidget>

namespace Reaction::Common {
    class Process {
        public:
            int spawnProcess(QWidget *windows, const QStringList &params);
    };
}

#endif // PROCESS_HPP
