Простая сборка
cmake ..
make -j[количество ядер/потоков]



//Конфигурация и cборка для Debug режима средствами CMake
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . -j40


//Конфигурация для Release режима для cистемы сборки ninja
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release ..
ninja


//Подключение библиотек для Debug режима
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/run/media/alexey/LinuxData/Cascade/occt_linux_build780/lin64/gcc/libd/

//Подключение библиотек для Release режима
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/run/media/alexey/LinuxData/Cascade/occt_linux_build780/lin64/gcc/lib/

//Запуск приложения
./SimpleGM


