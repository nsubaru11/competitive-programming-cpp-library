# AGENTS.md

## Project Big Picture

- This repository is a competitive-programming C++ library collection, not a single app or service.
- `src/lib/` is the includable API source tree, grouped as `lib/ds`, `lib/math`, and so on.
- `test/example/` contains usage examples; CMake registers every `.cpp` there as an executable.
- `docs/` contains module READMEs.

## Coding Conventions

- Target C++23 and follow `.clang-format`.
- Use tabs for indentation and keep a trailing newline at end-of-file.
- One public class per header at `src/lib/<package>/<ClassName>.hpp`, starting with `#pragma once`.
- Headers must include what they use and contain no `main`.
