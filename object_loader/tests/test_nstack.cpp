#include "gtest/gtest.h"
#include "geometry.hpp"
#include "nstack.hpp"

TEST(NStack, pushPopFirst){
    NStack<int> stack = NStack<int>(256);
    stack.push(1);
    stack.push(26);
    stack.push(42);
    ASSERT_EQ(stack.pop(), 42);
    ASSERT_EQ(stack.pop(), 26);
}

TEST(NStack, TopFirstSecond){
    NStack<int> stack = NStack<int>(256);
    stack.push(1);
    stack.push(26);
    stack.push(42);
    ASSERT_EQ(stack.top(), 42);
    ASSERT_EQ(stack.top(1), 26);
}

TEST(NStack, PushSecond){
    NStack<int> stack = NStack<int>(256);
    stack.push(1);
    stack.push(26);
    stack.push(42, 1);
    ASSERT_EQ(stack.top(), 26);
    ASSERT_EQ(stack.top(1), 42);
}

TEST(NStack, PopSecond){
    NStack<int> stack = NStack<int>(256);
    stack.push(1);
    stack.push(26);
    stack.push(42);
    ASSERT_EQ(stack.pop(1), 26);
    ASSERT_EQ(stack.top(), 42);
    ASSERT_EQ(stack.top(1), 1);
}