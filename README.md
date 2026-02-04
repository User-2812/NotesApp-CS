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


## Falls xcb Error
```bash
cd ~/NotesApp-CS

export CopperSpice_DIR=/home/user75/STEMgraph/cpplibs/cs2.1_libs/lib/cmake/CopperSpice

cmake -S . -B build -DCopperSpice_DIR="$CopperSpice_DIR"

cmake --build build -j "$(nproc)"

ls -la build/NotesApp

mkdir -p copperspice/deploy/platforms

mkdir -p copperspice/deploy/xcbglintegrations

ln -sf /home/user75/STEMgraph/cpplibs/cs2.1_libs/lib/CsGuiXcb2.1.so \
  copperspice/deploy/platforms/

ln -sf /home/user75/STEMgraph/cpplibs/cs2.1_libs/lib/CsGuiXcb_Glx2.1.so \
  copperspice/deploy/xcbglintegrations/

ls -la copperspice/deploy/platforms

ls -la copperspice/deploy/xcbglintegrations

unset SESSION_MANAGER 2>/dev/null || true

export CS_PLUGIN_PATH="$PWD/copperspice/deploy"

export LD_LIBRARY_PATH=/home/user75/STEMgraph/cpplibs/cs2.1_libs/lib:$LD_LIBRARY_PATH

./build/NotesApp
