find libc/ -iname '*.h' -o -iname '*.c' | xargs clang-format -i
find kernel/ -iname '*.h' -o -iname '*.c' | xargs clang-format -i