FROM silkeh/clang:14 as builder

WORKDIR /app

COPY . .

RUN cmake -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON . && cmake --build build -j

CMD ["./build/main"]
