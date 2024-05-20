# Компилятор языка DOTA
## Установка

> [!IMPORTANT]
> Данный компилятор можно запустить только на ОС Linux.

Чтобы его запустить вам понадобится:

1) Установить компилятор g++ и gcc.

2) Склонировать данный репозиторий. Для этого введите следующую команду в терминале:
``` bash
    git clone git@github.com:SANEKDASH/Binary-translator.git
```
3) Далее перейдите в директорию, созданную git-ом с помощью команды:
``` bash
    cd Binary-translator
```
4) Теперь вам нужно собрать проект с помощью команды `make`.

## Запуск
Чтобы получить объектный файл, созданный на основе написанного вами кода на языке __DOTA__,
сначала вам нужно получить файлы с синтаксическим деревом и таблицей имен. Для этого введите
следующую команду в терминал:
``` bash
    ./front <путь к файлу с текстом программы>
```
На выходе вы получите два файла: 'tree_save.txt' и 'id_table.txt'.

Далее вы должны получить объектный файл на основе двух предыдущих.
Для этого введите следующую команду в терминал:
``` bash
    ./back tree_save.txt id_table.txt <желаемое имя объектного файла>
```

Итак, вы получили объектный файл, теперь вам нужно получить исполняемый.
Для этого вам нужно слинковать полученный объектный файл с стандартной библиотекой языка '__DOTA__' и языком Си. Для этого используйте следующую команду:
``` bash
    gcc <имя объектного файла> lib/gavno.o -lm -o <желаемое имя исполняемого файла>
```

Далее осталось только запустить исполняемый файл с помощью команды:
``` bash
    ./<путь к исполняемому файла>
```
