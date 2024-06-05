#ifndef CPP4_3D_VIEWER_V2_0_1_SRC_CONTROLLER_SINGLETON_H_
#define CPP4_3D_VIEWER_V2_0_1_SRC_CONTROLLER_SINGLETON_H_

#include <iostream>

namespace s21 {

/**
 *@brief Класс Singleton, гарантирующий, что в однопоточном приложении будет
 *единственный экземпляр данного класса, и предоставляющий глобальную точку
 *доступа к этому экземпляру
 */
class Singleton {
 public:
  /**
   *@brief Метод, проверящий наличие ранее созданного экземпляра класса
   *Singleton при создании нового экземпляра класса. В случае наличия ранее
   *созданного экземпляра класса Singlton возвращает указатель на ранее
   *созданный экземпляр
   */
  static Singleton *getInstance() {
    if (!inst_) {
      inst_ = new Singleton();
    }
    return (inst_);
  }

  /**
   *@brief Сеттер для приватных полей класса Singlton. Устанавливает значения
   *цветов фона в формате RGB
   *@param red значение красного цвета в пространстве RGB
   *@param green  значение зеленого цвета в пространстве RGB
   *@param blue значение синего цвета в пространстве RGB
   */
  void SetBackColor(double red, double green, double blue) {
    back_color_[0] = red;
    back_color_[1] = green;
    back_color_[2] = blue;
  }

  /**
   *@brief Геттер для приватных полей класса Singlton. Возвращает значения
   *цветов фона в формате RGB
   */
  std::tuple<double, double, double> GetBackColour() {
    return std::tuple<double, double, double>(back_color_[0], back_color_[1],
                                              back_color_[2]);
  }

  /**
   *@brief Сеттер для приватных полей класса Singlton. Устанавливает значения
   *цветов линий в формате RGB
   *@param red значение красного цвета в пространстве RGB
   *@param green  значение зеленого цвета в пространстве RGB
   *@param blue значение синего цвета в пространстве RGB
   */
  void SetLineColor(double red, double green, double blue) {
    line_color_[0] = red;
    line_color_[1] = green;
    line_color_[2] = blue;
  }

  /**
   *@brief Геттер для приватных полей класса Singlton. Возвращает значения
   *цветов линий в формате RGB
   */
  std::tuple<double, double, double> GetLineColour() {
    return std::tuple<double, double, double>(line_color_[0], line_color_[1],
                                              line_color_[2]);
  }

  /**
   *@brief Сеттер для приватных полей класса Singlton. Устанавливает значения
   *цветов точек в формате RGB
   *@param red значение красного цвета в пространстве RGB
   *@param green  значение зеленого цвета в пространстве RGB
   *@param blue значение синего цвета в пространстве RGB
   */
  void SetPointColor(double red, double green, double blue) {
    point_color_[0] = red;
    point_color_[1] = green;
    point_color_[2] = blue;
  }

  /**
   *@brief Геттер для приватных полей класса Singlton. Возвращает значения
   *цветов точек в формате RGB
   */
  std::tuple<double, double, double> GetPointColour() {
    return std::tuple<double, double, double>(point_color_[0], point_color_[1],
                                              point_color_[2]);
  }

 protected:
  double back_color_[3];
  double line_color_[3];
  double point_color_[3];

 private:
  inline static Singleton *inst_{nullptr};
  /**
   *@brief Конструктор класса Singleton
   */
  Singleton() {
    for (int i = 0; i < 3; ++i) {
      back_color_[i] = 0.5;
      line_color_[i] = 0.5;
      point_color_[i] = 0.5;
    }
  }
};  // class Singleton

}  // namespace s21

#endif  // CPP4_3D_VIEWER_V2_0_1_SRC_CONTROLLER_SINGLETON_H_
