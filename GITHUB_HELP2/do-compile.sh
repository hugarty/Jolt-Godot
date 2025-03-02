current_dir=$(dirname "$0")
cmake -DCMAKE_BUILD_TYPE=Debug -B $current_dir/build -S $current_dir -DJPH_CROSS_PLATFORM_DETERMINISTIC=ON -DJPH_DEBUG_RENDERER=ON && \
make VERBSE=1 -j 6 all -C $current_dir/build && \
$current_dir/build/src/main

