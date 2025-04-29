#include "include/buttons.hpp"

using namespace Reaction::Gui;

QPushButton *GuiButtons::setButtons(QWidget *widget, const QString &text,
                                    const int loc_x, const int loc_y,
                                    const int width, const int height) {
  QPushButton *button = new QPushButton(widget);
  button->setText(text);
  button->setGeometry(loc_x, loc_y, width, height);

  return button;
}
