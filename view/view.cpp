#include "view.h"

View::View() :
    main_widget_(new QWidget(this)),
    main_layout_(new QGridLayout),
    score_(new QLabel(main_widget_)),
    pick_an_option_(new QPushButton(main_widget_)),
    input_answer_(new QPushButton(main_widget_)),
    audio_(new QPushButton(main_widget_)),
    mixed_(new QPushButton(main_widget_)),
    exit_(new QPushButton(main_widget_)),
    exit_keys_fst_(new QShortcut(this)),
    exit_keys_scd_(new QShortcut(this)),
    dialog_(new QDialog(this)) {
  win_scene_.setHidden(true);
  resize(maximumSize());

  setWindowIcon(QIcon(std::get<QPixmap>(FileLoader::GetFile(":/icon.png"))));
  setWindowTitle("DuoLingo");

  QPalette window_palette = this->palette();
  window_palette.setColor(QPalette::Window, QColor("#A8F000"));
  setPalette(window_palette);

  CustomAllButtons();

  exit_keys_fst_->setKey(Qt::CTRL + Qt::Key_W);
  exit_keys_scd_->setKey(Qt::CTRL + Qt::Key_F4);
  need_to_close_ = false;

  context_menu_ = new QMenu(tr("Context menu"), this);
  reset_score_second_way_ = context_menu_->addAction("Reset score");

  SetDialog();
  SetLayout();
  show();
}

void View::CreateMenu(const QVariant& complexity,
                      const QVariant& sound,
                      const QVariant& score) {
  settings_ = menuBar()->addMenu("Settings");

  complexity_ = settings_->addMenu("Complexity");
  easy_ = complexity_->addAction("Easy");
  easy_->setCheckable(true);

  hard_ = complexity_->addAction("Hard");
  hard_->setCheckable(true);

  easy_->setChecked(complexity.toString() == "easy");
  hard_->setChecked(complexity.toString() == "hard");

  sound_ = settings_->addAction("Sound");

  sound_->setCheckable(true);
  sound_->setChecked(sound.toString() == "on");
  score_->setText(score.toString());

  reset_score_ = settings_->addAction("Reset score");
}

void View::SetLayout() {
  main_layout_->addWidget(score_, 0, 0);
  main_layout_->addWidget(pick_an_option_, 1, 0);
  main_layout_->addWidget(input_answer_, 1, 1);
  main_layout_->addWidget(audio_, 2, 0);
  main_layout_->addWidget(mixed_, 2, 1);
  main_layout_->addWidget(exit_, 3, 1);

  main_widget_->setLayout(main_layout_);
  setCentralWidget(main_widget_);
}

void View::SetDialog() {
  dialog_layout_ = new QHBoxLayout;

  accept_ = new QPushButton(dialog_);
  deny_ = new QPushButton(dialog_);

  dialog_layout_->addWidget(accept_);
  dialog_layout_->addWidget(deny_);

  accept_->setText("Yes");
  deny_->setText("No");

  dialog_->setWindowTitle("Are you sure?");

  dialog_->setLayout(dialog_layout_);
}

void View::closeEvent(QCloseEvent* event) {
  if (!need_to_close_) {
    dialog_->show();
    event->ignore();
  }
}

void View::mousePressEvent(QMouseEvent* event) {
  if (event->button() != Qt::RightButton) {
    return;
  }
  auto event_pos = event->pos();
  auto label_pos = QPoint(score_->x(), score_->y());
  auto label_size = QPoint(score_->height(), score_->width());
  if (event_pos.x() >= label_pos.x()
      && event_pos.x() <= label_pos.x() + label_size.x()
      && event_pos.y() >= label_pos.y()
      && event_pos.y() <= label_pos.y() + label_size.y()) {
    setContextMenuPolicy(Qt::CustomContextMenu);
    context_menu_->exec(mapToGlobal(event->pos()));
  }
}

void View::CustomAllButtons() {
  CustomButton(pick_an_option_, "Pick-an-Option", QColor(Qt::darkMagenta),
               "Arial", 40, QFont::Weight::Normal);
  CustomButton(input_answer_, "Input-Answer", QColor(255, 192, 203),
               "Arial", 40, QFont::Weight::Normal);
  CustomButton(audio_, "Audio", QColor(Qt::magenta),
               "Arial", 40, QFont::Weight::Normal);
  CustomButton(mixed_, "Mixed", QColor(Qt::red),
               "Arial", 40, QFont::Weight::Normal);
  CustomButton(exit_, "Exit", QColor(Qt::darkRed),
               "Arial", 40, QFont::Weight::Normal);
}

void View::UpdateProgressBar(TaskWindow* window, size_t progress) {
  QString progress_text = "Your progress ";
  progress_text += std::to_string(progress).c_str();
  progress_text += "%";
  window->SetProgressText(progress_text);
  window->UpdateProgress(progress);
}

void View::UpdateAttempts(TaskWindow* window, size_t value) {
  QString text = "You have " + QString::number(value) + " attempts left";
  window->SetAttemptsText(text);
}
