
project 'kernel/arch' do
    dirs = [ 'kernel' ]
    deps = find_packages "kernel/arch"

    cc_files = mglob dirs, '*.c'
    cxx_files = mglob dirs, '*.cpp'
    as_files = mglob dirs, '*.s'

    cc_build = build :target_cc, cc_files, $kernel.cc_rules
    cxx_build = build :target_cxx, cxx_files, $kernel.cxx_rules
    as_build = build :target_as, as_files, $kernel.as_rules

    lds = build :target_cpp, files('kernel/planck_kernel.lds'), $basic_rules do
        flags '-P -x assembler-with-cpp'
    end

    $kernel.sources << cc_build
    $kernel.sources << cxx_build
    $kernel.sources << as_build

    $kernel.linker_script = lds
end
