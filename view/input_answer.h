#pragma once

#include <QTextEdit>

#include "task_window.h"

class InputAnswer : public TaskWindow {
 public:
  InputAnswer();
  void WriteTasks(const QString& question);

  QString GetAnswer() const override {
    return input_answer_->toPlainText();
  }

  void ShowAnswer(const QString& answer) override {
    input_answer_->setText(answer);
  }

  void CloseTask() override;

 private:
  QTextEdit* input_answer_;
  QLabel* question_;
};
