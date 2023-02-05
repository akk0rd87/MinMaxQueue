#include "pch.h"
#include "minmaxqueue.h"
TEST(TestCaseMinMaxQueue, MinMaxQueue) {
    MinMaxQueue<int> que;
    que.push(10);
    EXPECT_EQ(10, que.getMin());
    EXPECT_EQ(10, que.getMax());
    EXPECT_EQ(1, que.size());

    que.push(15);
    EXPECT_EQ(10, que.getMin());
    EXPECT_EQ(15, que.getMax());
    EXPECT_EQ(2, que.size());

    que.push(25);
    EXPECT_EQ(10, que.getMin());
    EXPECT_EQ(25, que.getMax());
    EXPECT_EQ(3, que.size());
    EXPECT_EQ(25, que.pop());
    EXPECT_EQ(2, que.size());

    que.push(23);
    EXPECT_EQ(10, que.getMin());
    EXPECT_EQ(23, que.getMax());
    EXPECT_EQ(3, que.size());

    que.push(-15);
    EXPECT_EQ(-15, que.getMin());
    EXPECT_EQ(23, que.getMax());
    EXPECT_EQ(4, que.size());

    EXPECT_EQ(-15, que.pop());
    EXPECT_EQ(10, que.getMin());
    EXPECT_EQ(23, que.getMax());
    EXPECT_EQ(3, que.size());

    EXPECT_EQ(23, que.pop());
    EXPECT_EQ(10, que.getMin());
    EXPECT_EQ(15, que.getMax());
    EXPECT_EQ(2, que.size());

    EXPECT_EQ(15, que.pop());
    EXPECT_EQ(10, que.getMin());
    EXPECT_EQ(10, que.getMax());
    EXPECT_EQ(1, que.size());

    EXPECT_EQ(10, que.pop());
    EXPECT_EQ(0, que.size());
}