#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	/// This is not an error the result is okay
	/// this represents success
	TEEL_ERR_NONE,

	/// A generic error meaning something went wrong
	/// Check teel_get_error() for more details in that case.
	TEEL_ERR_ERROR,

	/// A generic error meaning some kind of user input was bad.
	/// This is most likely an invalid argument passed by the user
	/// of the library to a function of the library.
	TEEL_ERR_BAD_INPUT,

	/// A generic error meaning some kind of expected data format
	/// failed to parse. This could be a network message that
	/// does not follow the teeworlds protocol or a console command
	/// string. Depending on which function you called.
	TEEL_ERR_PARSE,

	/// A generic error that means something was not found.
	/// What was not found depends on what we were looking for.
	/// This could be a file on disk or an element in a data structure.
	TEEL_ERR_NOT_FOUND,

	/// A generic error if something with IO (input output) went wrong.
	/// This will be a failed write or read to the file system or network.
	TEEL_ERR_IO,

	/// The library tried to allocate more memory but the host system
	/// failed to do so. In that case you need to download more RAM.
	TEEL_ERR_OUT_OF_MEMORY,

	/// Generic placeholder error for a feature which should be implemented
	/// but is not implemeneted yet.
	TEEL_ERR_NOT_IMPLEMENTED,

	/// A generic error that will be hit if the user passed a buffer to
	/// a teel library to write a result to. And the function had more
	/// data to write than the size of the given output buffer.
	TEEL_ERR_OUTPUT_BUFFER_FULL,

	/// A generic error that will be hit when we are parsing/consuming some kind of
	/// user provided data buffer. And we hit an unexpected end of the buffer.
	/// Or the user tried to consume the next element but nothing was left
	/// in the given buffer.
	TEEL_ERR_END_OF_INPUT_BUFFER,

	// A ganeric error that will be hit when a internal buffer defined by the teel
	// library it self is full. This happens when the teel library has a internal maximum capacity
	// and the user called it in a way exceeding this capacity.
	TEEL_ERR_INTERNAL_BUFFER_FULL,

	// A protocol packer/unpacker specific error. There is a soft concept of booleans
	// in the teeworlds protocol but they are technically sent as integers.
	// This error is thrown when we expect a boolean but got something other than
	// 1 or 0 which should be the only two values that represent true or false.
	TEEL_ERR_INVALID_BOOL,

	/// This is a huffman compression specific internal error.
	/// Which should never be hit.
	TEEL_ERR_HUFFMAN_NODE_NULL,

	/// This is a huffman compression specific internal error.
	/// Which should never be hit.
	TEEL_ERR_HUFFMAN_NO_MORE_BITS,

	/// The unpacker tried to read a string but the data ended
	/// before the null terminator.
	TEEL_ERR_STR_UNEXPECTED_EOF,

	/// There is a quoting error. This could be a missing
	/// opening or closing quote. Or too many quotes.
	TEEL_ERR_STR_QUOTE,

	/// Failed to parse a string because there are unexpected or missing braces.
	TEEL_ERR_STR_BRACE,

	/// A string contains invalid utf-8.
	TEEL_ERR_STR_UTF8,

	/// The identifier number of a snap item, network message
	/// or similar is a unexpected value which does not match
	/// any known id.
	TEEL_ERR_UNKNOWN_ID,

	/// A library internal union/struct identifier is out of bounds.
	/// This is a value that is not sent over the network.
	/// But describes which kind of field in a union should be accessed.
	/// The variable holding the invalid value is usually called "kind"
	/// and the expected values are defined in an enum.
	TEEL_ERR_INVALID_KIND,

	/// The network protocol acknowledge number is out of bounds
	TEEL_ERR_ACK_OUT_OF_BOUNDS,

	/// A console specific error that means a command was called with too
	/// few or too many arguments based on the expected parameters.
	TEEL_ERR_CONSOLE_WRONG_NUMBER_OF_ARGUMENTS,

	/// Console specific error.
	/// A given integer argument is not valid.
	TEEL_ERR_CONSOLE_INVALID_INTEGER,

	/// Console specific error.
	/// A given victim argument is not valid.
	TEEL_ERR_CONSOLE_INVALID_VICTIM,

	/// Console specific error.
	/// A given color argument is not valid.
	TEEL_ERR_CONSOLE_INVALID_COLOR,

	/// A console command was not found.
	TEEL_ERR_CONSOLE_NO_SUCH_COMMAND,

	/// A console speific error. That says the given parameters
	/// contain a syntax error.
	TEEL_ERR_CONSOLE_INVALID_PARAMS,

	/// Unknown console parameter type
	TEEL_ERR_CONSOLE_INVALID_PARAM_TYPE,

	/// Something is wrong with a optional parameter
	TEEL_ERR_CONSOLE_INVALID_OPTIONAL_PARAM,
} TeelError;

// Prepends the given string in front of the current error
// use this to enrich a bubbled up error with context from the
// callsite.
void teel_set_error_prefix(const char *fmt, ...);
void teel_set_error(const char *fmt, ...);
const char *teel_get_error();
void teel_clear_error();
const char *teel_error_code_to_str(TeelError err);

#ifdef __cplusplus
}
#endif
