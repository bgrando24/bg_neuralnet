# C++ Project Skeleton

This repository is a personal starter kit for modern C++ projects. It couples CMake with the vcpkg package manager so that dependency resolution, toolchain setup, and cross-platform builds work with a handful of commands on any machine.

## What you get

-   CMake 4.1+ project configured for C++20
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

**Windows**

1. Install the following:
    - Visual Studio Build Tools (C++ workload) or the full IDE
    - Git for Windows
    - CMake
    - Ninja (optional but recommended)
2. Ensure `cmake`, `ninja`, and `git` are on the `PATH`.

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
    ./vcpkg/bootstrap-vcpkg.sh              # Windows PowerShell: .\vcpkg\bootstrap-vcpkg.bat
    ```
3. Configure and build using the provided CMake presets:
    ```sh
    cmake --preset release                  # or --preset debug
    cmake --build --preset build-release    # or build-debug
    ```
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
-   `.vscode/` – optional editor configuration

---

## Troubleshooting

-   Missing headers? Re-run `cmake --preset <config>` to trigger vcpkg installation, then rebuild.
-   Build directory in a bad state? Remove `build/` (or run `cmake --fresh --preset <config>` when on CMake ≥ 3.24) and reconfigure.
-   Upgrading compilers or clang-tidy? Add configuration-specific cache variables in `CMakePresets.json`.

Happy hacking!
