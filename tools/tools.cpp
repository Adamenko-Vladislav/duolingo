#include "tools.h"

void CustomButton(QPushButton* button,
                  const QString& name,
                  const QColor& color,
                  const QString& font_name,
                  int font_size,
                  QFont::Weight x) {
  button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  button->setText(name);
  button->setFont(QFont(font_name, font_size, x));
  QPalette pal = button->palette();
  pal.setColor(QPalette::Button, color);
  button->setAutoFillBackground(true);
  button->setPalette(pal);
  button->update();
}