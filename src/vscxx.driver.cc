#/* !vscode++.cc */
#// (c) 2019 MIT License
#// Marcel Bobolz
#// <ergotamin.source@gmail.com>
#include <vscode++.hxx>
#include <iostream>
#include <unistd.h>
#include <array>
using namespace std;
//
void usage()
{
    cerr	<< "Usage: " endl
            << "      vscxx [options] <file>..." << endl
            << "Options:" << endl;
    options::print_usage(cerr);
}
//
struct gcc_func {
    std::vector<const char *> pargs;
    virtual ~gcc_func(void) final
    {
        cout << "An error occured." << endl;
    }
    explicit gcc_func(const char **args, unsigned long len)
    {
        int n = 0;

        for (; n < len; n++)
            this->pargs.push_back(args[n]);
    }
    const int operator()(int (*ExecV)(const char *arg0, char *const *cmdline))
    {
        return ExecV((const char *)this->pargs[0], (char *const *)this->pargs.data());
    }
};

//
int main(int argc, char **argv)
{
    using namespace cli;
    try
    {
        int end;
        options cargs(argc, argv, end, true);

        if (cargs.help()) {
            usage();
            return 0;
        }

        if (end == argc) {
            cerr << "error: missing input-file(s)" << endl;
            usage();
            return 1;
        }
        //
        unsigned long n = 0;
        //
        std::vector<const char *> args;
        //
        args.push_back(cargs.command().data());
        //
        for (; n < cargs.opt().size(); n++)
            args.push_back(cargs.opt()[n].data());
        //
        while (--argc)
            args.push_back(argv[argc]);
        //
        unsigned long le = 0;
        //
        n = 0;
        //
        gcc_func gcc(args.data(), args.size());
        gcc(execvp);
    }
    catch (const cli::exception& e)
    {
        cerr << e << endl;
        usage();
        return 1;
    }
}
