// !c++
#pragma once
#// (c) 2018 MIT License
#// Marcel Bobolz
#// <ergotamin.source@gmail.com>
static_assert(__GNUC__, "Your compiler is not supporting GnuExtensions !");
#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <csignal>
#include <gcc-plugin.h>
#include <plugin.h>
#include <config.h>
#include <system.h>
#include <coretypes.h>
#include <function.h>
#include <tree.h>
#include <tree-pass.h>
#include <rtl.h>
#include <intl.h>
#include <tm.h>
#include <cp/cp-tree.h>
#include <c-family/c-pragma.h>
#include <c-family/c-common.h>
#include <diagnostic.h>
#include <cpplib.h>
// Asserts publishing under GPL license terms.
int plugin_is_GPL_compatible;
// Custom type from 'struct plugin_info'.
typedef struct plugin_info plugin_info;
// Custom type from 'struct plugin_name_args'.
typedef struct plugin_name_args plugin_args;
// Custom type from 'struct plugin_gcc_version'.
typedef struct plugin_gcc_version gcc_version;
// Initializes the plugin. (default)
int plugin_init(plugin_args *pargs, gcc_version *version);
// vscode++ plugin namespace
namespace vscode {
    // Static AST.
    static tree ast;
    // Static node-pointer.
    static void *node;
    // Return value.
    static int exit_code;
    // Handles the initialization and registration.
    // Instead of plugin_init().
    static int init(plugin_args *, gcc_version *);
    // A signal handler to handle errors.
    static void handle_error(int);
    // Callback for pragma registrations.
    static void register_pragma(void *, void *);
    // Handles '#pragma vscode function args...'.
    static void handle_pragma(cpp_reader *);
    // Overrides the default gate-function on passes.
    static void gate_pass(void *, void *);
}
//
