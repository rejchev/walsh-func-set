#include <gtest/gtest.h>

#include "../walshf32.h"

int print(const int32_t&, const int32_t&, const int32_t&);
double getX(const uint32_t& i, const double& T);

using namespace walshf;

// wal(0, t/T) = pal(0, t/T) = 1
TEST(WALSH, W0)
{
    const double x = 0/1.0;
    const int32_t function = 0;

    const int32_t expected = 1;

    EXPECT_EQ(expected, wal(function, x));
}

// wal(1, t/T) = pal(1, t/T) = radf(0, t/T)
TEST(WALSH, W1)
{
    const int32_t T = 2;
    const int32_t function = 1;

    const std::vector<int32_t> expected {
        1, -1
    };

    for(int i = 1; i <= T; i++)
        EXPECT_EQ(expected[i - 1], print(
                i,
                expected[i-1],
                wal(function, getX(i - 1, T), radf::frad))
        );
}

// wal(2, t/T) = pal(3, t/T) = radf(1,t/T) * radf(0, t/T)
TEST(WALSH, W2)
{
    const int32_t T = 4;
    const int32_t function = 2;

    const std::vector<int32_t> expected {
            1, -1, -1, 1
    };

    for(int i = 1; i <= T; i++)
        EXPECT_EQ(expected[i - 1], print(
                i,
                expected[i-1],
                wal(function, getX(i - 1, T)))
        );
}

// wal(3, t/T) = pal(2, t/T) = radf(1,t/T) [t/T = 1/4]
TEST(WALSH, W3)
{
    const int32_t T = 8;
    const int32_t function = 3;

    std::vector<int32_t> expected {
            1, 1, -1, -1, 1, 1, -1, -1
    };

    for(int i = 1; i <= T; i++)
        EXPECT_EQ(expected[i - 1], print(
                i,
                expected[i-1],
                wal(function, getX(i - 1, T)))
        );
}

// wal(4, t/T) = pal(6, t/T) = radf(2, t/T) * radf(1, t/T)
TEST(WALSH, W4)
{
    const int32_t T = 8;
    const int32_t function = 4;

    const std::vector<int32_t> expected {
            1, -1, -1, 1, 1, -1, -1, 1
    };

    for(int i = 1; i <= T; i++)
        EXPECT_EQ(expected[i - 1], print(
                i,
                expected[i-1],
                wal(function, getX(i - 1, T)))
        );
}

// wal(5, t/T) = pal(7, t/T) = radf(2, t/T) * radf(1, t/T) * radf(0, t/T)
TEST(WALSH, W5)
{
    const int32_t T = 8;
    const int32_t function = 5;

    std::vector<int32_t> expected {
            1, -1, -1, 1, -1, 1, 1, -1
    };

    for(int i = 1; i <= T; i++)
        EXPECT_EQ(expected[i - 1], print(
                i,
                expected[i-1],
                wal(function, getX(i - 1, T)))
        );
}

// wal(6, t/T) = pal(5, t/T) = radf(2, t/T) * radf(0, t/T)
TEST(WALSH, W6)
{
    const int32_t T = 8;
    const int32_t function = 6;

    std::vector<int32_t> expected {
            1, -1, 1, -1, -1, 1, -1, 1
    };

    for(int i = 1; i <= T; i++)
        EXPECT_EQ(expected[i - 1], print(
                i,
                expected[i-1],
                wal(function, getX(i - 1, T)))
        );
}

// wal(7, t/T) = pal(4, t/T) = radf(2, t/T) [t/T = 1/8]
TEST(WALSH, W7)
{
    const int32_t T = 8;
    const int32_t function = 7;

    std::vector<int32_t> expected {
            1, -1, 1, -1, 1, -1, 1, -1
    };

    for(int i = 1; i <= T; i++)
        EXPECT_EQ(expected[i - 1], print(
                i,
                expected[i-1],
                wal(function, getX(i - 1, T)))
        );
}

TEST(WALSH, SEQ1_8)
{
    const int32_t n = 8;
    const int32_t functionNumber = 1;

    const double_t dx = 1.0/n;
    const double_t x = dx - 1.0/(n * 2);

    // expected: 1 1 1 1 | -1 -1 -1 -1

    auto* seq = walseq(functionNumber, n, x, dx, wal);

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

    auto* seq = walseq(functionNumber, n, x, dx, wal);

    EXPECT_TRUE(seq != nullptr);

    for(int32_t i = 0; i < n; i++)
        EXPECT_EQ(((i%2 == 0) ? 1 : -1), *(seq + i));

    free(seq);
}

TEST(WALSH, BSEQ31_32)
{
    const int32_t n = 32;
    const int32_t functionNumber = 31;

    const double_t dx = 1.0/n;
    const double_t x = dx - 1.0/(n * 2);

    // expected: 1 -1 1 -1 1 -1 ...

    auto* seq = walbseq(functionNumber, n, x, dx, wal);

    EXPECT_TRUE(seq != nullptr);

    for(int32_t i = 0; i < n; i++)
        EXPECT_EQ(((i%2 == 0) ? 0 : 1), *(seq + i));

    free(seq);
}

TEST(WALSH, LOG2_SEQ)
{
    const int32_t n = 64;
    const int32_t functionNumber = 63;

    // expected: 1 -1 1 -1 1 -1 ...

    auto* seq = walseq_log2(functionNumber, n, wal);

    EXPECT_TRUE(seq != nullptr);

    for(int32_t i = 0; i < n; i++)
        EXPECT_EQ(((i%2 == 0) ? 1 : -1), *(seq + i));

    free(seq);
}

TEST(WALSH, NORMALIZED_BWAL_16)
{
    const int32_t n = 16;

    uint32_t* seq;

    std::cout << std::endl;

    for(int32_t i = 0; i < n; i++) {

        seq = walbseq_log2(i, n, wal);

        EXPECT_TRUE(seq != nullptr);

        std::cout << "w" << i << ":";

        if(i < 10)
            std::cout << " ";

        std::cout << " ";

        for(int j = 0; j < n; j++)
            std::cout << *(seq + j) << " ";

        std::cout << std::endl;

        free(seq);
    }

    std::cout << std::endl;
}

double getX(const uint32_t& i, const double& T) {
    const double dx = 1.0/T;

    return (dx - 0.5 * dx) + i * dx;
}

int print(const int32_t& number, const int32_t& expected, const int32_t& res) {
    printf("[%d]: \t%d \t-> \t%d\n", number, expected, res);

    return res;
}