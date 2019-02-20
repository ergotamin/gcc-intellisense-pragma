HOST_GCC = g++
TARGET_GCC = gcc
PLUGIN_SOURCE_FILES = src/vscode++.cc
GCCPLUGINS_DIR := $(shell $(TARGET_GCC) -print-file-name=plugin)
CXXFLAGS += -I./include -I$(GCCPLUGINS_DIR)/include -fPIC -fno-rtti -O2



libvscode++.so: $(PLUGIN_SOURCE_FILES)
	$(HOST_GCC) -shared $(CXXFLAGS) $^ -o $@

all: default


default: libvscode++.so


.PHONY: all