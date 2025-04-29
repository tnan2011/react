#include "include/dropbox.hpp"
#include <QtGui/QPainter>

using namespace Reaction::Gui;

QComboBox *GuiDropbox::setComboBox(QWidget *widget, const QString &text,
                                   const int x_loc, const int y_loc,
                                   const int width, const int height) {

  QComboBox *comboBox = new GuiDropboxStyle(widget);
  comboBox->addItem(text);
  comboBox->setGeometry(x_loc, y_loc, width, height);

  return comboBox;
}

QComboBox *GuiDropbox::setMultiComboBox(QWidget *widget,
                                        const vector<QString> &text_list,
                                        const int x_loc, const int y_loc,
                                        const int width, const int height) {
  QComboBox *comboBox = new GuiDropboxStyle(widget);

  for (QString text : text_list) {
    comboBox->addItem(text);
  }
  comboBox->setGeometry(x_loc, y_loc, width, height);

  return comboBox;
}

void GuiDropboxStyle::setTransparent(bool enable) {
  transparent = enable;
  update();
}

void GuiDropboxStyle::paintEvent(QPaintEvent *paintEvent) {
  if (transparent) {
    QStyleOptionComboBox optionComboBox;
    initStyleOption(&optionComboBox);

    QPainter painter(this);
    optionComboBox.state &= ~(QStyle::State_HasFocus | QStyle::State_MouseOver);
    style()->drawControl(QStyle::CE_ComboBoxLabel, &optionComboBox, &painter,
                         this);
  } else {
    QComboBox::paintEvent(paintEvent);
  }
}
