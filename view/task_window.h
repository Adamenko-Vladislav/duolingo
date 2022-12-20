#pragma once

#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QProgressBar>

#include "tools.h"

class TaskWindow : public QMainWindow {
 Q_OBJECT

 public:
  TaskWindow();

  QGridLayout* GetMainLayout() const {
    return main_layout_;
  }

  QWidget* GetMainWidget() const {
    return main_widget_;
  }

  QPushButton* GetReady() const {
    return ready_;
  }

  QPushButton* GetExit() const {
    return exit_;
  }

  void SetAttemptsText(const QString& text) {
    attempts_->setText(text);
  }

  void SetProgressText(const QString& text) {
    progress_->setFormat(text);
  }

  void UpdateProgress(size_t value) {
    progress_->setValue(value);
  }

  virtual void ShowAnswer(const QString&) = 0;
  virtual QString GetAnswer() const = 0;
  virtual void CloseTask() = 0;

 private:
  void CustomAllButtons();
  void SetLayout();

  QWidget* main_widget_;
  QGridLayout* main_layout_;

  QPushButton* ready_;
  QPushButton* exit_;
  QLabel* attempts_;
  QProgressBar* progress_;
};
