# cmake -DCMAKE_BUILD_TYPE=Debug -B /home/hpca/xdev/development/first+jolt/build -S /home/hpca/xdev/development/first+jolt/ -DJPH_CROSS_PLATFORM_DETERMINISTIC=ON && \
# make -j 6 all -C /home/hpca/xdev/development/first+jolt/build && \
# ./build/test/FirstJolt_test
current_dir=$(dirname "$0")
cmake -DCMAKE_BUILD_TYPE=Debug -B $current_dir/build -S $current_dir -DJPH_CROSS_PLATFORM_DETERMINISTIC=ON -DJPH_DEBUG_RENDERER=ON && \
make -j 6 all -C $current_dir/build && \
$current_dir/build/src/main

