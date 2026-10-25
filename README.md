# Лабораторная работа 2
# Класс с ручным управлением памятью

## Цель работы

Реализовать строковый класс String с ручным управлением динамической памятью. Освоить RAII, правило пяти и идиому copy-and-swap.

Семейство A, вариант 3: проверка строки на палиндром.

## Структура проекта

```
oop-lab-2/
├── my_string.h       # объявление класса String
├── my_string.cpp     # реализация методов
├── tests.cpp         # тесты Google Test
├── CMakeLists.txt    # сборка проекта
└── README.md
```

## Краткая справка по использованию

- size() - количество символов в строке
- capacity() - текущая емкость буфера без завершающего '\0'
- str() - указатель на содержимое строки
- append(str) - добавление строки в конец
- find(str) - поиск первого вхождения подстроки, при отсутствии возвращается String::npos
- swap(other) - обмен содержимым двух объектов
- print(out) - вывод строки в поток
- is_palindrome() - проверка на палиндром

Поддерживаются создание пустой строки, создание из const char*, копирование, перемещение и присваивание. Память выделяется через new[] и освобождается в деструкторе через delete[]. Присваивание реализовано через copy-and-swap.

```cpp
String s1("Hello");
String s2(s1);
s2.append(", World!");
s2.print(std::cout);

String s3("level");
std::cout << s3.is_palindrome(); // 1
```

## Используемые инструменты

- C++20
- CMake 3.16+
- Google Test 1.14.0

## Сборка и запуск тестов

Команды выполняются из корня проекта.

```bash
cmake -S . -B build
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

## Проверка памяти

Для Linux или Ubuntu в WSL с поддержкой AddressSanitizer:

```bash
cmake -S . -B build-asan -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="-fsanitize=address -g -fno-omit-frame-pointer"
cmake --build build-asan
ASAN_OPTIONS=detect_leaks=1 ctest --test-dir build-asan --output-on-failure
```

## Вывод

Освоены ручное управление динамической памятью, RAII, копирование и перемещение объектов. Реализованы строковый класс, основные операции над строками и проверка на палиндром. Написаны тесты и выполнена проверка памяти через AddressSanitizer.

## Автор

Прудников Ярослав Александрович М8О-203БВ-25 (aka YALAMA)
