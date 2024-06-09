#pragma once


#include <string>


#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

// NOTE: this error message format will need to be updated with brackets if/when the error format changes
#define BUILD_GUARD_ERROR_MESSAGE(throw_from, guard_statement) \
   throw_from ": error: guard \"" guard_statement "\" not met"

#define EXPECT_THROW_GUARD_ERROR(code, throw_from, guard_statement) \
   EXPECT_THROW_WITH_MESSAGE(code, std::runtime_error, BUILD_GUARD_ERROR_MESSAGE(throw_from, guard_statement))

#define ASSERT_THROW_GUARD_ERROR(code, throw_from, guard_statement) \
   ASSERT_THROW_WITH_MESSAGE(code, std::runtime_error, BUILD_GUARD_ERROR_MESSAGE(throw_from, guard_statement))


