#include <QApplication>

#include "../Controller/facade.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Facade().Show();
  return a.exec();
}
