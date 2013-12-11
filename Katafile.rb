require 'ostruct'

$configuration = OpenStruct.new
$configuration.configuration = ENV['PLANCK_CONFIGURATION'] || 'Checked'
$configuration.platform = ENV['PLANCK_PLATFORM'] || 'x86'

# Fix for Windows builds
if ENV['PLANCK_BUILD_OUT'] then
    path = Pathname.new(File.realpath(ENV['PLANCK_BUILD_OUT'])).relative_path_from(Pathname.pwd)
    $configuration.output = file(path)
else
    $configuration.output = file("build/#{$configuration.platform}/#{$configuration.configuration}/")
end

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
import 'planck'
