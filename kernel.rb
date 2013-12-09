$kernel = OpenStruct.new
$kernel.sources = Array.new
$kernel.basic_rules = $target.basic_rules

kataload "config/#{$configuration.platform}/kernel.rb"

$kernel.as_rules = Configuration.new $kernel.basic_rules, $kernel_as_rules do
    flags '-Wall -Wextra -nostdinc'
    defines :IN_ASM => 1
end

$kernel.cc_rules = Configuration.new $kernel.basic_rules, $kernel_cc_rules do
    flags '-Wall -Wextra -nostdinc'
end

$kernel.cxx_rules = Configuration.new $kernel.cc_rules, $kernel_cxx_rules do
    flags '-fno-exceptions -fno-rtti'
end

import 'arch/' + $configuration.arch_dir
import 'kernel'
