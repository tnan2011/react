#include "include/label.hpp"
#include <QtGui/QFontMetrics>

using namespace Reaction::Gui;

QLabel *GuiLabel::setLabel(QWidget *widget, const QString &text,
                           const int x_loc, const int y_loc, const int width,
                           const int height) {

  QLabel *label = new QLabel(text, widget);
  label->setGeometry(x_loc, y_loc, width, height);

  return label;
}

void GuiLabelUtils::setLabelFixedSize(QLabel *label, const int size) {
  QFont font = label->font();
  font.setPointSize(size);
  label->setFont(font);

  QFontMetrics metrics(font);
  QSize textLabelSize = metrics.size(Qt::TextSingleLine, label->text());

  label->setFixedSize(textLabelSize);
}
