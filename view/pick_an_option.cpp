#include "pick_an_option.h"

PickAnOption::PickAnOption() {
  setWindowTitle("Pick an option");

  question_ = new QLabel(GetMainWidget());
  question_->setFont(QFont("Arial", 30, QFont::Bold));
  GetMainLayout()->addWidget(question_, 0, 1);
}

void PickAnOption::WriteTasks(const QString& question,
                              const std::vector<QString>& answers) {
  question_->setText(question);

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

void PickAnOption::closeEvent(QCloseEvent* event) {
  CloseTask();
}

size_t PickAnOption::GetCountAnswers() const {
  size_t answer = 0;
  for (auto item: all_check_boxes_) {
    if (item->isChecked()) {
      answer++;
    }
  }
  return answer;
}

QString PickAnOption::GetAnswer() const {
  for (auto item: all_check_boxes_) {
    if (item->isChecked()) {
      return item->text();
    }
  }
  return "";
}

void PickAnOption::CloseTask() {
  for (auto check_box: all_check_boxes_) {
    check_box->close();
  }
  question_->setText("");
}

void PickAnOption::ShowAnswer(const QString& answer) {
  for (auto check_box: all_check_boxes_) {
    check_box->setChecked(false);
  }
  for (auto check_box: all_check_boxes_) {
    if (check_box->text() == answer) {
      check_box->setChecked(true);
      break;
    }
  }
}
