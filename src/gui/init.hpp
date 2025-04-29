#ifndef INIT_HPP
#define INIT_HPP
#include "../mainWindow.hpp"

namespace Reaction::Gui {
    class InitUI {
        public:
            void setup(MainWindow *mainWindow, Signal *signal, State *state, Context *context);

    };
}

#endif // INIT_HPP
