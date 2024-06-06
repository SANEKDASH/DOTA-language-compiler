# Компилятор языка DOTA
## Установка

> [!IMPORTANT]
> Данный компилятор можно запустить только на ОС Linux.

Чтобы его запустить вам понадобится:

1) Установить компилятор g++ и dot.

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
    gcc <путь к объектному файлу> lib/gavno.o -lm -o <желаемое имя исполняемого файла>
```

Далее осталось только запустить исполняемый файл с помощью команды:
``` bash
    ./<путь к исполняемому файлу>
```

## Как это работает?
Компилятор языка '__DOTA__', как было указано выше, состоит из двух частей: __фронтенд__ и __бэкенд__.

Дальше вы можете увидеть описание работы каждой из них.

### Фронтенд

Задача __фронтенда__ - построить __синтаксическое дерево__ и __таблицу имен__ на основе текста программы,
а также создать файлы с этими объектами.

Формат синтаксического дерева, файла с синтаксическим деревом и файла с таблицей имен
можно посмотреть [тут](https://github.com/Iprime111/LanguageStandart).

### Бэкенд

Задача __бэкенда__ - создать __объектный файл__ на основе синтаксического дерева и таблицы имен.

### Кодирование инструкций
Бэкенд кодирует инструкции для архитектуры __x86-64__.

Структуру инструкции можно описать следующей схемой:
```
Instruction:
    +-------------+--------------------+-------------+--------------------------+----------------+
    | REX prefix  | Instruction opcode |   Mod R/M   |    Immediate argument    |  Displacement  |
    +-------------+--------------------+-------------+--------------------------+----------------+
    |   1 byte    |    1 or 2 bytes    |   1 byte    |       1 - 8 bytes        |  1 or 4 bytes  |
    | (if needed) |                    | (if needed) |       (if needed)        |   (if needed)  |
    +-------------+--------------------+-------------+--------------------------+----------------+

REX prefix:
    +------------+---------------+--------------------+---------------+-------------------+
    | REX header |  Qword usage  | Register extension | Sib extension | Mod R/M extension |
    +------------+---------------+--------------------+---------------+-------------------+
    |   4 bits   |     1 bit     |       1 bit        |     1 bit     |       1 bit       |
    +------------+---------------+--------------------+---------------+-------------------+

Mod R/M:
    +--------+-----------------------------+-------------------------+
    |  Mode  | Register or extended opcode | Register/memory operand |
    +--------+-----------------------------+-------------------------+
    | 2 bits |           3 bits            |         3 bits          |
    +--------+-----------------------------+-------------------------+

```

Процесс кодирования инструкции вы можете увидеть в [этом файле](https://github.com/SANEKDASH/Binary-translator/blob/main/Backend/instruction_encoding.cpp#L136).

### Создание ELF файла
ELF файл создается в соответствии с System V ABI для архитектуры x86-64.

Он состоит из следующих секций:
1) section .text
Содержит байт-код программы.
2) section .shstrtab
Содержит таблицу с названиями секций.
3) section .symtab
Содержит таблицу с символами.
4) section .strtab
Содержит таблицу с именами символов.
5) section .rela.text
Содержит таблицу релокаций секции __.text__.

