$kernel = OpenStruct.new
$kernel.sources = Array.new
$kernel.basic_rules = Configuration.new $target.basic_rules do
    includes file('include')
    defines :__KERNEL__ => 1
end

kataload "config/#{$configuration.platform}/kernel.rb"

$kernel.as_rules = Configuration.new $kernel.as_rules do
    flags '-Wall -Wextra'
    defines :__ASSEMBLER__ => 1
end

$kernel.cc_rules = Configuration.new $kernel.cc_rules do
    flags '-Wall'
end

$kernel.cxx_rules = Configuration.new $kernel.cc_rules, $kernel.cxx_rules do
    flags '-fno-exceptions -fno-rtti'
end

$kernel.cc_rules = Configuration.new $kernel.cc_rules do
    flags '-std=c99'
end

import 'arch/' + $kernel.arch_dir
import 'lib'
import 'kernel'
