#pragma once

#include <QCloseEvent>
#include <QDialog>
#include <QMenuBar>
#include <QShortcut>

#include "audio_task.h"
#include "input_answer.h"
#include "mixed_task.h"
#include "pick_an_option.h"
#include "presenter.h"
#include "win_scene.h"

class View : public QMainWindow {
 Q_OBJECT

 public:
  View();
  void CreateMenu(const QVariant& complexity,
                  const QVariant& sound,
                  const QVariant& score);

  QAction* GetEasy() const {
    return easy_;
  }

  QAction* GetHard() const {
    return hard_;
  }

  QAction* GetSound() const {
    return sound_;
  }

  QAction* GetResetScore() const {
    return reset_score_;
  }

  QAction* GetResetScoreSecondWay() const {
    return reset_score_second_way_;
  }

  QLabel* GetScore() const {
    return score_;
  }

  QPushButton* GetExit() const {
    return exit_;
  }

  QShortcut* GetExitKeysFst() const {
    return exit_keys_fst_;
  }

  QShortcut* GetExitKeysScd() const {
    return exit_keys_scd_;
  }

  QDialog* GetDialog() const {
    return dialog_;
  }

  QPushButton* GetAccept() const {
    return accept_;
  }

  QPushButton* GetDeny() const {
    return deny_;
  }

  const View* GetPtr() const {
    return this;
  }

  void SetNeedToClose(bool value) {
    need_to_close_ = value;
  }

  void SetScore(const QString& text) {
    score_->setText(text);
  }

  // Win

  QPushButton* GetWinFinishButton() const {
    return win_scene_.GetFinish();
  }

  void ShowWinScenePickAnOption() {
    win_scene_.setHidden(false);
  }

  void HideWinScene() {
    win_scene_.setHidden(true);
  }

  // PickAnOption

  PickAnOption* GetPickAnOption() const {
    return pick_an_option_task_;
  }

  QPushButton* GetPickAnOptionButton() const {
    return pick_an_option_;
  }

  size_t GetPickAnOptionCountAnswers() const {
    return pick_an_option_task_->GetCountAnswers();
  }

  void WriteTaskPickAnOption(const QString& quest,
                             const std::vector<QString>& answers) {
    pick_an_option_task_->WriteTasks(quest, answers);
  }

  // InputAnswer

  InputAnswer* GetInputAnswer() const {
    return input_answer_task_;
  }

  QPushButton* GetInputAnswerButton() const {
    return input_answer_;
  }

  void WriteTasksInputAnswer(const QString& task) {
    input_answer_task_->WriteTasks(task);
  }

  // Audio

  AudioTask* GetAudio() const {
    return audio_task_;
  }

  QPushButton* GetAudioButton() const {
    return audio_;
  }

  QPushButton* GetAudioTask() const {
    return audio_task_->GetAudio();
  }

  // Mixed

  Mixed* GetMixed() const {
    return mixed_task_;
  }

  QPushButton* GetMixedButton() const {
    return mixed_;
  }

  QPushButton* GetMixedAudioTask() const {
    return mixed_task_->GetAudio();
  }

  void WriteTasksMixedPickAnOption(const QString& quest,
                                   const std::vector<QString>& answers) {
    mixed_task_->WritePickAnOptionTask(quest, answers);
  }

  void WriteTasksMixedInputAnswer(const QString& task) {
    mixed_task_->WriteInputAnswerTask(task);
  }

  void WriteTasksMixedAudio() {
    mixed_task_->WriteAudioTask();
  }

  size_t GetMixedCountAnswers() {
    return mixed_task_->GetCountAnswers();
  }

  tasks_types::TasksTypes GetMixedLastQuestion() const {
    return mixed_task_->GetLastQuestion();
  }

  // General

  static void UpdateProgressBar(TaskWindow* window, size_t progress);
  static void UpdateAttempts(TaskWindow* window, size_t value);

  static QPushButton* GetTaskExitButton(TaskWindow* task) {
    return task->GetExit();
  }

  static void CloseTask(TaskWindow* task) {
    task->close();
  }

  static void ShowTask(TaskWindow* task) {
    task->show();
  }

  static void ClearTask(TaskWindow* task) {
    task->CloseTask();
  }

  static QPushButton* GetTaskReadyButton(const TaskWindow* task) {
    return task->GetReady();
  }

  static void TaskShowAnswer(TaskWindow* task, const QString& answer) {
    task->ShowAnswer(answer);
  }

  static QString GetTaskAnswer(const TaskWindow* task) {
    return task->GetAnswer();
  }

 protected:
  void closeEvent(QCloseEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;

 private:
  void SetLayout();
  void SetDialog();

  void CustomAllButtons();

  QMenu* complexity_;
  QMenu* settings_;

  QAction* easy_;
  QAction* hard_;

  QAction* sound_;
  QAction* reset_score_;
  QAction* reset_score_second_way_;

  QWidget* main_widget_;
  QGridLayout* main_layout_;

  QPushButton* pick_an_option_;
  QPushButton* input_answer_;
  QPushButton* audio_;
  QPushButton* mixed_;

  QPushButton* exit_;
  QShortcut* exit_keys_fst_;
  QShortcut* exit_keys_scd_;

  QDialog* dialog_;
  QHBoxLayout* dialog_layout_;
  QPushButton* accept_;
  QPushButton* deny_;

  bool need_to_close_;

  QLabel* score_;
  QMenu* context_menu_;

  PickAnOption* pick_an_option_task_{new PickAnOption};
  InputAnswer* input_answer_task_{new InputAnswer};
  AudioTask* audio_task_{new AudioTask};
  Mixed* mixed_task_{new Mixed};
  WinScene win_scene_{":/win.gif"};
};
