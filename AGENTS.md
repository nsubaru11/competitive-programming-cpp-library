# AGENTS.md

## Project Big Picture

- This repository is a competitive-programming C++ library collection, not a single app or service.
- `src/lib/` is the includable API source tree, grouped as `lib/ds`, `lib/math`, and so on.
- `test/example/` contains usage examples; CMake registers every `.cpp` there as an executable.
- `docs/` contains module READMEs.
- Contest solutions copy the headers they use into the solution file. Do not add dependencies other than the C++ standard library (no ACL, no Boost).

## Coding Conventions

- Target C++23.
- Format with the rules below. The author keeps the canonical `.clang-format` and `.editorconfig` in the [parent repository](https://github.com/nsubaru11/competitive-programming), which this repository does not contain; they are mirrored here so that a standalone clone behaves the same.
	- Indent with tabs (width 4), use LF line endings, keep a trailing newline at end-of-file, and wrap at 120 columns.
	- Continuation indent is 8. Do not indent `namespace` bodies. Indent `case` labels. Put the pointer `*` and reference `&` next to the type (`int* p`).
	- Open braces on the same line. Do not align consecutive assignments, declarations, or trailing comments.
	- Sort includes as `<...>` first, then `"..."`.
- Follow the C++ standard library naming: `snake_case` for functions, methods, variables, and concepts; `PascalCase` for classes and structs. Match the method names of the sibling [Java library](https://github.com/nsubaru11/competitive-programming-java-library) by converting them to snake case (for example `rotateLeft` becomes `rotate_left`). The Java library is a naming reference only; it is not needed to build or use this repository.
- One public class per header at `src/lib/<package>/<ClassName>.hpp`, starting with `#pragma once`.
- Headers must include what they use and contain no `main`.

## Competitive-Programming Assumptions

- Evaluate APIs under valid contest constraints and inputs. Do not require defensive handling for states that cannot be produced by the problem input.
- Prefer speed, short hot paths, and readable contest code over exhaustive validation or general-purpose container contracts.
- Add validation or special-case handling only when it is required for valid contest inputs, prevents a realistic wrong answer, or has negligible cost and clearly improves the API.
- Do not repeatedly raise extreme-value cases (such as negating the minimum value of a signed type) as general concerns unless the user asks or the constraints of a target problem include them.
- Do not add utilities that merely wrap functionality already in the standard library.
- Documentation states the expected preconditions instead of implying that every invalid argument is checked.

## Developer Workflows

- Build with CMake 4.0 or later and a C++23 compiler (the author uses GCC 15.2). Configure with `cmake -S . -B <build dir>`, then build one example with `cmake --build <build dir> --target <name>`. The target name is the path under `test/example/` with `/` replaced by `_` (for example `test/example/ds/tree/Treap.cpp` becomes `ds_tree_Treap`).
- Build only the example that covers the changed header. Build every example only when the user asks.
- Keep build directories (`cmake-build-*`, `build/`) out of Git. They are ignored by `.gitignore`.
- When adding a header, add a usage example under `test/example/<package>/` and an entry in the matching module README under `docs/`.

## Documentation Conventions

- Use polite Japanese (です・ます) for reader-facing explanations and steps. Use plain directives (〜する / 〜しない) in Japanese instructions for AI agents. Keep parallel list items in the same grammatical form. End sentences with 。 and leave short labels and names unpunctuated. Use paragraphs for connected conditions or explanations and numbered lists for sequential steps.
- Follow the Documentation Conventions of the [Java library's AGENTS.md](https://github.com/nsubaru11/competitive-programming-java-library/blob/main/AGENTS.md) where they apply: concise Japanese, relative links, and claims verified against `src/`.
- A module README (`docs/<package>/README.md`) is a table of headers and a one-line description of each. The example under `test/example/` is the canonical usage, so do not embed per-class code blocks.

## Git

- This is a public repository. Before committing, check that the diff contains no secrets (sessions, passwords, tokens, e-mail addresses).
- Write commit messages in Japanese as `prefix: 概要`, with one of `feat`, `fix`, `refactor`, `docs`, `chore`.
- Push only when the user asks. Never force push, and do not rewrite history that has already been pushed.
