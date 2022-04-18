#include "presenter.h"

#include "model.h"
#include "view.h"

Presenter::Presenter() :
    view_(new View),
    model_(new Model(this)) {
  view_->CreateMenu(model_->GetComplexity(),
                    model_->GetSoundStatus(),
                    model_->GetScore());
  SetConnections();
}

void Presenter::SetConnections() {
  QAction::connect(view_->GetEasy(), &QAction::changed,
                   view_->GetPtr(), [this]() {
        model_->ResetEasy();
      });
  QAction::connect(view_->GetHard(), &QAction::changed,
                   view_->GetPtr(), [this]() {
        model_->ResetHard();
      });
  QAction::connect(view_->GetSound(), &QAction::changed,
                   view_->GetPtr(), [this]() {
        model_->ResetSound();
      });
  QAction::connect(view_->GetResetScore(), &QAction::triggered,
                   view_->GetPtr(), [this]() {
        model_->ResetScore();
      });
  QAction::connect(view_->GetResetScoreSecondWay(), &QAction::triggered,
                   view_->GetPtr(), [this]() {
        model_->ResetScore();
      });
  QPushButton::connect(view_->GetExit(), &QPushButton::clicked,
                       view_->GetPtr(), [this]() {
        view_->close();
      });
  QShortcut::connect(view_->GetExitKeysFst(), &QShortcut::activated,
                     view_->GetPtr(), [this]() {
        view_->close();
      });
  QShortcut::connect(view_->GetExitKeysScd(), &QShortcut::activated,
                     view_->GetPtr(), [this]() {
        view_->close();
      });
  QPushButton::connect(view_->GetAccept(), &QPushButton::clicked,
                       view_->GetPtr(), [this]() {
        view_->SetNeedToClose(true);
        view_->close();
      });

  QPushButton::connect(view_->GetDeny(), &QPushButton::clicked,
                       view_->GetPtr(), [this]() {
        view_->GetDialog()->close();
      });
  QPushButton::connect(view_->GetWinFinishButton(), &QPushButton::clicked,
                       view_->GetPtr(), [this] {
        view_->setHidden(false);
        View::ClearTask(view_->GetPickAnOption());
        View::ClearTask(view_->GetInputAnswer());
        View::ClearTask(view_->GetAudio());
        View::ClearTask(view_->GetMixed());
        view_->HideWinScene();
      });
  SetPickAnOptionConnections();
  SetInputAnswerConnections();
  SetAudioConnections();
  SetMixedConnections();
}

QAction* Presenter::GetEasy() const {
  return view_->GetEasy();
}

QAction* Presenter::GetHard() const {
  return view_->GetHard();
}

QAction* Presenter::GetSound() const {
  return view_->GetSound();
}

QLabel* Presenter::GetScore() const {
  return view_->GetScore();
}

void Presenter::SetPickAnOptionConnections() {
  QPushButton::connect(view_->GetPickAnOptionButton(), &QPushButton::clicked,
                       view_->GetPtr(), [this] {
        StartTask(tasks_types::TasksTypes::kPickAnOption,
                  view_->GetPickAnOption());
      });
  QPushButton::connect(View::GetTaskExitButton(view_->GetPickAnOption()),
                       &QPushButton::clicked, view_->GetPtr(), [this] {
        View::CloseTask(view_->GetPickAnOption());
        view_->setHidden(false);
      });
  QPushButton::connect(View::GetTaskReadyButton(view_->GetPickAnOption()),
                       &QPushButton::clicked, view_->GetPtr(), [this] {
        size_t count_answers = view_->GetPickAnOptionCountAnswers();
        bool win = (count_answers == 1 && IsWin(view_->GetPickAnOption()));
        UpdateTasks(view_->GetPickAnOption(), win);
        if (win) {
          PickAnOptionTask task = model_->GetPickAnOptionTask();
          view_->WriteTaskPickAnOption(task.quest_, task.answers_);
        }
      });
}

void Presenter::SetInputAnswerConnections() {
  QPushButton::connect(view_->GetInputAnswerButton(),
                       &QPushButton::clicked, view_->GetPtr(), [this] {
        StartTask(tasks_types::TasksTypes::kInputAnswer,
                  view_->GetInputAnswer());
      });
  QPushButton::connect(View::GetTaskExitButton(view_->GetInputAnswer()),
                       &QPushButton::clicked, view_->GetPtr(), [this] {
        View::CloseTask(view_->GetInputAnswer());
        view_->setHidden(false);
      });
  QPushButton::connect(View::GetTaskReadyButton(view_->GetInputAnswer()),
                       &QPushButton::clicked, view_->GetPtr(), [this] {
        bool win = IsWin(view_->GetInputAnswer());
        UpdateTasks(view_->GetInputAnswer(), win);
        if (win) {
          QString task = model_->GetInputAnswerTask();
          view_->WriteTasksInputAnswer(task);
        }
      });
}

