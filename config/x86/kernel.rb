if $configuration.platform == 'x86' then
    basic_rules = Configuration.new $kernel.basic_rules do
        includes files('arch/x86/include', 'arch/x86/include/x86')
        defines :__i386__ => 1
    end

    cc_rules = Configuration.new basic_rules do
        flags '-m32'
        flags '-msoft-float -mregparm=3 -freg-struct-return'

        # Don't autogenerate SSE instructions
        flags '-mno-sse'

        # Never want PIC in a 32-bit kernel, prevent breakage with GCC built
        # with nonstandard options
        flags '-fno-pic'

        flags '-ffreestanding'
    end

    as_rules = Configuration.new basic_rules do
        flags '-m32'
    end
elsif $configuration.platform == 'x86_64' then
    basic_rules = Configuration.new basic_rules do
        includes files('arch/x86/include', 'arch/x86/include/x64')
        defines :__x86_64__ => 1
    end

    cc_rules = Configuration.new basic_rules do
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

$kernel.as_rules = Configuration.new $kernel.as_rules, as_rules do
end

$kernel.cc_rules = Configuration.new $kernel.cc_rules, cc_rules
