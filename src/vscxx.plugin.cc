#/* !intellisense_pragma.cc */
#// (c) 2019 <http://www.gnu.org/licenses/>
#// Marcel Bobolz
#// <ergotamin.source@gmail.com>
#include <vscxx.plugin.hh>
namespace vscode {
    // Plugin version string and short description.
    static constexpr plugin_info about {
        .version = "0.1-alpha",
        .help = "A compiler preprocessor for Microsoft C/C++ Intellisense."
    };
    //===========================================
    static int init(plugin_args *pargs, gcc_version *version)
    {
        vscode::exit_code = 1;

        const char *plugin = pargs->base_name;

        asm_file_name = HOST_BIT_BUCKET;

        signal(SIGPIPE, vscode::handle_error);

        register_callback(plugin, PLUGIN_INFO, NULL, (void *)&vscode::about);

        register_callback(plugin, PLUGIN_PRAGMAS, &vscode::register_pragma, NULL);

        register_callback(plugin, PLUGIN_OVERRIDE_GATE, &vscode::gate_pass, NULL);

        vscode::exit_code = 0;

        return vscode::exit_code;
    }
    //===========================================
    static void handle_error(int err)
    {
        printf("An error(%i) occured... !\n", err);
        vscode::exit_code = 1;
        __builtin_exit(vscode::exit_code);
    }
    //===========================================
    static void register_pragma(void *event, void *data)
    {
        c_register_pragma(NULL, "vscode", &handle_pragma);
    }
    //===========================================
    static void handle_pragma(cpp_reader *reader)
    {
        __builtin_memset(&ast, 0, sizeof(tree));

        cpp_ttype atom = pragma_lex(&ast);

        if (atom = CPP_OPEN_BRACE) {
            cpp_warning(reader, 111, "#pragma intellisense toggle {");
            return;
        }
    }
    //===========================================
    static void gate_pass(void *, void *)
    {
        vscode::exit_code = 1;

        ((errorcount || sorrycount)
         ? (kill(getpid(), SIGPIPE))
         : (vscode::exit_code = 0));

        printf("passing: %s\n", main_input_filename);

        exit(vscode::exit_code);
    }
    //===========================================
}
int plugin_init(plugin_args *pargs, gcc_version *version)
{
    return vscode::init(pargs, version);
}
#// := eof
