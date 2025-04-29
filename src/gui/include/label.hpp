#ifndef LABEL_HPP
#define LABEL_HPP

#include <QtWidgets/QLabel>
#include <QtCore/QString>
#include <QtWidgets/QWidget>

namespace Reaction::Gui {
    class GuiLabel {
        public:
        QLabel *setLabel(
            QWidget *widget, const QString &text, 
            const int x_loc, const int y_loc,
            const int width, const int height
        );
    };
    class GuiLabelUtils {
        public:
        void setLabelFixedSize(QLabel *label, const int size);
    };
}

#endif // LABEL_HPP
