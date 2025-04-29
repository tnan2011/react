#ifndef DROPBOX_HPP
#define DROPBOX_HPP
#include <QtWidgets/QComboBox>
#include <QtWidgets/QWidget>
#include <QtCore/QString>
#include <vector>

using namespace std;

namespace Reaction::Gui {
    class GuiDropbox {
        public:
        QComboBox *setComboBox(QWidget *widget, const QString &text,
                               const int x_loc, const int y_loc,
                               const int width, const int height
        );
        QComboBox *setMultiComboBox(QWidget *widget, const vector<QString> &text,
                                    const int x_loc, const int y_loc,
                                    const int width, const int height

        );
    };

    class GuiDropboxStyle : public QComboBox {
    Q_OBJECT
        public:
            using QComboBox::QComboBox;
            void setTransparent(bool enable);

        protected:
            void paintEvent(QPaintEvent *paintEvent) override;

        private:
            bool transparent = false;
    };
}

#endif // DROPBOX_HPP
