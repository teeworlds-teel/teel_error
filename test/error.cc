#include <gtest/gtest.h>
#include <teel_error/error.h>

TEST(Error, Basic) {
	EXPECT_STREQ(teel_get_error(), "");
	teel_set_error("expected y at offset %d", 10);
	EXPECT_STREQ(teel_get_error(), "expected y at offset 10");
	teel_clear_error();
	EXPECT_STREQ(teel_get_error(), "");
}
