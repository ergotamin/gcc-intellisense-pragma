// !c++
// #pragma once
//-------------------------------------
// (c) 2018 MIT License Marcel Bobolz
// <mailto:ergotamin.source@gmail.com>
//-------------------------------------
#include <vector>
//
extern const char *__progname;
//
extern "C"
// **`NOTE: `**
// ```
// Instructs sys_execve(...)
// ```
// ` ` [**` __ASSEMBLER__ `**](@deps)
int __asm_execve(const char *, char *const *, char *const *);
//
// **`NOTE: `**
// ```
//  Invokes 'gcc' with 'vscode'-plugin and arguments
// ```
// ` ` [**` __asm_execve `**](@deps) "-fplugin-vscode-...=..."
struct gcc_func {
    //
    std::vector<const char *>	__argv_;
    const char					**__envp_;
    const char					*__plugin_arg = "-fplugin-arg-vscode-";
    //
    virtual ~gcc_func(void) final
    {
        __builtin_printf("[%s] An error occured.\n", __progname);
    }
    //
    explicit gcc_func(char **argv, const char **envp)
    {
        this->__init__();
        char *key_value = NULL;
        while (*argv) {
            if (0 == __builtin_strncmp(*argv, this->__plugin_arg, 20)) {
                key_value = (char *)__builtin_calloc((4 >> 0 << 4), (4 >> 2));
                __builtin_strcat(key_value, this->__plugin_arg);
                __builtin_strcat(key_value, &*argv[16]);
                ++argv;
                this->__argv_.emplace_back(key_value);
                __builtin_free((void *)key_value);
                continue;
            }
            this->__argv_.emplace_back(*argv);
            ++argv;
        }
        this->__envp_ = envp;
    }
    //
    void __init__(void)
    {
        this->__argv_.emplace_back("/usr/bin/gcc");
        this->__argv_.emplace_back("-S");
        this->__argv_.emplace_back("-std=gnu++2a");
        this->__argv_.emplace_back("-m64");
        this->__argv_.emplace_back("-O0");
        this->__argv_.emplace_back("-DDEBUG");
        this->__argv_.emplace_back("-D_DEBUG");
        this->__argv_.emplace_back("-D_GNU_SOURCE");
        this->__argv_.emplace_back("-fplugin=vscode");
    }
    //
    int operator()(void)
    {
        return __asm_execve(this->__argv_.data()[0],
                            (char *const *)this->__argv_.data(),
                            (char *const *)this->__envp_);
    }
    //
};
//
// **`NOTE: `**
// ```
// entry point...
// ```
// ` ` [**`  `**](@deps)
int main(int argc, char **argv, const char **envp)
{
    --argc;
    if (!argc) {
        __builtin_exit(4 >> 0 << 4);
    } else {
        ++argv;
        gcc_func gcc(argv, envp);
        return gcc();
    }
}
