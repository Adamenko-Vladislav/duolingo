#include "win_scene.h"

WinScene::WinScene(const QString& file_name) :
    win_widget_(new QWidget(this)),
    finish_(new QPushButton(win_widget_)),
    win_layout_(new QGridLayout),
    movie_label_(new QLabel(win_widget_)),
    movie_(new QMovie(file_name)) {

  setWindowTitle("You won!");

  movie_label_->resize(1000, 900);
  movie_label_->setMovie(movie_);
  movie_->start();

  CustomButton(finish_, "Finish task", QColor(Qt::green));

  win_layout_->addWidget(movie_label_, 0, 0);
  win_layout_->addWidget(finish_, 1, 0);
  win_widget_->setLayout(win_layout_);
  setCentralWidget(win_widget_);
  setFixedSize(1000, 900);
}
