CXX := g++
DRIVER_SOURCES := src/__asm_execve.S src/gcc-code.cxx
PLUGIN_SOURCES := src/plugin.cxx
GCC_PLUGINS_DIR := $(shell $(CXX) -print-file-name=plugin)
CXXFLAGS_DRIVER := -m64 -std=gnu++2a -I./src -O2 -Ofast -pedantic -Wall -Wl,-O1
CXXFLAGS_PLUGIN := -I$(GCC_PLUGINS_DIR)/include -fPIC -fno-rtti -O2



gcc-code: $(DRIVER_SOURCES)
	$(CXX) $(CXXFLAGS_DRIVER) $^ -o $@


vscode.so: $(PLUGIN_SOURCES)
	$(CXX) -shared $(CXXFLAGS_PLUGIN) $^ -o $@


install-bin: gcc-code
	@install -m0755 gcc-code /usr/bin/gcc-code


install-lib: vscode.so
	@install -m0755 vscode.so $(GCC_PLUGINS_DIR)/vscode.so


clean:
	@rm -f vscode.so gcc-code


install: install-bin install-lib


all: gcc-code vscode.so install-bin install-lib clean


default: all


.PHONY: all install clean