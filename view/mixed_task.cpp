#include "mixed_task.h"

Mixed::Mixed() {
  setWindowTitle("Mixed");

  question_ = new QLabel(GetMainWidget());
  audio_ = new QPushButton(GetMainWidget());
  input_answer_ = new QTextEdit(GetMainWidget());

  CustomButton(audio_, "Listen", QColor(Qt::red));
  input_answer_->setFont(QFont("Arial", 30, QFont::Bold));
  input_answer_->setText("");

  question_->setFont(QFont("Arial", 30, QFont::Bold));

  question_->close();
  audio_->close();
  input_answer_->close();
}

QString Mixed::GetAnswer() const {
  QString answer;
  switch (current_task_) {
    case tasks_types::TasksTypes::kPickAnOption:
      for (auto item: all_check_boxes_) {
        if (item->isChecked()) {
          answer = item->text();
          break;
        }
      }
      break;
    case tasks_types::TasksTypes::kInputAnswer:
    case tasks_types::TasksTypes::kAudio:answer = input_answer_->toPlainText();
      break;
  }
  return answer;
}

void Mixed::CloseTask() {
  for (auto to: all_check_boxes_) {
    to->close();
  }
  all_check_boxes_.clear();
  question_->close();
  input_answer_->close();
  audio_->close();
}

void Mixed::ShowAnswer(const QString& answer) {
  switch (current_task_) {
    case tasks_types::TasksTypes::kPickAnOption:
      for (auto check_box: all_check_boxes_) {
        check_box->setChecked(false);
      }
      for (auto check_box: all_check_boxes_) {
        if (check_box->text() == answer) {
          check_box->setChecked(true);
          break;
        }
      }
      break;
    case tasks_types::TasksTypes::kInputAnswer:
    case tasks_types::TasksTypes::kAudio:input_answer_->setText(answer);
      break;
    case tasks_types::TasksTypes::kMixed:break;
  }
}

void Mixed::WritePickAnOptionTask(const QString& question,
                                  const std::vector<QString>& answers) {
  current_task_ = tasks_types::TasksTypes::kPickAnOption;

  question_->show();

  question_->setText(question);
  GetMainLayout()->addWidget(question_, 0, 1);
  all_check_boxes_.clear();
  int row = 1;
  for (const auto& item: answers) {
    all_check_boxes_.push_back(new QCheckBox(GetMainWidget()));
    all_check_boxes_.back()->setText(item);
    all_check_boxes_.back()->setFont(QFont("Arial", 20));

    GetMainLayout()->addWidget(all_check_boxes_.back(), row, 1);
    row++;
  }
}

void Mixed::WriteInputAnswerTask(const QString& question) {
  current_task_ = tasks_types::TasksTypes::kInputAnswer;

  question_->show();
  input_answer_->show();

  question_->setText(question);
  input_answer_->clear();

  GetMainLayout()->addWidget(question_, 0, 1);
  GetMainLayout()->addWidget(input_answer_, 1, 1);
}

void Mixed::WriteAudioTask() {
  current_task_ = tasks_types::TasksTypes::kAudio;

  input_answer_->show();
  audio_->show();

  input_answer_->clear();

  GetMainLayout()->addWidget(audio_, 0, 1);
  GetMainLayout()->addWidget(input_answer_, 1, 1);
}

size_t Mixed::GetCountAnswers() const {
  size_t answer = 0;
  for (auto item: all_check_boxes_) {
    if (item->isChecked()) {
      answer++;
    }
  }
  return answer;
}
