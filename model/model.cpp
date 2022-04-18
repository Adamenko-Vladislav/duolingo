#include "model.h"

#include "presenter.h"

Model::Model(Presenter* controller) :
    presenter_(controller),
    settings_(new QSettings("AdamadaCorporation", "Duolingo")) {
  SetDefaultSettings();
}

void Model::SetDefaultSettings() {
  QJsonDocument source =
      std::get<QJsonDocument>(FileLoader::GetFile(":/default_settings.json"));
  SetDefaultSettings(source, "score");
  SetDefaultSettings(source, "sound");
  SetDefaultSettings(source, "complexity");
}

void Model::SetDefaultSettings(const QJsonDocument& source,
                               const QString& path) {
  if (!settings_->contains(path)) {
    settings_->setValue(path, source[path].toVariant());
  }
}

void Model::ResetEasy() {
  QAction* easy = presenter_->GetEasy();
  QAction* hard = presenter_->GetHard();

  if (easy->isChecked()) {
    hard->setChecked(false);
    settings_->setValue("complexity", "easy");
  } else {
    hard->setChecked(true);
    settings_->setValue("complexity", "hard");
  }
}

void Model::ResetHard() {
  QAction* easy = presenter_->GetEasy();
  QAction* hard = presenter_->GetHard();

  if (hard->isChecked()) {
    easy->setChecked(false);
    settings_->setValue("complexity", "hard");
  } else {
    easy->setChecked(true);
    settings_->setValue("complexity", "easy");
  }
}

void Model::ResetSound() {
  QAction* sound = presenter_->GetSound();

  if (sound->isChecked()) {
    settings_->setValue("sound", "on");
  } else {
    settings_->setValue("sound", "off");
  }
}

void Model::ResetScore() {
  QLabel* label = presenter_->GetScore();
  label->setText("0");
  settings_->setValue("score", 0);
}

PickAnOptionTask Model::GetPickAnOptionTask() {
  QJsonDocument file =
      std::get<QJsonDocument>(FileLoader::GetFile(":/verbs.json"));
  QString name;
  std::vector<QString> answers;

  int count_variants =
      (settings_->value("complexity").toString() == "hard" ? 5 : 3);
  for (int i = 0; i < count_variants; ++i) {
    name = GetRandomVerb();
    answers.emplace_back(GetAllFormsOfVerb(file, name));
  }

  std::shuffle(answers.begin(),
               answers.end(),
               std::mt19937(std::random_device()()));

  last_correct_answer_ = GetAllFormsOfVerb(file, name);
  return {file[name]["translation"].toString(), answers};
}

QVariant Model::GetComplexity() const {
  return settings_->value("complexity");
}

QString Model::GetInputAnswerTask() {
  QString name = GetRandomVerb();
  QJsonDocument file =
      std::get<QJsonDocument>(FileLoader::GetFile(":/verbs.json"));

  if (settings_->value("complexity").toString() == "hard") {
    last_correct_answer_ = GetAllFormsOfVerb(file, name);
    return "Write all forms of verb \"" +
        file[name]["translation"].toString() + "\"";
  } else {
    int need_form = Random::RandomInt(1, 3);
    last_correct_answer_ =
        file[name]["form" + QString::number(need_form)].toString();

    QString question = "Write the " + QString::number(need_form);

    switch (need_form) {
      case 1:question += "st ";
        break;
      case 2:question += "nd ";
        break;
      case 3:question += "rd ";
        break;
    }

    question += "form of verb \"" + file[name]["translation"].toString() + "\"";

    return question;
  }
}

QString Model::GetRandomVerb() {
  return "verb" + QString(std::to_string(Random::RandomInt(0, 179)).c_str());
}

QString Model::GetAllFormsOfVerb(const QJsonDocument& file,
                                 const QString& name) {
  return file[name]["form1"].toString() + " - " + file[name]["form2"].toString()
      + " - " + file[name]["form3"].toString();
}

void Model::GenerateAudioTask() {
  int number = Random::RandomInt(1, 135);
  QJsonDocument file =
      std::get<QJsonDocument>(FileLoader::GetFile(":/sound.json"));
  last_correct_answer_ = file["verb" + QString::number(number)].toString();
  count_audio_ = (settings_->value("complexity").toString() == "hard" ? 3 : 5);
}
