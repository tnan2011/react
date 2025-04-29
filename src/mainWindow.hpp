#ifndef mainWindow_HPP
#define mainWindow_HPP
#include <QtWidgets/QMainWindow>
#include "QtWidgets/qwidget.h"
#include "common/include/context.hpp"
#include "common/include/props.hpp"
#include "common/include/state.hpp"
#include "utils/utils.hpp"
#include "common/include/signal.hpp"

using namespace Reaction;
using namespace Reaction::Utils;
using namespace Reaction::Common;

namespace Reaction {
    class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *window = nullptr);
        void initUI();
        ~MainWindow();

    protected:
        void showEvent(QShowEvent *event) override;

    private:
        AppProps *props;
        class Utils *utils;

        Signal *signal;
        Context *context;
        State *state;
    };
}
#endif // mainWindow_HPP
