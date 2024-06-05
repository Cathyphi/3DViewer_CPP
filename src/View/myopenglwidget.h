#ifndef CPP4_3DVIEWER_V2_0_1_SRC_VIEW_MYOPENGLWIDGET_H
#define CPP4_3DVIEWER_V2_0_1_SRC_VIEW_MYOPENGLWIDGET_H

#define GL_SILENCE_DEPRECATION

#include <QColor>
#include <QMouseEvent>
#include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QtOpenGL>

#include "../Controller/controller.h"
#include "../Controller/observer.h"
#include "../Controller/singleton.h"

//#include "viewer.h"

class MyOpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions {
  Q_OBJECT
 public:
  MyOpenGLWidget(QWidget *parent = nullptr);

  s21::Controller *controller_;
  s21::Singleton *color_ = s21::Singleton::getInstance();

  bool is_open = false;

  bool projection = true;
  int line_width = 1;
  int line_type = 0;

  int vertex_type = 0;
  int vertex_size = 10;

  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;
  void InitColor();

  bool scroll_up = false;

 signals:
  void MouseScaleWidget();
  void MouseMoveWidget(int x_value, int y_value, int z_value);

 protected:
  void wheelEvent(QWheelEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;

 private:
  int wheel_step_up_ = 120;
};

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_VIEW_MYOPENGLWIDGET_H
