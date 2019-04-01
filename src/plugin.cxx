//-----------------------------
//       Marcel Bobolz
//  ergotamin.source@gmail.com
//-----------------------------

#include <set>
#include <csignal>
#include <gcc-plugin.h>
#include <function.h>
#include <tree.h>
#include <tree-pass.h>
#include <rtl.h>
#include <genrtl.h>
#include <intl.h>
#include <tm.h>
#include <cp/cp-tree.h>
#include <cgraph.h>
#include <stringpool.h>
#include <c-family/c-pragma.h>
#include <c-family/c-common.h>
#include <diagnostic.h>
#include <cpplib.h>

//   ===============(LICENSE)=================

int plugin_is_GPL_compatible;
unsigned long __attribute__((__vector_size__(16))) vmagic = { 0x49540061302e3176UL, 0UL };

namespace vscode {
    //
    // **`NOTE: `**
    // ```
    // Holds information about the plugin
    // ```
    // ` ` [**`version, help`**](@member) ` `
    static constexpr struct plugin_info about {
        .version = (const char *)&vmagic,
        .help = "A compiler preprocessor for Microsoft C/C++ Intellisense."
    };

    struct decl_comparator {
        bool
        operator()(tree x, tree y) const
        {
            location_t xl(DECL_SOURCE_LOCATION(x));
            location_t yl(DECL_SOURCE_LOCATION(y));

            return xl < yl;
        }
    };
    typedef std::multiset<tree, decl_comparator> decl_set;

//   ===============(DECLARATIONS)=================

    static int init(plugin_name_args *, plugin_gcc_version *);
    static void handle_error(int);
    static void register_pragma(void *, void *);
    static void handle_pragma(cpp_reader *);
    static void gate_pass(void *, void *);
    static void tree_grab(tree, decl_set&);
    static void tree_walk(tree);
    static void print_decl(tree);

//   ===============(DEFINITIONS)=================

    //
    // **`NOTE: `**
    // ```
    // Handles the plugin-initialization
    // ```
    // ` ` [**`  `**](@deps)
    static int init(plugin_name_args *plugin, plugin_gcc_version *version)
    {
        asm_file_name = HOST_BIT_BUCKET;

        signal(SIGUSR1, vscode::handle_error);

        register_callback(plugin->base_name, PLUGIN_INFO, NULL, (void *)&vscode::about);
        register_callback(plugin->base_name, PLUGIN_OVERRIDE_GATE, &vscode::gate_pass, NULL);

        return 0;
    }
    //
    // **`NOTE: `**
    // ```
    // A signal handler for -SIGUSR1-
    // ```
    // ` ` [**`  `**](@deps)
    static void handle_error(int err)
    {
        __builtin_printf("An error(%i) occured... !\n", err);
        __builtin_exit(1);
    }
    //
    // **`NOTE: `**
    // ```
    // Overrides the default gate-function
    // ```
    // ` ` [**`  `**](@deps)
    static void gate_pass(void *, void *)
    {
        ((errorcount || sorrycount)
         ? (kill(getpid(), SIGUSR1))
         : (0));
  //    tree_walk(global_namespace);
        __builtin_exit(0);
    }
    //
    // **`NOTE: `**
    // ```
    // Ordered AST-collector
    // ```
    // ` ` [**`  `**](@deps)
    static void tree_grab(tree ns, decl_set& dset)
    {
        tree decl;
        cp_binding_level *level(NAMESPACE_LEVEL(ns));

        for (decl = level->names;
             decl != 0;
             decl = TREE_CHAIN(decl)) {
            if (DECL_IS_BUILTIN(decl))
                continue;

            dset.insert(decl);
        }
    }
    //
    // **`NOTE: `**
    // ```
    // Ordered AST-collector
    // ```
    // ` ` [**`  `**](@deps)
    static void tree_walk(tree ns)
    {
        decl_set dset;

        tree_grab(ns, dset);

        for (decl_set::iterator i(dset.begin()),
             e(dset.end()); i != e; ++i)
            print_decl(*i);
    }
    //
    // **`NOTE: `**
    // ```
    // Print AST-Declarations
    // ```
    // ` ` [**`  `**](@deps)
    static void print_decl(tree decl)
    {
        tree_code tc(TREE_CODE(decl));
        tree id(DECL_NAME(decl));
        const char *name(id
                         ? IDENTIFIER_POINTER(id)
                         : "<unnamed>");

        __builtin_printf(" (%s %s){ %s[:%i] }\n",
                         get_tree_code_name(tc),
                         name,
                         DECL_SOURCE_FILE(decl),
                         DECL_SOURCE_LINE(decl));
    }
}
//
// **`NOTE: `**
// ```
// Entry point for gcc-plugins
// ```
// ` ` [**`  `**](@deps)
int plugin_init(plugin_name_args *plugin_args, plugin_gcc_version *gcc_version)
{
    return vscode::init(plugin_args, gcc_version);
}
#//::eof
