#include <gtest/gtest.h>

#include <iostream>

#include "Controller/Controller.h"
#include "Model/model.h"

s21::Model model;
s21::Controller control(&model);

TEST(file_exist, test_1) {
  std::string str = "Obj/pyramid1.obj";
  bool res = model.Parser(str);
  EXPECT_FALSE(res);
}

TEST(parcer, test_2) {
  std::string str = "Obj/Deer.obj";
  bool res = model.Parser(str);
  EXPECT_TRUE(res);
}

TEST(open_model, test_3) {
  std::string str = "Obj/Cow.obj";
  bool res = control.Open(str);
  EXPECT_TRUE(res);
}

TEST(translation, test_4) {
  double new_value = 0.25;
  std::string str = "Obj/Cow.obj";
  if (model.Parser(str)) model.Translation(new_value, new_value, new_value);
  EXPECT_DOUBLE_EQ(model.GetX(0), 0.55284736989815619);
  EXPECT_DOUBLE_EQ(model.GetY(0), 0.19344381638353703);
  EXPECT_DOUBLE_EQ(model.GetZ(0), 0.091583994304130056);
}

TEST(rotationX, test_5) {
  double new_value = 0.25;
  std::string str = "Obj/Cow.obj";
  if (model.Parser(str)) model.RotationX(new_value);
  EXPECT_DOUBLE_EQ(model.GetX(0), 0.55284736989815619);
  EXPECT_DOUBLE_EQ(model.GetY(0), 0.21008835939230763);
  EXPECT_DOUBLE_EQ(model.GetZ(0), 0.040878103644556539);
}

TEST(rotationY, test_6) {
  double new_value = 0.25;
  std::string str = "Obj/Sphere.obj";
  if (model.Parser(str)) model.RotationY(new_value);
  EXPECT_DOUBLE_EQ(model.GetX(0), 0.54577408869286315);
  EXPECT_DOUBLE_EQ(model.GetY(0), 0.21008835939230763);
  EXPECT_DOUBLE_EQ(model.GetZ(0), -0.097169325779067589);
}

TEST(rotationZ, test_7) {
  double new_value = 0.25;
  std::string str = "Obj/Catana.obj";
  if (model.Parser(str)) model.RotationZ(new_value);
  EXPECT_DOUBLE_EQ(model.GetX(0), 0.47683060207537825);
  EXPECT_DOUBLE_EQ(model.GetY(0), 0.33858389147316059);
  EXPECT_DOUBLE_EQ(model.GetZ(0), -0.097169325779067589);
}

TEST(get_amount, test_8) {
  std::string str = "Obj/Catana.obj";
  if (control.Open(str)) {
    double vert_amount = control.GetSize().first;
    double poli_amount = control.GetSize().second;
    EXPECT_EQ(vert_amount, 6696);
    EXPECT_EQ(poli_amount, 6459);
  }
}

TEST(get_amount_1, test_9) {
  std::string str = "Obj/Hazelnut.obj";
  if (control.Open(str)) {
    double vert_amount = control.GetSize().first;
    double poli_amount = control.GetSize().second;
    EXPECT_EQ(vert_amount, 48304);
    EXPECT_EQ(poli_amount, 39646);
  }
}

TEST(get_amount_2, test_10) {
  std::string str = "Obj/Minicar.obj";
  if (control.Open(str)) {
    double vert_amount = control.GetSize().first;
    double poli_amount = control.GetSize().second;
    EXPECT_EQ(vert_amount, 77745);
    EXPECT_EQ(poli_amount, 107102);
  }
}

TEST(get_error, test_11) {
  std::string str = "Obj/Incorrect.obj";
  EXPECT_FALSE(control.Open(str));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
