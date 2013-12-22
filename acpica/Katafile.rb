$kernel.includes << file('include')

project 'acpica' do
    dirs = [
        'common',
        'oslayer',
        'components/debugger',
        'components/disassembler',
        'components/dispatcher',
        'components/events',
        'components/executer',
        'components/hardware',
        'components/namespace',
        'components/parser',
        'components/resources',
        'components/tables',
        'components/utilities'
    ]

    cc_files = mglob dirs, '*.c'
    cc_build = build :target_cc, cc_files, $kernel.cc_rules
    $kernel.sources << cc_build
end
