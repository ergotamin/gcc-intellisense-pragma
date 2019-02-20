CXX := g++
DRIVER_SOURCES := src/vscxx.driver.cxx src/vscxx.driver.cc
PLUGIN_SOURCES := src/vscxx.lib.cc
GCC_PLUGINS_DIR := $(shell $(CXX) -print-file-name=plugin)
CXXFLAGS_DRIVER := -m64 -std=gnu++2a -I./src -O2 -Ofast -pedantic -Wall -Wl,-O1
CXXFLAGS_PLUGIN := -I./src -I$(GCC_PLUGINS_DIR)/include -fPIC -fno-rtti -O2



vscxx: $(DRIVER_SOURCES)
	$(CXX) $(CXXFLAGS_DRIVER) $^ -o $@


libvscxx.so: $(PLUGIN_SOURCES)
	$(CXX) -shared $(CXXFLAGS_PLUGIN) $^ -o $@


install-bin: vscxx
	@install -m0755 vscxx /usr/bin/vscxx


install-lib: libvscxx.so
	@install -m0755 libvscxx.so $(GCC_PLUGINS_DIR)


install: install-bin install-lib


all: vscxx libvscxx.so


default: all


.PHONY: all install