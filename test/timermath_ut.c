
#include "timermath/timermath.h"
#include "describe/describe.h"


static void
compare_numbers(struct tm_math * tm, uint32_t smaller, uint32_t larger)
{
    // Equal value
    assert_ok(  !   tm_is_lt(tm,    smaller,    smaller));
    assert_ok(  !   tm_is_lt(tm,    larger,     larger));

    assert_ok(  !   tm_is_gt(tm,    smaller,    smaller));
    assert_ok(  !   tm_is_gt(tm,    larger,     larger));

    assert_ok(      tm_is_ge(tm,    smaller,    smaller));
    assert_ok(      tm_is_ge(tm,    larger,     larger));

    assert_ok(      tm_is_le(tm,    smaller,    smaller));
    assert_ok(      tm_is_le(tm,    larger,     larger));

    // Less than
    assert_ok(      tm_is_lt(tm,    smaller,    larger));
    assert_ok(  !   tm_is_lt(tm,    larger,     smaller));

    // Greater than
    assert_ok(      tm_is_gt(tm,    larger,     smaller));
    assert_ok(  !   tm_is_gt(tm,    smaller,    larger));
}


int main(int argc, char const *argv[])
{
    (void) argv;
    (void) argc;

    describe("Timer math with a maskable max value") {

        struct tm_math tm;
        tm_initialize(&tm, 255);

        it("can increment timer values") {
            assert_ok(10 == tm_offset(&tm, 0, 10));
            assert_ok(0 == tm_offset(&tm, 255, 1));
        }

        it("can decrement timer values") {
            assert_ok(0 == tm_offset(&tm, 10, -10));
            assert_ok(255 == tm_offset(&tm, 0, -1));
        }

        it("can roll over timer values while incrementing") {
            uint32_t t = 128;

            uint32_t i;
            for (i = 0; i < 255; ++i) {
                t = tm_offset(&tm, t, 1);
            }

            assert_ok(127 == t);
        }

        it("can roll over timer values while decrementing") {
            uint32_t t = 128;

            uint32_t i;
            for (i = 0; i < 255; ++i) {
                t = tm_offset(&tm, t, -1);
            }

            assert_ok(129 == t);
        }

        it("can get the positive difference between two timer values") {
            assert_equal(0,     tm_get_diff(&tm, 0,     0));
            assert_equal(10,    tm_get_diff(&tm, 10,    0));
            assert_equal(1,     tm_get_diff(&tm, 0,     255));
            assert_equal(3,     tm_get_diff(&tm, 1,     254));
            assert_equal(127,   tm_get_diff(&tm, 128,   1));
        }

        it("can get the negative difference between two timer values") {
            assert_equal(-1,    tm_get_diff(&tm, 0,     1));
            assert_equal(-10,   tm_get_diff(&tm, 0,     10));
            assert_equal(-1,    tm_get_diff(&tm, 255,   0));
            assert_equal(-3,    tm_get_diff(&tm, 254,   1));
            assert_equal(-127,  tm_get_diff(&tm, 1,     128));
        }

        it("can compare numbers close together") {
            uint32_t smaller = 0;
            uint32_t larger = 1;
            compare_numbers(&tm, smaller, larger);
        }

        it("can compare numbers far apart") {
            uint32_t smaller = 0;
            uint32_t larger = 127;
            compare_numbers(&tm, smaller, larger);
        }

        it("can compare numbers around the rollover") {
            uint32_t smaller = 129;
            uint32_t larger = 0;
            compare_numbers(&tm, smaller, larger);
        }
    }

    describe("Timer math with a non-maskable max value") {

        struct tm_math tm;
        tm_initialize(&tm, 256);

        it("can increment timer values") {
            assert_ok(10 == tm_offset(&tm, 0, 10));
            assert_ok(0 == tm_offset(&tm, 256, 1));
        }

        it("can decrement timer values") {
            assert_ok(0 == tm_offset(&tm, 10, -10));
            assert_ok(256 == tm_offset(&tm, 0, -1));
        }

        it("can roll over timer values while incrementing") {
            uint32_t t = 128;

            uint32_t i;
            for (i = 0; i < 256; ++i) {
                t = tm_offset(&tm, t, 1);
            }

            assert_ok(127 == t);
        }

        it("can roll over timer values while decrementing") {
            uint32_t t = 128;

            uint32_t i;
            for (i = 0; i < 256; ++i) {
                t = tm_offset(&tm, t, -1);
            }

            assert_ok(129 == t);
        }

        it("can get the positive difference between two timer values") {
            assert_equal(0,     tm_get_diff(&tm, 0,     0));
            assert_equal(10,    tm_get_diff(&tm, 10,    0));
            assert_equal(1,     tm_get_diff(&tm, 0,     256));
            assert_equal(3,     tm_get_diff(&tm, 1,     255));
            assert_equal(127,   tm_get_diff(&tm, 128,   1));
        }

        it("can get the negative difference between two timer values") {
            assert_equal(-1,    tm_get_diff(&tm, 0,     1));
            assert_equal(-10,   tm_get_diff(&tm, 0,     10));
            assert_equal(-1,    tm_get_diff(&tm, 256,   0));
            assert_equal(-4,    tm_get_diff(&tm, 254,   1));
            assert_equal(-127,  tm_get_diff(&tm, 1,     128));
        }

        it("can compare numbers close together") {
            uint32_t smaller = 0;
            uint32_t larger = 1;
            compare_numbers(&tm, smaller, larger);
        }

        it("can compare numbers far apart") {
            uint32_t smaller = 0;
            uint32_t larger = 128;
            compare_numbers(&tm, smaller, larger);
        }

        it("can compare numbers around the rollover") {
            uint32_t smaller = 255;
            uint32_t larger = 0;
            compare_numbers(&tm, smaller, larger);
        }
    }

    describe("Timer math with a 32 bit max value") {
        struct tm_math tm;
        tm_initialize(&tm, 4294967295);

        it("can increment timer values") {
            assert_ok(10 == tm_offset(&tm, 0, 10));
            assert_ok(0 == tm_offset(&tm, 4294967295, 1));
        }

        it("can decrement timer values") {
            assert_ok(0 == tm_offset(&tm, 10, -10));
            assert_ok(4294967295 == tm_offset(&tm, 0, -1));
        }

        it("can compare numbers around the rollover") {
            uint32_t smaller = 4294967295;
            uint32_t larger = 1;
            compare_numbers(&tm, smaller, larger);
        }

        it("can compare numbers far apart") {
            uint32_t smaller = 0;
            uint32_t larger = 2147483647;
            compare_numbers(&tm, smaller, larger);
        }
    }

    return assert_failures();
}

