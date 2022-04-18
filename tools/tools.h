#pragma once

#include <QPushButton>

#include "file_loader.h"
#include "random.h"

void CustomButton(QPushButton* button,
                  const QString& name,
                  const QColor& color,
                  const QString& font_name = "Arial",
                  int font_size = 20,
                  QFont::Weight x = QFont::Bold);

namespace tasks_types {

enum class TasksTypes {
  kPickAnOption,
  kInputAnswer,
  kAudio,
  kMixed,
  kCount
};

}  // namespace tasks_types
