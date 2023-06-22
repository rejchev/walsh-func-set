#include <gtest/gtest.h>

#include "../walshf32.h"

double_t calc_x(const double_t& t, const int32_t& T);
void print(const int32_t&, const int32_t&, const int32_t&);

using namespace walshf;

// wal(0, t/T) = pal(0, t/T) = 1
TEST(WALSH, W0)
{
    const int32_t x = 1;
    const int32_t function = 0;
    const int32_t expected = 1;

    EXPECT_EQ(expected, wal(function, x));
}

// wal(1, t/T) = pal(1, t/T) = radf(0, t/T)
TEST(WALSH, W1)
{
    const int32_t x = 2;
    const int32_t function = 1;

    for(int i = 1; i <= x; i++)
        EXPECT_EQ(((i - 1) % 2 == 0 ? 1 : -1), wal(function, calc_x(double_t(i), x)));
}

// wal(2, t/T) = pal(3, t/T) = radf(1,t/T) * radf(0, t/T)
TEST(WALSH, W2)
{
    const int32_t x = 4;
    const int32_t function = 2;

    std::vector<int32_t> expected {
            1, -1, -1, 1
    };

    for(int i = 1, res; i <= x; i++)
    {
        res = wal(function, calc_x(double_t(i), x));
        print(i, expected[i - 1], res);

        EXPECT_EQ(expected[i-1], res);
    }
}

// wal(3, t/T) = pal(2, t/T) = radf(1,t/T) [t/T = 1/4]
TEST(WALSH, W3)
{
    const int32_t x = 8;
    const int32_t function = 3;

    std::vector<int32_t> expected {
            1, 1, -1, -1, 1, 1, -1, -1
    };

    for(int i = 1, res; i <= x; i++)
    {
        res = wal(function, calc_x(double_t(i), x));
        print(i, expected[i - 1], res);

        EXPECT_EQ(expected[i-1], res);
    }
}

// wal(4, t/T) = pal(6, t/T) = radf(2, t/T) * radf(1, t/T)
TEST(WALSH, W4)
{
    const int32_t x = 8;
    const int32_t function = 4;

    std::vector<int32_t> expected {
            1, -1, -1, 1, 1, -1, -1, 1
    };

    for(int i = 1, res; i <= x; i++)
    {
        res = wal(function, calc_x(double_t(i), x));
        print(i, expected[i - 1], res);

        EXPECT_EQ(expected[i-1], res);
    }
}

// wal(5, t/T) = pal(7, t/T) = radf(2, t/T) * radf(1, t/T) * radf(0, t/T)
TEST(WALSH, W5)
{
    const int32_t x = 8;
    const int32_t function = 5;

    std::vector<int32_t> expected {
            1, -1, -1, 1, -1, 1, 1, -1
    };

    for(int i = 1, res; i <= x; i++)
    {
        res = wal(function, calc_x(double_t(i), x));
        print(i, expected[i - 1], res);

        EXPECT_EQ(expected[i-1], res);
    }
}

// wal(6, t/T) = pal(5, t/T) = radf(2, t/T) * radf(0, t/T)
TEST(WALSH, W6)
{
    const int32_t x = 8;
    const int32_t function = 6;

    std::vector<int32_t> expected {
            1, -1, 1, -1, -1, 1, -1, 1
    };

    for(int i = 1, res; i <= x; i++)
    {
        res = wal(function, calc_x(double_t(i), x));
        print(i, expected[i - 1], res);

        EXPECT_EQ(expected[i-1], res);
    }
}

// wal(7, t/T) = pal(4, t/T) = radf(2, t/T) [t/T = 1/8]
TEST(WALSH, W7)
{
    const int32_t x = 8;
    const int32_t function = 7;

    std::vector<int32_t> expected {
            1, -1, 1, -1, 1, -1, 1, -1
    };

    for(int i = 1, res; i <= x; i++)
    {
        res = wal(function, calc_x(double_t(i), x));
        print(i, expected[i - 1], res);

        EXPECT_EQ(expected[i-1], res);
    }
}

TEST(WALSH, SEQ1_8)
{
    const int32_t n = 8;
    const int32_t functionNumber = 1;

    const double_t dx = 1.0/n;
    const double_t x = dx - 1.0/(n * 2);

    // expected: 1 1 1 1 | -1 -1 -1 -1

    auto* seq = wal_seq(functionNumber, n, x, dx);

    EXPECT_TRUE(seq != nullptr);

    for(int32_t i = 0; i < n; i++)
        EXPECT_EQ(((i/4 == 0) ? 1 : -1), *(seq + i));

    free(seq);
}

TEST(WALSH, SEQ15_16)
{
    const int32_t n = 16;
    const int32_t functionNumber = 15;

    const double_t dx = 1.0/n;
    const double_t x = dx - 1.0/(n * 2);

    // expected: 1 -1 1 -1 1 -1 ...

    auto* seq = wal_seq(functionNumber, n, x, dx);

    EXPECT_TRUE(seq != nullptr);

    for(int32_t i = 0; i < n; i++)
        EXPECT_EQ(((i%2 == 0) ? 1 : -1), *(seq + i));

    free(seq);
}

TEST(WALSH, LOG2_SEQ)
{
    const int32_t n = 16;
    const int32_t functionNumber = 15;

    // expected: 1 -1 1 -1 1 -1 ...

    auto* seq = wal_seq_log2(functionNumber, n);

    EXPECT_TRUE(seq != nullptr);

    for(int32_t i = 0; i < n; i++)
        EXPECT_EQ(((i%2 == 0) ? 1 : -1), *(seq + i));

    free(seq);
}

double_t calc_x(const double_t& t, const int32_t& T) {
    double_t dt = 1.0/(2*T);

    return (t/T - dt);
}

void print(const int32_t& number, const int32_t& expected, const int32_t& res) {
    printf("[%d]: \t%d \t-> \t%d\n", number, expected, res);
}