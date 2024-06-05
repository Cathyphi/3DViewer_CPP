#ifndef CPP4_3DVIEWER_V2_0_1_SRC_CONTROLLER_OBSERVER_H_
#define CPP4_3DVIEWER_V2_0_1_SRC_CONTROLLER_OBSERVER_H_

#include <iostream>
#include <string>
#include <vector>

namespace s21 {

/**
 *@brief Класс наблюдатель. Отслеживание перемещение кнопок масштабирвоания,
 *перемещения и вращения модели в классе Viewer
 */
class Observer {
 public:
  /**
   *@brief Дефолтный деструктор класса Observer
   */
  virtual ~Observer() = default;
  /**
   *@brief Виртуальный метод, хранящий значение коэффициента изменения и тип
   *сигнала
   *@param value коэффициента изменения
   *@param signal тип сигнала (MOVX, MOVY, MOVZ, SCAL, ROTX, ROTY, ROTZ)
   */
  virtual void OnNotify(double value, int signal) = 0;
};

/**
 *@brief Класс Observable. Позволяет создавать массив классов, которым
 *передаюстя сигналы изменений в классе Observer
 */
class Observable {
 public:
  /**
   *@brief Виртуальный дефолтный деструктор класса Observer
   */
  virtual ~Observable() = default;

  /**
   *@brief Метод добавления наблючателя в массив
   *@param o - указатель на объект класса Observer, который необходимо добавить
   */
  void AddObserver(Observer *o) { observers_.push_back(o); }

  /**
   *@brief Метод удаления наблючателя из массива
   *@param o - указатель на объект класса Observer, который необходимо удалить
   */
  void RemoveObserver(Observer *o) {
    observers_.erase(std::remove(observers_.begin(), observers_.end(), o));
  }

 protected:
  /**
   *@brief Метод, отправляющий всем наблюдателям из массива наблюдателей сигнал
   *об изменениях в классе Observer
   *@param value коэффициента изменения
   *@param signal тип сигнала (MOVX, MOVY, MOVZ, SCAL, ROTX, ROTY, ROTZ)
   */
  void Notify(double value, int signal) {
    for (auto *o : observers_) {
      o->OnNotify(value, signal);
    }
  }

 private:
  std::vector<s21::Observer *> observers_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_CONTROLLER_OBSERVER_H_
