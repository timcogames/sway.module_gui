#### Конфигурируем проект для Google тестов

```console
cmake -D CMAKE_BUILD_TYPE=Release \
      -D GLOB_THIRD_PARTY_DIR=/Users/<USER_NAME>/Documents/Third-party \
      -D GLOB_LIBPNG_ROOT_DIR=/opt/homebrew/Cellar/libpng/1.6.44 \
      -D GLOB_FT2_ROOT_DIR=/opt/homebrew/Cellar/freetype/2.13.3 \
      -D GLOB_GTEST_ROOT_DIR=/Users/<USER_NAME>/Documents/Third-party/googletest/googletest \
      -D GLOB_GTEST_LIB_DIR=/Users/<USER_NAME>/Documents/Third-party/googletest/build/lib \
      -D GLOB_GMOCK_ROOT_DIR=/Users/<USER_NAME>/Documents/Third-party/googletest/googlemock \
      -D GLOB_GMOCK_LIB_DIR=/Users/<USER_NAME>/Documents/Third-party/googletest/build/lib \
      -D MODULE_RMS_LIB_TYPE=object \
      -D MODULE_RENDER_LIB_TYPE=object \
      -D MODULE_UI_ENABLE_TESTS=ON \
      -D MODULE_UI_LIB_TYPE=static \
      -D MODULE_UI_USE_GMOCK=ON \
      ../
```

#### Запускаем сборку

```console
cmake --build ./
```
