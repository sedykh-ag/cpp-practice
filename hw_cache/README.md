# Caches homework
Contains LFU cache and ideal cache implementation and their comparison.

## LFU Cache
**Build**
```sh
cd lfu
cmake -S . -B build
cmake --build build
```
**Run tests**
```sh
cd build
ctest -C Debug
```

## Ideal Cache
**Build**
```sh
cd ideal
cmake -S . -B build
cmake --build build
```
**Run tests**
```sh
cd build
ctest -C Debug
```

## Comparison
To compare LFU cache with ideal caching, run
```sh
python compare.py
```

## Conclusions

LFU cache does not differ much from ideal on my randomly generated tests (probably because cache hits are too sparse).

In real world scenario, however, the difference should be much more noticeable.