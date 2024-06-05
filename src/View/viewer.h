#ifndef CPP4_3DVIEWER_V2_0_1_SRC_VIEW_VIEWER_H_
#define CPP4_3DVIEWER_V2_0_1_SRC_VIEW_VIEWER_H_

#define SETTINGS_TRAY "settings"
#define SETTINGS "settings_combo"

#define GL_SILENCE_DEPRECATION

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QObject>
#include <QOpenGLWidget>
#include <QSettings>
#include <QTimer>

#include "../Controller/controller.h"
#include "../Controller/observer.h"
#include "../Controller/singleton.h"
#include "QtGifImage/src/gifimage/qgifimage.h"
#include "myopenglwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Viewer;
}
QT_END_NAMESPACE

namespace s21 {

class Viewer : public QMainWindow, public Observable {
  Q_OBJECT

 public:
  Viewer() = default;
  Viewer(Controller *controller, QWidget *parent = nullptr);
  ~Viewer();

 private slots:

  void on_actionReally_exit_triggered();
  void on_horizontalSlider_MoveX_valueChanged(int value);
  void on_horizontalSlider_MoveY_valueChanged(int value);
  void on_horizontalSlider_MoveZ_valueChanged(int value);
  void on_horizontalSlider_RotateX_valueChanged(int value);
  void on_horizontalSlider_RotateY_valueChanged(int value);
  void on_horizontalSlider_RotateZ_valueChanged(int value);
  void on_horizontalSlider_Scale_valueChanged(int value);
  void on_back_Red_valueChanged(int value);
  void on_back_Green_valueChanged(int value);
  void on_back_Blue_valueChanged(int value);
  void on_line_Red_valueChanged(int value);
  void on_line_Green_valueChanged(int value);
  void on_line_Blue_valueChanged(int value);
  void on_point_Red_valueChanged(int value);
  void on_point_Green_valueChanged(int value);
  void on_point_Blue_valueChanged(int value);
  void on_pushButton_File_clicked();
  void on_radioButton_Central_toggled(bool checked);
  void on_radioButton_Parallel_toggled(bool checked);
  void on_radioButton_Vert_No_toggled(bool checked);
  void on_radioButton_Vert_Crcl_toggled(bool checked);
  void on_radioButton_Vert_Sqr_toggled(bool checked);
  void on_radioButton_Line_Solid_toggled(bool checked);
  void on_radioButton_LineStipple_toggled(bool checked);
  void on_horizontalSlider_pxLine_valueChanged(int value);
  void on_horizontalSlider_pxVert_valueChanged(int value);
  void on_pushButton_jpeg_clicked();
  void on_pushButton_bmp_clicked();
  void on_pushButton_load_clicked();
  void on_pushButton_save_clicked();
  void on_pushButton_gif_clicked();
  void oneGif();
  void InitSliders();
  void MouseScale();
  void MouseMove(int x_value, int y_value, int z_value);

 private:
  Ui::Viewer *ui_;
  Controller *controller_;
  Singleton *singleton_ = Singleton::getInstance();

  bool flag_open_file_ = false;

  double prev_diff_ = 1;

  int angleX_ = 180;
  int angleY_ = 180;
  int angleZ_ = 180;

  int x_ = 50;
  int y_ = 50;
  int z_ = 50;

  QSettings *settings_;

  int start_time_, tmp_time_;
  float time_print_;
  const int gif_fps_ = 10, gif_length_ = 5;
  QTimer *timer_;
  QGifImage *gif_;
  QString set_filename_;
  QString gif_filename_;

  std::deque<int> rotations_;

  bool mouse_move_ = false;
};
}  // namespace s21
#endif  // CPP4_3DVIEWER_V2_0_1_SRC_VIEW_VIEWER_H_
