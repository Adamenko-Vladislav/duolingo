#include "audio_task.h"

AudioTask::AudioTask() {
  setWindowTitle("Audio");

  audio_ = new QPushButton(GetMainWidget());
  CustomButton(audio_, "Listen", QColor(Qt::red));

  answer_ = new QTextEdit(GetMainWidget());
  answer_->setFont(QFont("Arial", 30));
  answer_->setText("");

  GetMainLayout()->addWidget(audio_, 0, 1);
  GetMainLayout()->addWidget(answer_, 1, 1);
}
