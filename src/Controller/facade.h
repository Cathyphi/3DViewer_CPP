#ifndef CPP4_3DVIEWER_V2_0_1_SRC_CONTROLLER_FACADE_H
#define CPP4_3DVIEWER_V2_0_1_SRC_CONTROLLER_FACADE_H

#include <../Controller/controller.h>
#include <../Model/model.h>
#include <../View/viewer.h>

namespace s21 {

/**
 *@brief Класс фасад, "скрывающий" от пользователя все логические процессы
 *взаимодействия с программой
 */
class Facade {
 public:
  /**
   * @brief Базовый конструктор класса Fasade
   */
  Facade() {
    model_ = new Model;
    controller_ = new Controller(model_);
    viewer_ = new Viewer(controller_);
  }

  /**
   * @brief Метод для вывода модели на экран
   */
  void Show() { viewer_->show(); }

 private:
  Model *model_;
  Controller *controller_;
  Viewer *viewer_;
};

}  // namespace s21
#endif  // CPP4_3DVIEWER_V2_0_1_SRC_CONTROLLER_FACADE_H
