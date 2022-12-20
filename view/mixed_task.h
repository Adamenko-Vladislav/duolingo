#pragma once

#include <QCheckBox>
#include <QTextEdit>

#include "task_window.h"
#include "tools.h"

class Mixed : public TaskWindow {
 public:
  Mixed();

  void CloseTask() override;
  QString GetAnswer() const override;
  void ShowAnswer(const QString& answer) override;

  void WritePickAnOptionTask(const QString& question,
                             const std::vector<QString>& answers);
  void WriteInputAnswerTask(const QString& question);
  void WriteAudioTask();

  QPushButton* GetAudio() const {
    return audio_;
  }

  size_t GetCountAnswers() const;

  tasks_types::TasksTypes GetLastQuestion() const {
    return current_task_;
  }

 private:
  QLabel* question_;
  QPushButton* audio_;
  std::vector<QCheckBox*> all_check_boxes_;
  QTextEdit* input_answer_;

  tasks_types::TasksTypes current_task_;
};
