#ifndef CPP4_3DVIEWER_V2_0_1_SRC_MODEL_MODEL_H
#define CPP4_3DVIEWER_V2_0_1_SRC_MODEL_MODEL_H

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

/**
 * @brief Структура, хранящая одну координату по осям X, Y, Z
 * @param X значение по оси X
 * @param Y значение по оси Y
 * @param Z значение по оси Z
 */

struct vertex {
  double X;
  double Y;
  double Z;
};

/**
 * @brief Структура, хранящая полигон, состоящий из нескольких вершин
 */
using poligon = std::vector<unsigned>;

namespace s21 {

/**
 *@brief Класс модель, содержащую в себе бизнес-логику, представление - форму
 *пользовательского интерфейса для осуществления взаимодействия с программой
 */
class Model {
 public:
  /**
   * @brief Дефолтный коструктор для класса Model
   */
  Model() = default;
  /**
   * @brief Деструктор для класса Model
   */
  ~Model() = default;

  /**
   * @brief Метод для сбора и структурирования информации из объектного файла
   * @param file_name название объектного файла
   */
  bool Parser(std::string file_name);

  /**
   * @brief Метод для сбора и структурирования координат вершин в файле
   * @param str указатель на строку объектного файла
   */
  void VertexParcer(char *str);

  /**
   * @brief Метод для сбора и структурирования вершин в полигонах
   * @param str указатель на строку объектного файла
   */
  void PoligonParcer(char *str, poligon &pol);

  /**
   * @brief Метод для определения минимального  и максимального значения
   * координат X, Y, Z среди всех имеющихся вершин
   * @param check_point структура, хранящая координаты проверяемой вершины
   */
  void MinMax(vertex check_point);

  /**
   * @brief Геттер для колличества полигонов в объектном файле
   */
  size_t PoligonsAmount();

  /**
   * @brief Геттер для i-го полигона в объектном файле
   * @param i номер элемента массива полиговон
   */
  poligon GetPoligon(int i);

  /**
   * @brief Геттер для j-ой вершины i-го полигона в объектном файле
   * @param i номер элемента массива полиговон
   * @param j номер элемента массива вершин в i-ом полигоне
   */
  unsigned GetPoligonNum(int i, int j);

  /**
   * @brief Геттер для колличества вершин в i-ом полигоне
   * @param i номер элемента массива полиговон
   */
  size_t PoligonSize(int i);

  /**
   * @brief Геттер для колличества вершин в объектном файле
   */
  size_t VertexAmount();

  /**
   * @brief Геттер для координаты Х в i-ой вершине
   * @param i номер вершины
   */
  double GetX(int i);

  /**
   * @brief Геттер для координаты Y в i-ой вершине
   * @param i номер вершины
   */
  double GetY(int i);

  /**
   * @brief Геттер для координаты Z в i-ой вершине
   * @param i номер вершины
   */
  double GetZ(int i);

  /**
   * @brief Метод для изменения значения вершин с учетом централизации объекта
   */
  void Centralization();
  /**
   * @brief Метод для изменения значения вершин с учетом масштабирования объекта
   * @param scale_value коэффициент масштабирования
   */
  void Scaling(double scale_value);
  /**
   * @brief Метод для изменения значения вершин с учетом масштабирования объекта
   * при открытии объектного файла
   */
  void FirstScaling();
  /**
   * @brief Метод для очищения приватных полей класса
   */
  void ClearModel();

  /**
   * @brief Метод для изменения значения вершин с учетом перемещения объекта по
   * осям X, Y, Z
   * @param newX коэффициент перемещения объекта по оси Х
   * @param newY коэффициент перемещения объекта по оси Y
   * @param newZ коэффициент перемещения объекта по оси Z
   */
  void Translation(double newX, double newY, double newZ);

  /**
   * @brief Метод для изменения значения вершин с учетом вращения объекта по оси
   * Х
   * @param rotation_angle коэффициент вращения
   */
  void RotationX(double rotation_angle);

  /**
   * @brief Метод для изменения значения вершин с учетом вращения объекта по оси
   * Y
   * @param rotation_angle коэффициент вращения
   */
  void RotationY(double rotation_angle);

  /**
   * @brief Метод для изменения значения вершин с учетом вращения объекта по оси
   * Z
   * @param rotation_angle коэффициент вращения
   */
  void RotationZ(double rotation_angle);

  bool CheckVertex(char *str);

 private:
  std::vector<vertex> vector_vertex_;
  std::vector<poligon> vector_poligon_;
  double minmaxX_[2] = {1000, -1000};
  double minmaxY_[2] = {1000, -1000};
  double minmaxZ_[2] = {1000, -1000};
};
}  // namespace s21
#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODEL_MODEL_H