void Presenter::SetAudioConnections() {
  QPushButton::connect(view_->GetAudioButton(), &QPushButton::clicked,
                       view_->GetPtr(), [this] {
        StartTask(tasks_types::TasksTypes::kAudio, view_->GetAudio());
        model_->GenerateAudioTask();
        View::ClearTask(view_->GetAudio());
      });
  QPushButton::connect(View::GetTaskExitButton(view_->GetAudio()),
                       &QPushButton::clicked, view_->GetPtr(), [this] {
        View::CloseTask(view_->GetAudio());
        View::ClearTask(view_->GetAudio());
        view_->setHidden(false);
      });
  QPushButton::connect(View::GetTaskReadyButton(view_->GetAudio()),
                       &QPushButton::clicked, view_->GetPtr(), [this] {
        bool win = IsWin(view_->GetAudio());
        UpdateTasks(view_->GetAudio(), win);
        if (win) {
          model_->GenerateAudioTask();
        }
      });
  QPushButton::connect(view_->GetAudioTask(), &QPushButton::clicked,
                       view_->GetPtr(), [this] {
        QString name = ":/sound_task/" + model_->GetLastCorrectAnswerString()
            + ".wav";
        if (model_->IsSoundOn() && model_->CanRequest()) {
          QSound::play(name);
        }
        model_->DecAudioRequest();
      });
}

void Presenter::SetMixedConnections() {
  QPushButton::connect(view_->GetMixedButton(), &QPushButton::clicked,
                       view_->GetPtr(), [this] {
        view_->hide();
        model_->UpdateStatistics();
        View::UpdateAttempts(view_->GetMixed(), 5);
        View::UpdateProgressBar(view_->GetMixed(), 0);
        View::ShowTask(view_->GetMixed());
        GenerateMixedTask();
      });
  QPushButton::connect(View::GetTaskExitButton(view_->GetMixed()),
                       &QPushButton::clicked, view_->GetPtr(), [this] {
        View::ClearTask(view_->GetMixed());
        View::CloseTask(view_->GetMixed());
        view_->setHidden(false);
      });
  QPushButton::connect(view_->GetMixedAudioTask(), &QPushButton::clicked,
                       view_->GetPtr(), [this] {
        QString name = ":/sound_task/" + model_->GetLastCorrectAnswerString()
            + ".wav";
        if (model_->IsSoundOn() && model_->CanRequest()) {
          QSound::play(name);
        }
        model_->DecAudioRequest();
      });
  QPushButton::connect(View::GetTaskReadyButton(view_->GetMixed()),
                       &QPushButton::clicked, view_->GetPtr(), [this] {
        bool win = IsWin(view_->GetMixed());
        UpdateTasks(view_->GetMixed(), win);
        if (win) {
          GenerateMixedTask();
        }
      });
}

void Presenter::UpdateTasks(TaskWindow* task, bool win) {
  if (win) {
    if (model_->IsSoundOn()) {
      QSound::play(":/win_sound.wav");
    }
    model_->IncCorrectAnswers();
    View::UpdateProgressBar(task, model_->GetCorrectAnswers() * 10);
    View::ClearTask(task);

    if (model_->GetCorrectAnswers() == 10) {
      View::CloseTask(task);
      view_->ShowWinScenePickAnOption();
      model_->UpdateScore();
      view_->SetScore(model_->GetScore().toString());
    }
  } else {
    if (model_->IsSoundOn()) {
      QSound::play(":/lose_sound.wav");
    }
    model_->DecAttempts();
    View::UpdateAttempts(task, model_->GetAttempts());

    if (model_->GetAttempts() == 0) {
      view_->setHidden(false);
      View::CloseTask(task);
    }
    View::TaskShowAnswer(task, model_->GetLastCorrectAnswerString());
  }
}

void Presenter::StartTask(tasks_types::TasksTypes type, TaskWindow* window) {
  view_->hide();
  model_->UpdateStatistics();
  View::UpdateAttempts(window, 5);
  View::UpdateProgressBar(window, 0);
  View::ShowTask(window);
  if (type == tasks_types::TasksTypes::kPickAnOption) {
    PickAnOptionTask task = model_->GetPickAnOptionTask();
    view_->WriteTaskPickAnOption(task.quest_, task.answers_);
  } else if (type == tasks_types::TasksTypes::kInputAnswer) {
    QString task = model_->GetInputAnswerTask();
    view_->WriteTasksInputAnswer(task);
  }
}

bool Presenter::IsWin(TaskWindow* task) const {
  return model_->GetLastCorrectAnswerString() == View::GetTaskAnswer(task);
}

void Presenter::GenerateMixedTask() {
  auto type = Random::EnumChoose<tasks_types::TasksTypes>();
  while (type == tasks_types::TasksTypes::kMixed) {
    type = Random::EnumChoose<tasks_types::TasksTypes>();
  }
  View::ClearTask(view_->GetMixed());
  if (type == tasks_types::TasksTypes::kAudio) {
    model_->GenerateAudioTask();
    view_->WriteTasksMixedAudio();
  } else if (type == tasks_types::TasksTypes::kInputAnswer) {
    QString task = model_->GetInputAnswerTask();
    view_->WriteTasksMixedInputAnswer(task);
  } else if (type == tasks_types::TasksTypes::kPickAnOption) {
    PickAnOptionTask task = model_->GetPickAnOptionTask();
    view_->WriteTasksMixedPickAnOption(task.quest_, task.answers_);
  }
}
