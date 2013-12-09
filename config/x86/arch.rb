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

if $configuration.platform == 'x86' then
    basic_rules = Configuration.new do
        defines :__i386__ => 1
    end

    cc_rules = Configuration.new do
        flags '-m32'
        flags '-msoft-float -mregparm=3 -freg-struct-return'

        # Don't autogenerate SSE instructions
        flags '-mno-sse'

        # Never want PIC in a 32-bit kernel, prevent breakage with GCC built
        # with nonstandard options
        flags '-fno-pic'

        flags '-ffreestanding'
    end

    as_rules = Configuration.new do
        flags '-m32'
    end
elsif $configuration.platform == 'x86_64' then
    basic_rules = Configuration.new do
        defines :__x86_64__ => 1
    end

    cc_rules = Configuration.new do
        flags '-m64'

        # Don't autogenerate SSE instructions
        flags '-mno-sse'

        flags '-mtune=generic'
        flags '-mno-red-zone'
        flags '-mcmodel=kernel'

        flags '-ffreestanding'
        flags '-maccumulate-outgoing-args'
    end

    as_rules = Configuration.new do
        flags '-m64'
    end
end

$basic_rules = Configuration.new $basic_rules, basic_rules

$kernel_cc_rules = Configuration.new $kernel_cc_rules, cc_rules do
    flags '-pipe'
    flags '-Wno-sign-compare'
    flags '-fno-asynchronous-unwind-tables'
    flags '-mno-sse -mno-mmx -mno-sse2 -mno-3dnow'
    flags '-mno-avx'
end

$kernel_as_rules = Configuration.new $kernel_as_rules, as_rules
