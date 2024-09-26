# Caches homework
Contains LFU cache and ideal cache implementation and their comparison.

## Building
To build both projects, do

```sh
cmake -S . -B build
cmake --build build
```

After building, `compare.py` script will automatically be launched, which compares LFU caching with ideal caching.
The results will be in the `compare_results.txt` file.

## Testing
To run tests for both projects, do
```sh
cd build
ctest -C Debug --parallel
```

## Conclusions

LFU cache does not differ much from ideal on my randomly generated tests (probably because cache hits are too sparse).

In real world scenario, however, the difference should be much more noticeable.