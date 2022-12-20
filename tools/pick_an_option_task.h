#pragma once

#include <QString>

#include <utility>
#include <vector>

struct PickAnOptionTask {
  PickAnOptionTask(QString quest,
                   std::vector<QString> answers) :
      quest_(std::move(quest)),
      answers_(std::move(answers)) {
  }

  QString quest_;
  std::vector<QString> answers_;
};
