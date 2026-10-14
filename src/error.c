#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <teel_error/error.h>

typedef struct {
	char message[2048];
} TeelErrorContext;

#if defined(_MSC_VER)
#define THREAD_LOCAL __declspec(thread)
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#define THREAD_LOCAL _Thread_local
#else
#define THREAD_LOCAL __thread
#endif
static THREAD_LOCAL TeelErrorContext err_last = {0};
#undef THREAD_LOCAL

void teel_set_error_prefix(const char *fmt, ...) {
	if(!fmt) {
		return;
	}
	va_list ap;
	va_start(ap, fmt);
	char buf[2048];
	int n = vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);
	if(n > 0 && (size_t)n < sizeof(buf)) {
		snprintf(buf + n, sizeof(buf) - n, ": %s", err_last.message);
	}
	memcpy(err_last.message, buf, sizeof(err_last.message));
}

void teel_set_error(const char *fmt, ...) {
	if(!fmt) {
		err_last.message[0] = '\0';
		return;
	}
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(err_last.message, sizeof(err_last.message), fmt, ap);
	va_end(ap);
}

const char *teel_get_error() {
	return err_last.message;
}

void teel_clear_error() {
	memset(&err_last, 0, sizeof(err_last));
}

const char *teel_error_code_to_str(TeelError err) {
	switch(err) {
	case TEEL_ERR_NONE: return "TEEL_ERR_NONE";
	case TEEL_ERR_ERROR: return "TEEL_ERR_ERROR";
	case TEEL_ERR_BAD_INPUT: return "TEEL_ERR_BAD_INPUT";
	case TEEL_ERR_PARSE: return "TEEL_ERR_PARSE";
	case TEEL_ERR_NOT_FOUND: return "TEEL_ERR_NOT_FOUND";
	case TEEL_ERR_IO: return "TEEL_ERR_IO";
	case TEEL_ERR_OUT_OF_MEMORY: return "TEEL_ERR_OUT_OF_MEMORY";
	case TEEL_ERR_NOT_IMPLEMENTED: return "TEEL_ERR_NOT_IMPLEMENTED";
	case TEEL_ERR_OUTPUT_BUFFER_FULL: return "TEEL_ERR_OUTPUT_BUFFER_FULL";
	case TEEL_ERR_END_OF_INPUT_BUFFER: return "TEEL_ERR_END_OF_INPUT_BUFFER";
	case TEEL_ERR_INTERNAL_BUFFER_FULL: return "TEEL_ERR_INTERNAL_BUFFER_FULL";
	case TEEL_ERR_INVALID_BOOL: return "TEEL_ERR_INVALID_BOOL";
	case TEEL_ERR_HUFFMAN_NODE_NULL: return "TEEL_ERR_HUFFMAN_NODE_NULL";
	case TEEL_ERR_HUFFMAN_NO_MORE_BITS: return "TEEL_ERR_HUFFMAN_NO_MORE_BITS";
	case TEEL_ERR_STR_UNEXPECTED_EOF: return "TEEL_ERR_STR_UNEXPECTED_EOF";
	case TEEL_ERR_STR_QUOTE: return "TEEL_ERR_STR_QUOTE";
	case TEEL_ERR_STR_BRACE: return "TEEL_ERR_STR_BRACE";
	case TEEL_ERR_STR_UTF8: return "TEEL_ERR_STR_UTF8";
	case TEEL_ERR_UNKNOWN_ID: return "TEEL_ERR_UNKNOWN_ID";
	case TEEL_ERR_INVALID_KIND: return "TEEL_ERR_INVALID_KIND";
	case TEEL_ERR_ACK_OUT_OF_BOUNDS: return "TEEL_ERR_ACK_OUT_OF_BOUNDS";
	case TEEL_ERR_CONSOLE_WRONG_NUMBER_OF_ARGUMENTS: return "TEEL_ERR_CONSOLE_WRONG_NUMBER_OF_ARGUMENTS";
	case TEEL_ERR_CONSOLE_INVALID_INTEGER: return "TEEL_ERR_CONSOLE_INVALID_INTEGER";
	case TEEL_ERR_CONSOLE_INVALID_VICTIM: return "TEEL_ERR_CONSOLE_INVALID_VICTIM";
	case TEEL_ERR_CONSOLE_INVALID_COLOR: return "TEEL_ERR_CONSOLE_INVALID_COLOR";
	case TEEL_ERR_CONSOLE_NO_SUCH_COMMAND: return "TEEL_ERR_CONSOLE_NO_SUCH_COMMAND";
	case TEEL_ERR_CONSOLE_INVALID_PARAMS: return "TEEL_ERR_CONSOLE_INVALID_PARAMS";
	case TEEL_ERR_CONSOLE_INVALID_PARAM_TYPE: return "TEEL_ERR_CONSOLE_INVALID_PARAM_TYPE";
	case TEEL_ERR_CONSOLE_INVALID_OPTIONAL_PARAM: return "TEEL_ERR_CONSOLE_INVALID_OPTIONAL_PARAM";
	}
	return "TEEL_ERR_UNKNOWN";
}
