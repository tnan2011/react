#ifndef BUTTONS_HPP
#define BUTTONS_HPP
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <QtCore/QString>

namespace Reaction::Gui {
    class GuiButtons {
        public:
            QPushButton *setButtons(QWidget *widget, const QString &text,
                                    const int loc_x, const int loc_y,
                                    const int width, const int height);
    };
}

#endif // BUTTONS_HPP
