#include "model.h"

bool s21::Model::Parser(std::string file_name) {
  std::ifstream file(file_name);
  if (file) {
    std::string line;
    while (std::getline(file, line)) {
      char *str = const_cast<char *>(line.c_str());
      if (*str == 'v') {
        ++str;
        if (*str == ' ') {
          if (!CheckVertex(str)) return false;
          VertexParcer(str);
        }
      } else if (*str == 'f') {
        poligon pol;
        PoligonParcer(str, pol);
        vector_poligon_.push_back(pol);
      }
    }
  } else
    return false;
  if (vector_vertex_.size() < 3 || vector_poligon_.size() < 1) return false;
  return true;
}

bool s21::Model::CheckVertex(char *str) {
  char *str_for_check = str;
  char prev_str = '\0';
  int count_numbers = 0, flag_dot = 0;
  while (*str_for_check) {
    if (*str_for_check == ' ' || *str_for_check == '-' ||
        *str_for_check == '\t' || *str_for_check == '\n' ||
        *str_for_check == '\r') {
      prev_str = *str_for_check;
      ++str_for_check;
    } else if (std::isdigit(*str_for_check)) {
      if (prev_str == ' ' || prev_str == '-') {
        ++count_numbers;
        flag_dot = 0;
      }
      prev_str = *str_for_check;
      ++str_for_check;
    } else if (*str_for_check == '.' && std::isdigit(prev_str) &&
               flag_dot == 0) {
      if (!std::isdigit(*(++str_for_check)))
        return false;
      else
        ++flag_dot;
    } else if (*str_for_check == 'e') {
      if (*(++str_for_check) == '-') --count_numbers;
      prev_str = *str_for_check;
      ++str_for_check;
    } else {
      return false;
    }
  }
  if (count_numbers != 3) return false;
  return true;
}

void s21::Model::VertexParcer(char *str) {
  ++str;
  vertex point = {0, 0, 0};
  point.X = strtod(str, &str);
  point.Y = strtod(str, &str);
  point.Z = strtod(str, &str);
  vector_vertex_.push_back(point);
  MinMax(point);
}

void s21::Model::PoligonParcer(char *str, poligon &pol) {
  while (*str != '\0') {
    if (*str == ' ') {
      ++str;
      if (isdigit(*str)) {
        pol.push_back(strtod(str, &str));
        --str;
      } else {
        ++str;
      }
    }
    ++str;
  }
}

void s21::Model::MinMax(vertex check_point) {
  if (check_point.X < minmaxX_[0]) {
    minmaxX_[0] = check_point.X;
  }
  if (check_point.X > minmaxX_[1]) {
    minmaxX_[1] = check_point.X;
  }

  if (check_point.Y < minmaxY_[0]) {
    minmaxY_[0] = check_point.Y;
  }
  if (check_point.Y > minmaxY_[1]) {
    minmaxY_[1] = check_point.Y;
  }
  if (check_point.Z < minmaxZ_[0]) {
    minmaxZ_[0] = check_point.Z;
  }
  if (check_point.Z > minmaxZ_[1]) {
    minmaxZ_[1] = check_point.Z;
  }
}

size_t s21::Model::PoligonsAmount() { return vector_poligon_.size(); }
poligon s21::Model::GetPoligon(int i) { return vector_poligon_[i]; }
unsigned s21::Model::GetPoligonNum(int i, int j) {
  return vector_poligon_[i][j];
}
size_t s21::Model::PoligonSize(int i) { return vector_poligon_[i].size(); }
size_t s21::Model::VertexAmount() { return vector_vertex_.size(); }
double s21::Model::GetX(int i) { return vector_vertex_[i].X; }
double s21::Model::GetY(int i) { return vector_vertex_[i].Y; }
double s21::Model::GetZ(int i) { return vector_vertex_[i].Z; }

void s21::Model::Centralization() {
  double centerX = minmaxX_[0] + (minmaxX_[1] - minmaxX_[0]) / 2;
  double centerY = minmaxY_[0] + (minmaxY_[1] - minmaxY_[0]) / 2;
  double centerZ = minmaxZ_[0] + (minmaxZ_[1] - minmaxZ_[0]) / 2;
  for (size_t i = 0; i < VertexAmount(); ++i) {
    vector_vertex_[i].X -= centerX;
    vector_vertex_[i].Y -= centerY;
    vector_vertex_[i].Z -= centerZ;
  }
}

void s21::Model::Scaling(double scale_value) {
  for (size_t i = 0; i < VertexAmount(); ++i) {
    vector_vertex_[i].X *= scale_value;
    vector_vertex_[i].Y *= scale_value;
    vector_vertex_[i].Z *= scale_value;
  }
}

void s21::Model::FirstScaling() {
  double max = 0;
  double x = minmaxX_[1] - minmaxX_[0];
  double y = minmaxY_[1] - minmaxY_[0];
  double z = minmaxZ_[1] - minmaxZ_[0];
  x > y ? max = x : max = y;
  if (z > max) max = z;
  double scale_value = 2 / max;
  Scaling(scale_value);
}
void s21::Model::ClearModel() {
  vector_vertex_.clear();
  vector_poligon_.clear();
  minmaxX_[0] = 1000;
  minmaxX_[1] = -1000;
  minmaxY_[0] = 1000;
  minmaxY_[1] = -1000;
  minmaxZ_[0] = 1000;
  minmaxZ_[1] = -1000;
}

void s21::Model::Translation(double newX, double newY, double newZ) {
  for (size_t i = 0; i < VertexAmount(); ++i) {
    vector_vertex_[i].X += newX;
    vector_vertex_[i].Y += newY;
    vector_vertex_[i].Z += newZ;
  }
}

void s21::Model::RotationX(double rotation_angle) {
  for (size_t i = 0; i < VertexAmount(); ++i) {
    double tmpY = vector_vertex_[i].Y;
    double tmpZ = vector_vertex_[i].Z;
    vector_vertex_[i].Y =
        tmpY * cos(rotation_angle) + tmpZ * sin(rotation_angle);
    vector_vertex_[i].Z =
        tmpY * (-sin(rotation_angle)) + tmpZ * cos(rotation_angle);
  }
}

void s21::Model::RotationY(double rotation_angle) {
  for (size_t i = 0; i < VertexAmount(); ++i) {
    double tmpX = vector_vertex_[i].X;
    double tmpZ = vector_vertex_[i].Z;
    vector_vertex_[i].X =
        tmpX * cos(rotation_angle) + tmpZ * sin(rotation_angle);
    vector_vertex_[i].Z =
        tmpX * (-sin(rotation_angle)) + tmpZ * cos(rotation_angle);
  }
}

void s21::Model::RotationZ(double rotation_angle) {
  for (size_t i = 0; i < VertexAmount(); ++i) {
    double tmpX = vector_vertex_[i].X;
    double tmpY = vector_vertex_[i].Y;
    vector_vertex_[i].X =
        tmpX * cos(rotation_angle) - tmpY * sin(rotation_angle);
    vector_vertex_[i].Y =
        tmpX * sin(rotation_angle) + tmpY * cos(rotation_angle);
  }
}
