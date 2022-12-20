#pragma once

#include <QLabel>
#include <QPixmap>
#include <QSound>

#include <memory>

#include "task_window.h"
#include "tools.h"

class View;
class Model;

class Presenter {
 public:
  Presenter();
  void SetConnections();
  void SetPickAnOptionConnections();
  void SetInputAnswerConnections();
  void SetAudioConnections();
  void SetMixedConnections();

  QAction* GetEasy() const;
  QAction* GetHard() const;
  QAction* GetSound() const;
  QLabel* GetScore() const;

 private:
  void UpdateTasks(TaskWindow* task, bool win);
  void StartTask(tasks_types::TasksTypes type, TaskWindow* task);
  void GenerateMixedTask();

  bool IsWin(TaskWindow* task) const;

  std::shared_ptr<Model> model_;
  std::shared_ptr<View> view_;
};
