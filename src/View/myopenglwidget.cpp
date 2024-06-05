#include "myopenglwidget.h"

#include "ui_viewer.h"
//#include "viewer.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) : QOpenGLWidget{parent} {}

void MyOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
}

void MyOpenGLWidget::paintGL() {
  if (line_type == 0) glEnable(GL_LINES);
  if (line_type == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
  }
  glLineWidth(line_width);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (projection == true) {
    glFrustum(-1, 1, -1, 1, 1, 5);
  } else {
    glOrtho(-1, 1, -1, 1, 1, 5);
  }
  glTranslatef(0, 0, -2);
  glMatrixMode(GL_MODELVIEW);
  glClearColor(std::get<0>(color_->GetBackColour()),
               std::get<1>(color_->GetBackColour()),
               std::get<2>(color_->GetBackColour()), 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(std::get<0>(color_->GetLineColour()),
            std::get<1>(color_->GetLineColour()),
            std::get<2>(color_->GetLineColour()));

  if (is_open == true) {
    for (size_t i = 0; i < controller_->GetSize().second - 1; i++) {
      glBegin(GL_LINE_LOOP);
      for (size_t j = 0; j < controller_->PoligonSize(i); j++) {
        glVertex3d(controller_->GetX(controller_->GetPoligonNum(i, j) - 1),
                   controller_->GetY(controller_->GetPoligonNum(i, j) - 1),
                   controller_->GetZ(controller_->GetPoligonNum(i, j) - 1));
      }
      glEnd();
    }
  }
  if (line_type == 0) glDisable(GL_LINES);
  if (line_type == 1) glDisable(GL_LINE_STIPPLE);

  if (vertex_type) {
    if (vertex_type == 1) glEnable(GL_POINT_SMOOTH);
    if (vertex_type == 2) glEnable(GL_POINT_BIT);
    glPointSize(vertex_size);
    glColor3f(std::get<0>(color_->GetPointColour()),
              std::get<1>(color_->GetPointColour()),
              std::get<2>(color_->GetPointColour()));
    glBegin(GL_POINTS);
    if (is_open == true) {
      for (size_t i = 0; i < controller_->GetSize().second; i++) {
        for (size_t j = 0; j < controller_->PoligonSize(i); j++) {
          glVertex3d(controller_->GetX(controller_->GetPoligonNum(i, j) - 1),
                     controller_->GetY(controller_->GetPoligonNum(i, j) - 1),
                     controller_->GetZ(controller_->GetPoligonNum(i, j) - 1));
        }
      }
    }
    glEnd();
    if (vertex_type == 1) glDisable(GL_POINT_SMOOTH);
    if (vertex_type == 2) glDisable(GL_POINT_BIT);
  }
}

void MyOpenGLWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void MyOpenGLWidget::InitColor() {
  color_->SetBackColor(0.5, 0.5, 0.5);
  color_->SetLineColor(0.5, 0.5, 0.5);
  color_->SetPointColor(0.5, 0.5, 0.5);
}

void MyOpenGLWidget::wheelEvent(QWheelEvent *event) {
  if (event->angleDelta().y() == wheel_step_up_) {
    scroll_up = true;
  } else {
    scroll_up = false;
  }
  emit MouseScaleWidget();
}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *event) {
  int position = event->pos().y();
  if (position > 525)
    position = 525 - (position - 525);
  else
    position = 525 + (525 - position);
  if (event->buttons() == Qt::RightButton)
    emit MouseMoveWidget(0, 0, position / 10);
  if (event->buttons() == Qt::LeftButton) {
    //      int position = event->pos().y();
    //      if (position > 525) position = 525 - (position - 525);
    //      else position = 525 + (525 - position);
    emit MouseMoveWidget(event->pos().x() / 10, position / 10, 0);
  }
}
