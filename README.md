# C++ Project Skeleton

This repository is a personal starter kit for modern C++ projects. It couples CMake with the vcpkg package manager so that dependency resolution, toolchain setup, and cross-platform builds work with a handful of commands on any machine.

## What you get

-   CMake 3.25+ project configured for C++20
-   vcpkg integrated via the CMake toolchain file and pinned registry baseline
-   Ninja-based CMake presets for debug/release builds
-   Example `src/main.cpp` using bundled `spdlog` and `nlohmann-json`
-   GitHub Actions workflow that builds on Linux, macOS, and Windows
-   VS Code IntelliSense configuration pointing at vcpkg headers

---

## Prerequisites (run once per machine)

Install the usual build tools, CMake ≥ 3.25, Git, and Ninja (preferred). Example commands:

**Ubuntu/Debian**

```sh
sudo apt update
sudo apt install -y build-essential cmake ninja-build git curl pkg-config
```

**macOS (Homebrew)**

```sh
xcode-select --install
brew install cmake ninja git
```

**Windows (MSVC)**

1. Install: Visual Studio Build Tools (C++), Git, CMake, (optional) Ninja.
2. Open an **x64 Native Tools Command Prompt for VS** (or run `vcvarsall.bat`) so `cl.exe` is on PATH.
    - If you prefer MinGW instead of MSVC, set `VCPKG_TARGET_TRIPLET=x64-mingw-dynamic` before configuring.

---

## Quick start (new project)

1. Clone the skeleton and rename the remote when ready:
    ```sh
    git clone https://github.com/bgrando24/cpp_skeleton.git my_new_project
    cd my_new_project
    ```
2. Pull submodules and bootstrap vcpkg:

    ```sh
    git submodule update --init --recursive
    ./vcpkg/bootstrap-vcpkg.sh
    # Windows PowerShell: .\vcpkg\bootstrap-vcpkg.bat
    ```

    > **Windows tip:** Run the commands from an **MSVC Developer Prompt** so CMake/Ninja use `cl.exe`
    > (matches vcpkg’s `x64-windows` triplet). If you use MinGW, set `VCPKG_TARGET_TRIPLET=x64-mingw-dynamic`.

3. Configure and build using the provided CMake presets:

    ```sh
    cmake --preset release                  # or --preset debug
    cmake --build --preset build-release    # or build-debug
    ```

    - If you get a “could not read presets” error on older CMake, either upgrade CMake (≥3.27 for Presets v8)
      or edit `CMakePresets.json` and set `"version": 6`.

4. Run the sample app:
    ```sh
    ./build/app                             # Windows: .\build\app.exe
    ```

During development you only need `cmake --build --preset build-<config>` to rebuild.

---

## Customise for your own project

-   Update the project name in `CMakeLists.txt` (`project(...)`) and `vcpkg.json` (`"name"`).
-   Replace `src/main.cpp` with your own sources and adjust `add_executable` / `target_sources` as needed.
-   Add a `.gitignore` (at minimum ignore `build/`, `vcpkg_installed/`, and `.cache/`) before committing to a new repo.
-   Optional: re-run `git remote set-url origin <your new remote>` and remove history with `git checkout --orphan main` if you want a clean slate.

---

## Run with docker

```sh
docker build -t <container-name> .
docker run <container-name>
```

---

## Managing dependencies with vcpkg

-   Declare dependencies in `vcpkg.json`. Example:
    ```json
    {
        "name": "my-app",
        "dependencies": ["fmt", "range-v3"]
    }
    ```
-   After editing `vcpkg.json`, re-run `cmake --preset <config>` so vcpkg can install the new packages.
-   The pinned registry baseline in `vcpkg-configuration.json` locks dependency versions. Update it with `git -C vcpkg rev-parse HEAD` when you intentionally upgrade vcpkg.

---

## CMake presets overview

-   `CMakePresets.json` defines a shared configuration (`base`) that uses Ninja, writes to `build/`, and points CMake at the vcpkg toolchain.
-   `release` and `debug` presets inherit from `base`. The matching `build-*` presets drive `cmake --build`.
-   Add more presets (e.g. different generators or sanitizer builds) by extending `configurePresets`.

---

## Testing with CTest

CMake has built-in testing for your **executables**, called `CTest`.

In short, CTest is intended for testing whether executables run without error and also allows you to pass in arguments.

**To add your own tests inside the `CMakeLists.txt` file:**

1. Ensure your executable is built by CMake along with any required libraries

```CMake
# create an executable called "app", using src/main.cpp
add_executable(app src/main.cpp)
# libraries to link, for example:
target_link_libraries(app PRIVATE
  spdlog::spdlog
  nlohmann_json::nlohmann_json
)
```

2. Testing should already be enabled, but check `enable_testing()` is present:

```CMake
# place this before adding any tests, should be there already in this skeleton
enable_testing()
```

3. Add your test! The syntax is straightforward:

```CMake
# syntax: NAME <arbitrary name for test> COMMAND <executable name you defined above>
# to pass in arguments, just add them after the name of the executable, for example:
    # add_test(NAME test_main COMMAND app arg1 arg2 ...)
add_test(NAME test_main COMMAND app)
```

4. To run tests:

```sh
# build the project, e.g. "cmake --build --preset build-debug"
cd build
ctest
```

And that's it! Your terminal output should look something like:

```sh
Test project <project_dir>/cpp_skeleton/build
    Start 1: <name of your test>
1/2 Test #1: <name of your test> ..............   Passed    0.00 sec
    Start 2: <name of second test>
2/2 Test #2: <name of second test> ............   Passed    0.00 sec

100% tests passed, 0 tests failed out of 2

Total Test time (real) =   0.01 sec
```

### More resources:

-   Handy tutorial: https://cmake.org/cmake/help/book/mastering-cmake/chapter/Testing%20With%20CMake%20and%20CTest.html
-   Or official docs: https://cmake.org/cmake/help/book/mastering-cmake/chapter/Testing%20With%20CMake%20and%20CTest.html

---

## Continuous integration

`.github/workflows/ci.yml`:

-   Checks out code with submodules, bootstraps vcpkg, configures with the `release` preset, and builds using `build-release`.
-   Runs the sample executable on Linux and macOS as a smoke test.
-   Extend the workflow with test commands or extra cache steps as your project grows.

---

## Repository layout

-   `CMakeLists.txt` – top-level CMake configuration
-   `CMakePresets.json` – shared presets for configure/build
-   `src/main.cpp` – sample application
-   `vcpkg.json` – vcpkg manifest
-   `vcpkg-configuration.json` – pinned registry baseline
-   `vcpkg/` – vcpkg submodule

---

## Troubleshooting

-   Missing headers? Re-run `cmake --preset <config>` to trigger vcpkg installation, then rebuild.
-   Build directory in a bad state? Remove `build/` (or run `cmake --fresh --preset <config>` when on CMake ≥ 3.24) and reconfigure.
-   Upgrading compilers or clang-tidy? Add configuration-specific cache variables in `CMakePresets.json`.
