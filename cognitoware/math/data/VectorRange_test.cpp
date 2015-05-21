/*
 * VectorRange_test.cpp
 *
 *  Created on: Jan 18, 2015
 *      Author: Alan Oursland
 */

#include "cognitoware/math/data/Vector.h"
#include "cognitoware/math/data/VectorRange.h"
#include "gtest/gtest.h"

namespace cognitoware {
namespace math {
namespace data {

class VT2 : public Vector<VT2, 2> {
public:
  VT2() : Vector() {}
  VT2(const VT2& v) : Vector(v) {}
  VT2(const VT2&& v) : Vector(v) {}
  VT2(std::vector<double> a) : Vector(std::move(a)) {}
};

TEST(VectorRangeTest, ctor1) {
  VT2 min({1.0, 1.0});
  VT2 max({3.0, 4.0});
  VT2 inside({2.0, 2.0});
  VT2 outside1({2.0, 5.0});
  VT2 outside2({0.0, 2.0});
  VectorRange<VT2> vr(min, max);
  EXPECT_EQ(6, vr.area());
  EXPECT_TRUE(vr.Contains(inside));
  EXPECT_FALSE(vr.Contains(outside1));
  EXPECT_FALSE(vr.Contains(outside2));

  std::default_random_engine generator(0);
  VT2 sample1 = vr.Sample(&generator);
  VT2 sample2 = vr.Sample(&generator);
  ASSERT_FALSE(sample1 == sample2);
  for(int i = 0; i < 100; i++) {
    ASSERT_TRUE(vr.Contains(vr.Sample(&generator)));
  }
}

}  // namespace data
}  // namespace math
}  // namespace cognitoware