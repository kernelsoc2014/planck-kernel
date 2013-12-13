#!/bin/env ruby

SEPARATOR = "#DEFINITION#"

puts "#pragma once"

text = ARGF.read
text.each_line do |line|
    line.strip!
    next unless line.start_with? SEPARATOR
    puts line[SEPARATOR.length..-1].gsub(/\$/, '')
end
