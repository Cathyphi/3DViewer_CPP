#ifndef CPP4_3DVIEWER_V2_0_1_SRC_CONTROLLER_CONTROLLER_H_
#define CPP4_3DVIEWER_V2_0_1_SRC_CONTROLLER_CONTROLLER_H_

#include <iostream>

#include "../Model/model.h"
#include "observer.h"

/**
 *@brief Пространство имен s21::
 */

namespace s21 {
enum { MOVX, MOVY, MOVZ, SCAL, ROTX, ROTY, ROTZ };

/**
 *@brief Класс контроллер, осуществляющий модификацию модели по действию
 *пользователя.
 */
class Controller : public Observer {
 public:
  /**
   * @brief Дефолтный деструктор класса Controller
   */
  ~Controller() = default;

  /**
   * @brief Конструктор класса Controller
   * @param model указатель на объект класса Model
   */
  Controller(Model *model) : model_(model) {}

  /**
   * @brief Метод для считывания, заполнения и хранения значений вершин и
   * полигонов из объектного файла
   * @param path путь к объектному файлу
   */
  bool Open(std::string path) {
    ClearModel();
    //    bool res = model_->Parser(path);
    if (model_->Parser(path)) {
      model_->Centralization();
      model_->FirstScaling();
      return true;
    }
    return false;
  }

  /**
   * @brief Геттер для колличества вершин в i-ом полигоне из объета класса Model
   * @param i номер элемента массива полиговон
   */
  size_t PoligonSize(int i) { return model_->PoligonSize(i); }

  /**
   * @brief Геттер для j-ой вершины i-го полигона из объета класса Model
   * @param i номер элемента массива полиговон
   * @param j номер элемента массива вершин в i-ом полигоне
   */
  unsigned GetPoligonNum(int i, int j) { return model_->GetPoligonNum(i, j); }

  /**
   * @brief Геттер для координаты Х в i-ой вершине, хранящейся в объекте класса
   * Model
   * @param i номер вершины
   */
  double GetX(int i) { return model_->GetX(i); }

  /**
   * @brief Геттер для координаты Y в i-ой вершине, хранящейся в объекте класса
   * Model
   * @param i номер вершины
   */
  double GetY(int i) { return model_->GetY(i); }

  /**
   * @brief Геттер для координаты Z в i-ой вершине, хранящейся в объекте класса
   * Model
   * @param i номер вершины
   */
  double GetZ(int i) { return model_->GetZ(i); }

  /**
   * @brief Геттер для колличества вершин и полигонов в объекте класса Model
   */
  std::pair<unsigned, unsigned> GetSize() {
    return std::pair<unsigned, unsigned>(model_->VertexAmount(),
                                         model_->PoligonsAmount());
  }

  /**
   * @brief Метод для отслеживания сигналов класса Observable и реализации
   * перемещений и масстабирования объекта при поступлении сигнала
   * @param value коэффицент изменения модели
   * @param signal тип сигланна, определенный в enum
   */
  void OnNotify(double value, int signal) override {
    if (signal == SCAL) model_->Scaling(value);
    if (signal == MOVX) model_->Translation(value, 0, 0);
    if (signal == MOVY) model_->Translation(0, value, 0);
    if (signal == MOVZ) model_->Translation(0, 0, value);
    if (signal == ROTX) model_->RotationX(value);
    if (signal == ROTY) model_->RotationY(value);
    if (signal == ROTZ) model_->RotationZ(value);
  }

  /**
   * @brief Метод для очищения приватных полей класса Model
   */
  void ClearModel() { model_->ClearModel(); }

 private:
  Model *model_;
};
}  // namespace s21
#endif  // CPP4_3DVIEWER_V2_0_1_SRC_CONTROLLER_CONTROLLER_H_
