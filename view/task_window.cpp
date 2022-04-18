#include "task_window.h"

TaskWindow::TaskWindow() :
    main_widget_(new QWidget()),
    main_layout_(new QGridLayout),
    ready_(new QPushButton(main_widget_)),
    attempts_(new QLabel(main_widget_)),
    progress_(new QProgressBar(main_widget_)),
    exit_(new QPushButton(main_widget_)) {
  Qt::WindowFlags flags = windowFlags();
  Qt::WindowFlags closeFlag = Qt::WindowCloseButtonHint;
  flags = flags & (~closeFlag);
  setWindowFlags(flags);

  QPalette window_palette = this->palette();
  window_palette.setColor(QPalette::Window, Qt::darkCyan);
  setPalette(window_palette);

  attempts_->setText("You have 5 attempts left");
  attempts_->setFont(QFont("Arial", 20, QFont::Bold));

  progress_->setValue(0);
  progress_->setTextVisible(true);
  progress_->setFormat("Your progress 0%");
  progress_->setFont(QFont("Arial", 20, QFont::Bold));
  progress_->setMaximumWidth(400);

  exit_->setMaximumHeight(200);
  ready_->setMaximumHeight(200);

  resize(maximumSize());

  CustomAllButtons();
  SetLayout();
}

void TaskWindow::CustomAllButtons() {
  CustomButton(ready_, "Ready", QColor(Qt::green));
  CustomButton(exit_, "Finish task", QColor(Qt::red));
}

void TaskWindow::SetLayout() {
  main_layout_->addWidget(progress_, 0, 0);
  main_layout_->addWidget(attempts_, 1, 0);
  main_layout_->addWidget(ready_, 99, 0);
  main_layout_->addWidget(exit_, 99, 1);
  main_widget_->setLayout(main_layout_);
  setCentralWidget(main_widget_);
}
