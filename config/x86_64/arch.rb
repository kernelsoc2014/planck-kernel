require 'sensei/compilers/gcc'
require 'sensei/compilers/binutils'

target_toolchain_prefix = ENV['TARGET_TOOLCHAIN_PREFIX'] || 'x86_64-elf-'

rule :target_cc => Compilers::CCompiler.new(target_toolchain_prefix + "gcc")
rule :target_cxx => Compilers::CCompiler.new(target_toolchain_prefix + "g++")
rule :target_cpp => Compilers::CPreprocessor.new(target_toolchain_prefix + "cpp")
rule :target_as => Compilers::CCompiler.new(target_toolchain_prefix + "gcc")
rule :target_ar => Compilers::CLibrarian.new(target_toolchain_prefix + "ar")
rule :target_ld => Compilers::CLinker.new(target_toolchain_prefix + "ld")
rule :target_objcopy => Compilers::CObjCopy.new(target_toolchain_prefix + "objcopy")
