#include "viewer.h"

#include "ui_viewer.h"

namespace s21 {
Viewer::Viewer(Controller *controller, QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::Viewer), controller_(controller) {
  ui_->setupUi(this);
  this->AddObserver(controller_);
  connect(ui_->widget, &MyOpenGLWidget::MouseScaleWidget, this,
          &s21::Viewer::MouseScale);
  connect(ui_->widget, &MyOpenGLWidget::MouseMoveWidget, this,
          &s21::Viewer::MouseMove);
}

Viewer::~Viewer() { delete ui_; }

void Viewer::on_actionReally_exit_triggered() { close(); }

void Viewer::on_horizontalSlider_MoveX_valueChanged(int value) {
  if (controller_->GetSize().first && controller_->GetSize().second) {
    if (!flag_open_file_) Notify((value - x_) / 100.0f, MOVX);
    x_ = value;
    ui_->widget->update();
  }
}

void Viewer::on_horizontalSlider_MoveY_valueChanged(int value) {
  if (controller_->GetSize().first && controller_->GetSize().second) {
    if (!flag_open_file_) Notify((value - y_) / 100.0f, MOVY);
    y_ = value;
    ui_->widget->update();
  }
}

void Viewer::on_horizontalSlider_MoveZ_valueChanged(int value) {
  if (controller_->GetSize().first && controller_->GetSize().second) {
    if (!flag_open_file_) Notify((value - z_) / 100.0f, MOVZ);
    z_ = value;
    ui_->widget->update();
  }
}

void Viewer::on_horizontalSlider_RotateX_valueChanged(int value) {
  if (controller_->GetSize().first && controller_->GetSize().second) {
    if (!flag_open_file_) Notify((value - angleX_) * M_PI / 180, ROTX);
    angleX_ = value;
    ui_->widget->update();
    if (rotations_.empty() || rotations_.back() != 1) {
      if (rotations_.size() == 3) rotations_.pop_front();
      rotations_.push_back(1);
    }
  }
}

void Viewer::on_horizontalSlider_RotateY_valueChanged(int value) {
  if (controller_->GetSize().first && controller_->GetSize().second) {
    if (!flag_open_file_) Notify((value - angleY_) * M_PI / 180, ROTY);
    angleY_ = value;
    ui_->widget->update();
    if (rotations_.empty() || rotations_.back() != 2) {
      if (rotations_.size() == 3) rotations_.pop_front();
      rotations_.push_back(2);
    }
  }
}

void Viewer::on_horizontalSlider_RotateZ_valueChanged(int value) {
  if (controller_->GetSize().first && controller_->GetSize().second) {
    if (!flag_open_file_) Notify((value - angleZ_) * M_PI / 180, ROTZ);
    angleZ_ = value;
    ui_->widget->update();
    if (rotations_.empty() || rotations_.back() != 3) {
      if (rotations_.size() == 3) rotations_.pop_front();
      rotations_.push_back(3);
    }
  }
}

void Viewer::on_horizontalSlider_Scale_valueChanged(int value) {
  if (controller_->GetSize().first && controller_->GetSize().second) {
    double scale = (value) / 100.0f;
    if (!flag_open_file_) Notify(scale * prev_diff_, SCAL);
    prev_diff_ = 1 / scale;
    ui_->widget->update();
  }
}

void Viewer::on_back_Red_valueChanged(int value) {
  singleton_->SetBackColor(value / 255.0f,
                           std::get<1>(singleton_->GetBackColour()),
                           std::get<2>(singleton_->GetBackColour()));
  ui_->widget->update();
}

void Viewer::on_back_Green_valueChanged(int value) {
  singleton_->SetBackColor(std::get<0>(singleton_->GetBackColour()),
                           value / 255.0f,
                           std::get<2>(singleton_->GetBackColour()));
  ui_->widget->update();
}

void Viewer::on_back_Blue_valueChanged(int value) {
  singleton_->SetBackColor(std::get<0>(singleton_->GetBackColour()),
                           std::get<1>(singleton_->GetBackColour()),
                           value / 255.0f);
  ui_->widget->update();
}

void Viewer::on_line_Red_valueChanged(int value) {
  singleton_->SetLineColor(value / 255.0f,
                           std::get<1>(singleton_->GetLineColour()),
                           std::get<2>(singleton_->GetLineColour()));
  ui_->widget->update();
}

void Viewer::on_line_Green_valueChanged(int value) {
  singleton_->SetLineColor(std::get<0>(singleton_->GetLineColour()),
                           value / 255.0f,
                           std::get<2>(singleton_->GetLineColour()));
  ui_->widget->update();
}

void Viewer::on_line_Blue_valueChanged(int value) {
  singleton_->SetLineColor(std::get<0>(singleton_->GetLineColour()),
                           std::get<1>(singleton_->GetLineColour()),
                           value / 255.0f);
  ui_->widget->update();
}

void Viewer::on_point_Red_valueChanged(int value) {
  singleton_->SetPointColor(value / 255.0f,
                            std::get<1>(singleton_->GetPointColour()),
                            std::get<2>(singleton_->GetPointColour()));
  ui_->widget->update();
}

void Viewer::on_point_Green_valueChanged(int value) {
  singleton_->SetPointColor(std::get<0>(singleton_->GetPointColour()),
                            value / 255.0f,
                            std::get<2>(singleton_->GetPointColour()));
  ui_->widget->update();
}

void Viewer::on_point_Blue_valueChanged(int value) {
  singleton_->SetPointColor(std::get<0>(singleton_->GetPointColour()),
                            std::get<1>(singleton_->GetPointColour()),
                            value / 255.0f);
  ui_->widget->update();
}

void Viewer::on_pushButton_File_clicked() {
  flag_open_file_ = true;
  QString path =
      QFileDialog::getOpenFileName(this, "Choose OBJ file", "/Users/",
                                   "OBJ Files (*.obj);; All Files (*.*)");
  if (controller_->Open(path.toStdString())) {
    ui_->label->setText(path.split('/').last());
    ui_->widget->is_open = true;
    ui_->label_Lines_count->setText(
        QString::number(controller_->GetSize().second));
    ui_->label_vertex_count->setText(
        QString::number(controller_->GetSize().first));
    ui_->widget->controller_ = controller_;
    InitSliders();
    ui_->widget->InitColor();
    ui_->widget->update();
    flag_open_file_ = false;
    mouse_move_ = true;
  } else {
    ui_->label->setText(" INCORRECT FILE!!!");
    ui_->widget->is_open = false;
  }
}

void Viewer::on_radioButton_Central_toggled(bool checked) {
  if (checked == true) ui_->widget->projection = true;
  ui_->widget->update();
}

void Viewer::on_radioButton_Parallel_toggled(bool checked) {
  if (checked == true) ui_->widget->projection = false;
  ui_->widget->update();
}

void Viewer::on_radioButton_Vert_No_toggled(bool checked) {
  if (checked == true) ui_->widget->vertex_type = 0;
  ui_->widget->update();
}

void Viewer::on_radioButton_Vert_Crcl_toggled(bool checked) {
  if (checked == true) ui_->widget->vertex_type = 1;
  ui_->widget->update();
}

void Viewer::on_radioButton_Vert_Sqr_toggled(bool checked) {
  if (checked == true) ui_->widget->vertex_type = 2;
  ui_->widget->update();
}

void Viewer::on_radioButton_Line_Solid_toggled(bool checked) {
  if (checked == true) ui_->widget->line_type = 0;
  ui_->widget->update();
}

void Viewer::on_radioButton_LineStipple_toggled(bool checked) {
  if (checked == true) ui_->widget->line_type = 1;
  ui_->widget->update();
}

void Viewer::on_horizontalSlider_pxLine_valueChanged(int value) {
  ui_->widget->line_width = value;
  ui_->horizontalSlider_pxLine->setValue(value);
  ui_->widget->update();
}

void Viewer::on_horizontalSlider_pxVert_valueChanged(int value) {
  ui_->widget->vertex_size = value;
  ui_->horizontalSlider_pxVert->setValue(value);
  ui_->widget->update();
}

void Viewer::on_pushButton_jpeg_clicked() {
  QPixmap viewer = ui_->widget->grab();
  QString Path = QFileDialog::getSaveFileName(this, NULL, NULL, "jpeg(*.jpeg)");
  if (!Path.isNull()) viewer.save(Path);
}

void Viewer::on_pushButton_bmp_clicked() {
  QPixmap viewer = ui_->widget->grab();
  QString Path = QFileDialog::getSaveFileName(this, NULL, NULL, "bmp(*.bmp)");
  if (!Path.isNull()) viewer.save(Path);
}

void Viewer::on_pushButton_save_clicked() {
  QSettings settings_("settings_Viewer", "Conf");
  settings_.setValue("X_translation", ui_->horizontalSlider_MoveX->value());
  settings_.setValue("Y_translation", ui_->horizontalSlider_MoveY->value());
  settings_.setValue("Z_translation", ui_->horizontalSlider_MoveZ->value());
  settings_.setValue("X_rotation", ui_->horizontalSlider_RotateX->value());
  settings_.setValue("Y_rotation", ui_->horizontalSlider_RotateY->value());
  settings_.setValue("Z_rotation", ui_->horizontalSlider_RotateZ->value());
  settings_.setValue("Scale", ui_->horizontalSlider_Scale->value());
  settings_.setValue("Edge_size", ui_->horizontalSlider_pxLine->value());
  settings_.setValue("Vertex_size", ui_->horizontalSlider_pxVert->value());
  settings_.setValue("Dotten", ui_->radioButton_Vert_No->isChecked());
  settings_.setValue("Dotten2", ui_->radioButton_Vert_Crcl->isChecked());
  settings_.setValue("Dotten3", ui_->radioButton_Vert_Sqr->isChecked());
  settings_.setValue("Parallel", ui_->radioButton_Parallel->isChecked());
  settings_.setValue("Central", ui_->radioButton_Central->isChecked());
  settings_.setValue("LineStipple", ui_->radioButton_LineStipple->isChecked());
  settings_.setValue("Line_Solid", ui_->radioButton_Line_Solid->isChecked());
  settings_.setValue("back_color", ui_->back_Red->value());
  settings_.setValue("back_color1", ui_->back_Green->value());
  settings_.setValue("back_color2", ui_->back_Blue->value());
  settings_.setValue("line_color", ui_->line_Red->value());
  settings_.setValue("line_color1", ui_->line_Green->value());
  settings_.setValue("line_color2", ui_->line_Blue->value());
  settings_.setValue("point_color", ui_->point_Red->value());
  settings_.setValue("point_color1", ui_->point_Green->value());
  settings_.setValue("point_color2", ui_->point_Blue->value());

  settings_.setValue("text", ui_->label->text());
  QMessageBox::information(this, "Сохранение настроек",
                           "Сохранение настроек выполнено успешно");
}

void Viewer::on_pushButton_load_clicked() {
  QSettings settings_("settings_Viewer", "Conf");
  ui_->label->setText(settings_.value("text", "").toString());
  set_filename_ = ui_->label->text();
  ui_->gif_label->setText(set_filename_.split('/').last());
  ui_->horizontalSlider_MoveX->setValue(
      settings_.value("X_translation", 0).toInt());
  ui_->horizontalSlider_MoveY->setValue(
      settings_.value("Y_translation", 0).toInt());
  ui_->horizontalSlider_MoveZ->setValue(
      settings_.value("Z_translation", 0).toInt());

  while (!rotations_.empty()) {
    int num = rotations_.at(rotations_.size() - 1);
    rotations_.pop_back();
    if (num == 1)
      ui_->horizontalSlider_RotateX->setValue(
          settings_.value("X_rotation", 0).toInt());
    if (num == 2)
      ui_->horizontalSlider_RotateY->setValue(
          settings_.value("Y_rotation", 0).toInt());
    if (num == 3)
      ui_->horizontalSlider_RotateZ->setValue(
          settings_.value("Z_rotation", 0).toInt());
  }

  ui_->horizontalSlider_Scale->setValue(settings_.value("Scale", 0).toInt());
  ui_->horizontalSlider_pxLine->setValue(
      settings_.value("Edge_size", 0).toInt());
  ui_->horizontalSlider_pxVert->setValue(
      settings_.value("Vertex_size", 0).toInt());

  ui_->radioButton_Vert_No->toggled(settings_.value("Dotten").toBool());
  ui_->radioButton_Vert_Crcl->toggled(settings_.value("Dotten2").toBool());
  ui_->radioButton_Vert_Sqr->toggled(settings_.value("Dotten3").toBool());

  ui_->radioButton_Parallel->toggled(settings_.value("Parallel").toBool());
  ui_->radioButton_Central->toggled(settings_.value("Central").toBool());

  ui_->radioButton_LineStipple->toggled(
      settings_.value("LineStipple").toBool());
  ui_->radioButton_Line_Solid->toggled(settings_.value("Line_Solid").toBool());

  ui_->radioButton_Vert_No->setChecked(settings_.value("Dotten").toBool());
  ui_->radioButton_Vert_Crcl->setChecked(settings_.value("Dotten2").toBool());
  ui_->radioButton_Vert_Sqr->setChecked(settings_.value("Dotten3").toBool());

  ui_->radioButton_Parallel->setChecked(settings_.value("Parallel").toBool());
  ui_->radioButton_Central->setChecked(settings_.value("Central").toBool());

  ui_->radioButton_LineStipple->setChecked(
      settings_.value("LineStipple").toBool());
  ui_->radioButton_Line_Solid->setChecked(
      settings_.value("Line_Solid").toBool());

  ui_->back_Red->setValue(settings_.value("back_color").toInt());
  ui_->back_Green->setValue(settings_.value("back_color1").toInt());
  ui_->back_Blue->setValue(settings_.value("back_color2").toInt());

  ui_->line_Red->setValue(settings_.value("line_color").toInt());
  ui_->line_Green->setValue(settings_.value("line_color1").toInt());
  ui_->line_Blue->setValue(settings_.value("line_color2").toInt());

  ui_->point_Red->setValue(settings_.value("point_color").toInt());
  ui_->point_Green->setValue(settings_.value("point_color1").toInt());
  ui_->point_Blue->setValue(settings_.value("point_color2").toInt());
}

void Viewer::on_pushButton_gif_clicked() {
  gif_filename_ = QFileDialog::getSaveFileName(this, "Сохранить файл", nullptr,
                                               "Image(*.gif)");
  if (gif_filename_.isNull()) return;
  gif_ = new QGifImage;
  gif_->setDefaultDelay(1000 / gif_fps_);
  start_time_ = 0, tmp_time_ = 1000 / gif_fps_;
  timer_ = new QTimer(this);
  connect(timer_, SIGNAL(timeout()), this, SLOT(oneGif()));
  timer_->start(1000 / gif_fps_);
  this->ui_->pushButton_gif->setEnabled(false);
  this->ui_->gif_label->setText("идет запись GIF файла");
}

void Viewer::oneGif() {
  if (start_time_ == tmp_time_) {
    QPixmap screenGIF(this->ui_->widget->size());
    this->ui_->widget->render(&screenGIF);

    QImage image = screenGIF.toImage();
    image = image.scaled(640, 480, Qt::KeepAspectRatio);
    image = image.copy((image.width() - 640) / 2, 0, 640, 480);
    gif_->addFrame(image, 1000 / gif_fps_);
    time_print_ = (float)start_time_ / 1e3;
    tmp_time_ += 1000 / gif_fps_;
  }
  if (start_time_ == 1000 * gif_length_) {
    gif_->save(gif_filename_);
    timer_->stop();
    disconnect(timer_, SIGNAL(timeout()), this, SLOT(oneGif()));
    delete gif_;
    delete timer_;
    this->ui_->pushButton_gif->setEnabled(true);
    this->ui_->gif_label->setText("GIF файл записан");
  }
  start_time_ += 1000 / gif_fps_;
}

void Viewer::InitSliders() {
  ui_->horizontalSlider_MoveX->setValue(50.0);
  ui_->horizontalSlider_MoveY->setValue(50.0);
  ui_->horizontalSlider_MoveZ->setValue(50.0);
  ui_->horizontalSlider_RotateX->setValue(180.0);
  ui_->horizontalSlider_RotateY->setValue(180.0);
  ui_->horizontalSlider_RotateZ->setValue(180.0);
  ui_->horizontalSlider_Scale->setValue(100.0);
  ui_->horizontalSlider_pxLine->setValue(1.0);
  ui_->horizontalSlider_pxVert->setValue(10.0);
  ui_->back_Red->setValue(127);
  ui_->back_Green->setValue(127);
  ui_->back_Blue->setValue(127);
  ui_->line_Green->setValue(127);
  ui_->line_Red->setValue(127);
  ui_->line_Blue->setValue(127);
  ui_->point_Red->setValue(127);
  ui_->point_Green->setValue(127);
  ui_->point_Blue->setValue(127);
  on_radioButton_Central_toggled(true);
  ui_->radioButton_Central->setChecked(true);
  on_radioButton_Line_Solid_toggled(true);
  ui_->radioButton_Line_Solid->setChecked(true);
  on_radioButton_Vert_No_toggled(true);
  ui_->radioButton_Vert_No->setChecked(true);
}

void Viewer::MouseScale() {
  if (mouse_move_ == true) {
    int prev_value = ui_->horizontalSlider_Scale->value();
    if (ui_->widget->scroll_up == true) {
      ui_->horizontalSlider_Scale->setValue(prev_value + 10);
    } else {
      ui_->horizontalSlider_Scale->setValue(prev_value - 10);
    }
  }
}

void Viewer::MouseMove(int x_value, int y_value, int z_value) {
  if (mouse_move_ == true) {
    if (x_value == 0) x_value = ui_->horizontalSlider_MoveX->value();
    if (y_value == 0) y_value = ui_->horizontalSlider_MoveY->value();
    if (z_value == 0) z_value = ui_->horizontalSlider_MoveZ->value();
    ui_->horizontalSlider_MoveX->setValue(x_value);
    ui_->horizontalSlider_MoveY->setValue(y_value);
    ui_->horizontalSlider_MoveZ->setValue(z_value);
  }
}

}  // namespace s21
