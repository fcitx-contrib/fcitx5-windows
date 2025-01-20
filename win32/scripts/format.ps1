git ls-files -- '*.cpp' '*.h' | ForEach-Object { clang-format -i $_ }
