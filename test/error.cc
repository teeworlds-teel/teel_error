#include <gtest/gtest.h>
#include <teel_error/error.h>

TEST(Error, Basic) {
	EXPECT_STREQ(teel_get_error(), "");
	teel_set_error("expected y at offset %d", 10);
	EXPECT_STREQ(teel_get_error(), "expected y at offset 10");
	teel_clear_error();
	EXPECT_STREQ(teel_get_error(), "");
}

TEST(Error, Prefix) {
	EXPECT_STREQ(teel_get_error(), "");
	teel_set_error("parser failed on 0xff");
	EXPECT_STREQ(teel_get_error(), "parser failed on 0xff");
	teel_set_error_prefix("failed to decode packet");
	EXPECT_STREQ(teel_get_error(), "failed to decode packet: parser failed on 0xff");
}
