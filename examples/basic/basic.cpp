#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <teel_error/error.h>

namespace {
int my_func_that_throws(const char *text, TeelError *err) {
	if(strcmp(text, "foo") == 0) {
		return 1;
	}
	if(strcmp(text, "bar") == 0) {
		return 2;
	}

	teel_set_error("got text='%s' which is neither the expected foo nor bar", text);
	*err = TEEL_ERR_BAD_INPUT;
	return -1;
}
} // namespace

int main() {
	TeelError err = {};
	int out = my_func_that_throws("yellow", &err);
	if(err != TEEL_ERR_NONE) {
		printf("error: %s\n", teel_get_error());
		return 0;
	}

	printf("out: %d\n", out);
	return 0;
}
