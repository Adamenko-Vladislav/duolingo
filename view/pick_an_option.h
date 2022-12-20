#pragma once

#include <QCheckBox>

#include "task_window.h"

class PickAnOption : public TaskWindow {
 public:
  PickAnOption();

  void WriteTasks(const QString& question, const std::vector<QString>& answers);
  size_t GetCountAnswers() const;
  QString GetAnswer() const override;
  void ShowAnswer(const QString& answer) override;
  void CloseTask() override;

 protected:
  void closeEvent(QCloseEvent* event) override;

 private:
  std::vector<QCheckBox*> all_check_boxes_;
  QLabel* question_;
};
