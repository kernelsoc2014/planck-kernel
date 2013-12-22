
project 'planck/lib' do
    dirs = [ '.' ]

    cc_files = mglob dirs, '*.c'

    cc_build = build :target_cc, cc_files, $kernel.cc_rules do
        # This should use SSE on x86_64 platforms
        # Should be replaced by common code in future
        remove_flag '-no-sse'
    end

    $kernel.sources << cc_build
end
