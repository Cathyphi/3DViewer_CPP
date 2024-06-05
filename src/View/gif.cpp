
#include "gif.h"

GIF::GIF(QWidget *parent)
    : QWidget(parent), ui(new Ui::GIF), m_movie(":/loading.gif") {
  ui->setupUi(this);

  ui->lbMovie->setMovie(&m_movie);

  connect(ui->bnStart, SIGNAL(clicked(bool)), &m_movie, SLOT(start()));
  connect(ui->bnStop, SIGNAL(clicked(bool)), &m_movie, SLOT(stop()));
}

GIF::~GIF() { delete ui; }
