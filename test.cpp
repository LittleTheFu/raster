#include <gtest/gtest.h>
#include <Eigen/Dense>  // 别忘了引入Eigen

// 示例1：演示基本断言
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

// 新增测试：判断两个4D向量是否正交
TEST(EigenVectorTest, OrthogonalCheck) {
  Eigen::Vector4f a(1, 0, 0, 0);  // X轴方向
  Eigen::Vector4f b(0, 1, 0, 0);  // Y轴方向

  float dot = a.dot(b);

  // 断言点积接近0（浮点数比较，给个小容差）
  EXPECT_NEAR(dot, 0.0f, 1e-6f);
}

// 再加一个例子：不正交的情况
TEST(EigenVectorTest, NotOrthogonalCheck) {
  Eigen::Vector4f a(1, 1, 0, 0);
  Eigen::Vector4f b(1, 0, 0, 0);

  float dot = a.dot(b);

  // 点积不为0
  EXPECT_GT(std::abs(dot), 1e-6f);
}
