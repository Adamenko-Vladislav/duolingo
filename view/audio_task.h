#pragma once

#include <QTextEdit>

#include "task_window.h"
#include "tools.h"

class AudioTask : public TaskWindow {
 public:
  AudioTask();

  QPushButton* GetAudio() const {
    return audio_;
  }

  QString GetAnswer() const override {
    return answer_->toPlainText();
  }

  void ShowAnswer(const QString& answer) override {
    answer_->setText(answer);
  }

  void CloseTask() override {
    answer_->setText("");
  }

 private:
  QPushButton* audio_;
  QTextEdit* answer_;
};
