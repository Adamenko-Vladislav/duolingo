#include "input_answer.h"

InputAnswer::InputAnswer() {
  setWindowTitle("Input Answer");

  question_ = new QLabel(GetMainWidget());
  question_->setFont(QFont("Arial", 30, QFont::Bold));

  input_answer_ = new QTextEdit(GetMainWidget());
  input_answer_->setFont(QFont("Arial", 30, QFont::Bold));

  GetMainLayout()->addWidget(question_, 0, 1);
  GetMainLayout()->addWidget(input_answer_, 1, 1);
}

void InputAnswer::WriteTasks(const QString& question) {
  question_->setText(question);
  input_answer_->clear();
}

void InputAnswer::CloseTask() {
  input_answer_->setText("");
  question_->setText("");
}
