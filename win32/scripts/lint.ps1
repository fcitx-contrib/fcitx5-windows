git ls-files -- '*.cpp' '*.h' | ForEach-Object {
  clang-format -Werror --dry-run $_ 
  if ($LASTEXITCODE -ne 0) {
    exit 1
  }
}
