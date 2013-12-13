
project 'planck' do
    dirs = [ '.' ]

    cc_files = mglob dirs, '*.c'
    cxx_files = mglob dirs, '*.cpp'

    cc_build = build :target_cc, cc_files, $kernel.cc_rules
    cxx_build = build :target_cxx, cxx_files, $kernel.cxx_rules

    $kernel.sources << cc_build
    $kernel.sources << cxx_build
end

project 'planck_kernel' do
    planck_kernel = build :target_ld, $kernel.sources, $kernel.ld_rules do
        flags '-z max-page-size=0x1000'

        memmap file('planck_kernel.map', :projectbuild)

        depends $kernel.linker_script
        script $kernel.linker_script
        output $configuration.output + 'boot/planck_kernel'
    end

    register_package :libinput => planck_kernel
end
