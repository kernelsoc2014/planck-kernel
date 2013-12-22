$kernel.arch_dir = 'x86_64'
$kernel.includes = [ file('arch/x86_64/include') ]
$kernel.defines = {
    :__x86_64__ => 1,
    :_PLANCK_KERNEL => 1
}

$kernel.basic_rules = Configuration.new $kernel.basic_rules do
    includes $kernel.includes
    defines $kernel.defines
end

$kernel.cc_rules = Configuration.new $kernel.basic_rules, $kernel.cc_rules do
    flags '-m64'

    # Don't autogenerate SSE instructions
    flags '-mno-sse'

    flags '-mtune=generic'
    flags '-mno-red-zone'
    flags '-mcmodel=kernel'

    flags '-ffreestanding'
    flags '-maccumulate-outgoing-args'
end

$kernel.as_rules = Configuration.new $kernel.basic_rules, $kernel.as_rules do
    flags '-m64'
end

import '../acpica'
