require 'sensei/compilers/gcc'
require 'sensei/compilers/binutils'

$configuration.arch_dir = 'arm'

target_toolchain_prefix = ENV['TARGET_TOOLCHAIN_PREFIX'] || 'arm-elf-'

rule :target_cc => Compilers::CCompiler.new(target_toolchain_prefix + "gcc")
rule :target_cxx => Compilers::CCompiler.new(target_toolchain_prefix + "g++")
rule :target_as => Compilers::CCompiler.new(target_toolchain_prefix + "gas")
rule :target_ar => Compilers::CLibrarian.new(target_toolchain_prefix + "ar")
rule :target_ld => Compilers::CLinker.new(target_toolchain_prefix + "gcc")

$basic_rules = Configuration.new do
    defines :ARCH_ARM => 1
end

abort "Incomplete platform."
