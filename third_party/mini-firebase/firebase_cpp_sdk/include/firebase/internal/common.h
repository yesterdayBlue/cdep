// Copyright 2016 Google Inc. All Rights Reserved.

#ifndef FIREBASE_APP_CLIENT_CPP_SRC_INCLUDE_FIREBASE_INTERNAL_COMMON_H_
#define FIREBASE_APP_CLIENT_CPP_SRC_INCLUDE_FIREBASE_INTERNAL_COMMON_H_

// This file contains definitions that configure the SDK.

// Include a STL header file, othewise _STLPORT_VERSION won't be set.
#include <utility>

// Move operators use rvalue references, which are a C++11 extension.
// Also, stlport doesn't implement std::move().
#if __cplusplus >= 201103L && !defined(_STLPORT_VERSION)
#define FIREBASE_USE_MOVE_OPERATORS
#endif  // __cplusplus >= 201103L && !defined(_STLPORT_VERSION)

#if !defined(DOXYGEN) && !defined(SWIG)
#if !defined(_WIN32) && !defined(__CYGWIN__)
// Prevent GCC & Clang from stripping a symbol.
#define FIREBASE_APP_KEEP_SYMBOL __attribute__((used))
#else
// MSVC needs to reference a symbol directly in the application for it to be
// kept in the final executable.  In this case, the end user's application
// must include the appropriate Firebase header (e.g firebase/analytics.h) to
// initialize the module.
#define FIREBASE_APP_KEEP_SYMBOL
#endif  // !defined(_WIN32) && !defined(__CYGWIN__)

// Module initializer's name.
//
// This can be used to explicitly include a module initializer in an application
// to prevent the object from being stripped by the linker.  The symbol is
// located in the "firebase" namespace so can be referenced using:
//
// ::firebase::FIREBASE_APP_REGISTER_CALLBACKS_REFERENCE_NAME(name)
//
// Where "name" is the module name, for example "analytics".
#define FIREBASE_APP_REGISTER_CALLBACKS_INITIALIZER_NAME(module_name) \
  g_##module_name##_initializer

// Declare a module initializer variable as a global.
#define FIREBASE_APP_REGISTER_CALLBACKS_INITIALIZER_VARIABLE(module_name)     \
  namespace firebase {                                                        \
  extern void* FIREBASE_APP_REGISTER_CALLBACKS_INITIALIZER_NAME(module_name); \
  } /* namespace firebase */

// Generates code which references a module initializer.
// For example, FIREBASE_APP_REGISTER_REFERENCE(analytics) will register the
// module initializer for the analytics module.
#define FIREBASE_APP_REGISTER_CALLBACKS_REFERENCE(module_name)        \
  FIREBASE_APP_REGISTER_CALLBACKS_INITIALIZER_VARIABLE(module_name);  \
  namespace firebase {                                                \
  static void* module_name##_ref FIREBASE_APP_KEEP_SYMBOL =           \
      &FIREBASE_APP_REGISTER_CALLBACKS_INITIALIZER_NAME(module_name); \
  }     /* namespace firebase */
#endif  //  !defined(DOXYGEN) && !defined(SWIG)

#endif  // FIREBASE_APP_CLIENT_CPP_SRC_INCLUDE_FIREBASE_INTERNAL_COMMON_H_
