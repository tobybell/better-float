SYSROOT = /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk

better-float: better-float.cc
	clang++ -o $@ -std=c++20 -O2 --sysroot=$(SYSROOT) $^
