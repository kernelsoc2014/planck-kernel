require 'sensei/compilers/gcc'
require 'sensei/compilers/binutils'

class CSymbolGeneratorConfiguration < Compilers::CCompilerConfiguration
  attr_reader :_output

  def output(out)
    @_output = out
  end
end

class CSymbolGeneratorBuilder < Compilers::CCompilerBuilder
  def get_output_name(input)
    input = input.convert('.h', :projectbuild)
    input = input.rebase @config._output if @config._output
    input
  end
end

class CSymbolGenerator < Rule
  def initialize(path, toolpath)
    super() do
      description "SYM $out"
      command "sh -c \"set -o pipefail; #{path} -MMD -MT $out -MF $out.d $flags -S $in -o - | #{toolpath} > $out\""
      depfile "$out.d"
      deps "gcc"
    end
  end

  def create_config(*args, &block)
    CSymbolGeneratorConfiguration.new *args, &block
  end

  def create_builder(rule, config, input)
    CSymbolGeneratorBuilder.new rule, config, input
  end
end

target_toolchain_prefix = ENV['TARGET_TOOLCHAIN_PREFIX'] || 'x86_64-elf-'

rule :target_cc => Compilers::CCompiler.new(target_toolchain_prefix + "gcc")
rule :target_cxx => Compilers::CCompiler.new(target_toolchain_prefix + "g++")
rule :target_cpp => Compilers::CPreprocessor.new(target_toolchain_prefix + "cpp")
rule :target_as => Compilers::CCompiler.new(target_toolchain_prefix + "gcc")
rule :target_ar => Compilers::CLibrarian.new(target_toolchain_prefix + "ar")
rule :target_ld => Compilers::CLinker.new(target_toolchain_prefix + "ld")
rule :target_objcopy => Compilers::CObjCopy.new(target_toolchain_prefix + "objcopy")
rule :gensym => CSymbolGenerator.new(target_toolchain_prefix + "gcc", file('tools/gensym.rb').to_build.to_s)
