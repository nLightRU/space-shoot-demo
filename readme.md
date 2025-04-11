## Список
* LLVM/clang
* Ninja
* SFML 2.6.2


Создаём папки
build
    Debug
    Release

В папке Debug вызываем cmake ../.. -G Ninja -DCMAKE_BUILD_TYPE=Debug
В папке Release вызываем cmake ../.. -G Ninja -DCMAKE_BUILD_TYPE=Release

В папки Debug и Release копируем dll из SFML-2.6.2/bin (те файлы, у которых -d в конце)
В папки Debug и Release копируем папку resources


Спрайты
https://opengameart.org/content/vertical-shmup-set-1-m484-games

Звук
https://opengameart.org/content/space-shooter-music