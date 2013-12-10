require 'sensei/compilers/gcc'
require 'sensei/compilers/binutils'

$configuration.arch_dir = 'x86'

target_toolchain_prefix = 'i686-elf-' if $configuration.platform == 'x86'
target_toolchain_prefix = 'x86_64-elf-' if $configuration.platform == 'x86_64'
target_toolchain_prefix = ENV['TARGET_TOOLCHAIN_PREFIX'] || target_toolchain_prefix

rule :target_cc => Compilers::CCompiler.new(target_toolchain_prefix + "gcc")
rule :target_cxx => Compilers::CCompiler.new(target_toolchain_prefix + "g++")
rule :target_cpp => Compilers::CPreprocessor.new(target_toolchain_prefix + "cpp")
rule :target_as => Compilers::CCompiler.new(target_toolchain_prefix + "gcc")
rule :target_ar => Compilers::CLibrarian.new(target_toolchain_prefix + "ar")
rule :target_ld => Compilers::CLinker.new(target_toolchain_prefix + "ld")
rule :target_objcopy => Compilers::CObjCopy.new(target_toolchain_prefix + "objcopy")
