#pragma once

#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMovie>

#include "tools.h"

class WinScene : public QMainWindow {
 public:
  explicit WinScene(const QString& file_name);

  QPushButton* GetFinish() const {
    return finish_;
  }

 private:
  QWidget* win_widget_;
  QGridLayout* win_layout_;
  QMovie* movie_;
  QLabel* movie_label_;
  QPushButton* finish_;
};
