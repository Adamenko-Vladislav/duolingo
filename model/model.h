#pragma once

#include <QAction>
#include <QSettings>

#include <memory>

#include "pick_an_option_task.h"
#include "tools.h"

class Presenter;

class Model {
 public:
  explicit Model(Presenter*);

  QVariant GetComplexity() const;

  QVariant GetSoundStatus() const {
    return settings_->value("sound");
  }

  QVariant GetScore() const {
    return settings_->value("score");
  }

  void ResetEasy();
  void ResetHard();
  void ResetSound();
  void ResetScore();

  bool IsSoundOn() {
    return settings_->value("sound").toString() == "on";
  }

  QString GetLastCorrectAnswerString() const {
    return last_correct_answer_;
  }

  void DecAudioRequest() {
    count_audio_--;
  }

  bool CanRequest() const {
    return count_audio_ > 0;
  }

  void UpdateStatistics() {
    attempts_ = 5;
    correct_answers_ = 0;
  }

  void IncCorrectAnswers() {
    correct_answers_++;
  }

  void DecAttempts() {
    attempts_--;
  }

  size_t GetAttempts() const {
    return attempts_;
  }

  size_t GetCorrectAnswers() const {
    return correct_answers_;
  }

  void UpdateScore() {
    size_t score = settings_->value("score").toInt();
    if (GetComplexity().toString() == "hard") {
      score += 10;
    } else {
      score += 5;
    }
    settings_->setValue("score", QString::number(score));
  }

  PickAnOptionTask GetPickAnOptionTask();
  QString GetInputAnswerTask();

  static QString GetRandomVerb();
  static QString GetAllFormsOfVerb(const QJsonDocument& file,
                                   const QString& name);

  void GenerateAudioTask();

 private:
  void SetDefaultSettings();

  void SetDefaultSettings(const QJsonDocument&, const QString&);

  std::shared_ptr<Presenter> presenter_;
  QSettings* settings_;
  QString last_correct_answer_;

  size_t attempts_;
  size_t correct_answers_;
  int32_t count_audio_;
};
