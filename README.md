# cpp-knowledge-base

C++ knowledge base project.

**Stack:** C++20, CMake 3.16+, Ubuntu 24.04 (GCC, CMake, Git)

## Prerequisites

- [Docker](https://docs.docker.com/get-docker/) — for the development environment
- CMake 3.16+ — only needed if building outside Docker

## Development environment

Docker provides a consistent build environment. Scripts live in `docker/`:

| Script | Purpose |
|--------|---------|
| `docker_run.sh` | Start an interactive shell (builds the image on first run) |
| `docker_build.sh` | Rebuild the `cpp-env` image |
| `docker_clean.sh` | Stop containers and remove the `cpp-env` image |

Start the environment from the project root:

```bash
./docker/docker_run.sh
```

Your project directory is mounted at `/project` inside the container.

Clean up when done:

```bash
./docker/docker_clean.sh
```

## VS Code Dev Containers

The [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) extension opens the project in the same Docker image. It installs C++ and CMake extensions automatically.

1. Open the project in VS Code
2. **Ctrl+Shift+P** → **Dev Containers: Reopen in Container**

The container uses `docker/Dockerfile` (same as `docker_run.sh`).

## Build

CMake is the build system. Two presets are defined in `CMakePresets.json`:

| Preset | Output directory | Flags |
|--------|------------------|-------|
| `release` | `build/release` | `-O3` |
| `debug` | `build/debug` | `-O3 -g -fno-omit-frame-pointer` |

From inside the container (or locally with CMake installed):

```bash
cmake --preset release
cmake --build --preset release
```

Or for a debug build with symbols:

```bash
cmake --preset debug
cmake --build --preset debug
```

Run an example executable:

```bash
./build/release/abstract_factory
# or
./build/debug/abstract_factory
```

Clean build outputs:

```bash
rm -rf build
```

## Project layout

```
.
├── CMakeLists.txt          # Root CMake project
├── CMakePresets.json       # Debug and release build presets
├── src/                    # Examples and exercises
├── docker/                 # Docker image and helper scripts
└── .devcontainer/          # VS Code Dev Container config
```

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) and [CODE_STYLE.md](CODE_STYLE.md).

## License

Apache License 2.0 — see [LICENSE](LICENSE).
