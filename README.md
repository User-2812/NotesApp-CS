# NotesApp (CopperSpice)

Kleine Notizen-App mit CS

'' Build

```bash
CS_LIB_PREFIX=$(find ~ -type d -path "*/lib/cmake/CopperSpice")

echo $CS_LIB_PREFIX

cmake -B ./build -DCMAKE_PREFIX_PATH=$CS_LIB_PREFIX

cmake --build ./build

cmake --install ./build --prefix ./build

./build/NotesApp
