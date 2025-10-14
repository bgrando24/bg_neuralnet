# syntax=docker/dockerfile:1
FROM ubuntu:24.04 AS builder

RUN apt-get update && apt-get install -y \
    build-essential cmake ninja-build git curl pkg-config zip unzip tar \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# vcpkg and bootstrap
COPY vcpkg ./vcpkg
RUN rm -f vcpkg/vcpkg && \
    cd vcpkg && ./bootstrap-vcpkg.sh -disableMetrics

# source files
COPY vcpkg.json vcpkg-configuration.json CMakeLists.txt CMakePresets.json ./
COPY src ./src
COPY tests ./tests

# build both debug (for testing) and release (for runtime)
RUN --mount=type=cache,target=/root/.cache/vcpkg \
    cmake --preset debug && \
    cmake --build --preset build-debug && \
    cd build && ctest --output-on-failure --verbose && \
    cd .. && \
    cmake --preset release && \
    cmake --build --preset build-release

# min runtime image with release build (no sanitizers)
FROM ubuntu:24.04
WORKDIR /app
COPY --from=builder /app/build/app .
COPY --from=builder /app/build/run_tests .

# "start" script just runs both 'ctest' and the 'app' executable sequentially
RUN echo '#!/bin/sh\n\
    echo "Running tests..."\n\
    ./run_tests\n\
    echo "\n--- Tests passed! Running app ---\n"\n\
    ./app' > /app/start.sh && chmod +x /app/start.sh

CMD ["/app/start.sh"]