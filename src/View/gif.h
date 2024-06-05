#ifndef CPP4_3DVIEWER_V2_0_1_SRC_VIEW_GIF_H
#define CPP4_3DVIEWER_V2_0_1_SRC_VIEW_GIF_H

#include <QMovie>
#include <QWidget>

namespace Ui {
class GIF;
}

class GIF : public QWidget {
  Q_OBJECT

 public:
  explicit GIF(QWidget *parent = 0);
  ~GIF();

 private:
  Ui::GIF *ui;

  QMovie m_movie;
};

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_VIEW_GIF_H
