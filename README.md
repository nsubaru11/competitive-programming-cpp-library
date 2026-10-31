![C++23](https://img.shields.io/badge/C%2B%2B-23-00599C?style=flat-square)
![Dependencies: none](https://img.shields.io/badge/dependencies-none-4C9A2A?style=flat-square)
[![License: 0BSD](https://img.shields.io/badge/license-0BSD-blue?style=flat-square)](./LICENSE)

# Competitive Programming C++ Library

競技プログラミング向けのアルゴリズム・データ構造をC++で実装したリポジトリです。

- [Author: nsubaru (AtCoder)](https://atcoder.jp/users/nsubaru)

## モジュール一覧

| フォルダ      | 主な内容     | ドキュメント                          |
|---------------|--------------|---------------------------------------|
| `src/lib/ds`  | データ構造   | [モジュール一覧](./docs/ds/README.md)   |
| `src/lib/math`| 数論         | [モジュール一覧](./docs/math/README.md) |

## 使い方

`src` をインクルードパスに追加し、ヘッダーをインクルードします。

```cpp
#include "lib/ds/tree/ImplicitTreap.hpp"
#include "lib/math/ModPow.hpp"
```

## 構成

- `src/lib/`: インクルードして使うライブラリ本体
- `test/example/`: 利用例。CMake で実行ファイルとして登録される
- `docs/`: モジュールのドキュメント
