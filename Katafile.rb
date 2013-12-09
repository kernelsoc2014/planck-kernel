require 'ostruct'

$configuration = OpenStruct.new
$configuration.configuration = ENV['CONFIGURATION'] || 'Checked'
$configuration.platform = ENV['PLATFORM'] || 'x86'
$configuration.output = file("build/#{$configuration.platform}/#{$configuration.configuration}/")

if not [ "Checked", "Free" ].include? $configuration.configuration then
    abort "Invalid configuration #{$configuration.configuration}."
end

if not [ "x86", "x86_64", "arm" ].include? $configuration.platform then
    abort "Invalid platform #{$configuration.platform}."
end

$target = OpenStruct.new
$target.basic_rules = Configuration.new $basic_rules do
    includes file('include')

    defines :BUILD_CHECKED => 1 if $configuration.configuration == "Checked"
    defines :BUILD_FREE => 1 if $configuration.configuration == "Free"
end

kataload "config/#{$configuration.platform}/arch.rb"
kataload "kernel.rb"
