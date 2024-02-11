#### Конфигурируем проект для Google тестов

```console
cmake -D GLOB_THIRD_PARTY_DIR=/Users/<USER_NAME>/Documents/Third-party \
      -D GLOB_LIBPNG_ROOT_DIR=/opt/homebrew/Cellar/libpng/1.6.40 \
      -D GLOB_FT2_ROOT_DIR=/opt/homebrew/Cellar/freetype/2.13.2 \
      -D GLOB_GTEST_ROOT_DIR=/Users/<USER_NAME>/Documents/Third-party/googletest/googletest \
      -D GLOB_GTEST_LIB_DIR=/Users/<USER_NAME>/Documents/Third-party/googletest/build/lib \
      -D GLOB_GMOCK_ROOT_DIR=/Users/<USER_NAME>/Documents/Third-party/googletest/googlemock \
      -D GLOB_GMOCK_LIB_DIR=/Users/<USER_NAME>/Documents/Third-party/googletest/build/lib \
      -D MODULE_RMS_LIB_TYPE=object \
      -D MODULE_RENDER_LIB_TYPE=object \
      -D MODULE_UI_ENABLE_TESTS=ON \
      ../
```

#### Запускаем сборку

```console
cmake --build ./
```
