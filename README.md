## Push-Swap
### Задача
([здесь](https://github.com/gerus66/push-swap/blob/master/readme/push_swap.en.pdf) подробнее)

Даны два стека, которые умеют выполнять операции:

`sa` `sb` `ss` __swap__ the first 2 elements at the top of stack _A/B/both_

`pa` `pb` take the first element at the top of _B/A_ and __push__ it at the top of _A/B_

`ra` `rb` `rr` __rotate__ all elements of stack _A/B/both_ , the first element becomes the last one.

`rra` `rrb` `rrr` __reverse rotate__ all elements of stack _A/B/both_, the last element becomes the first one.

В стеке _A_ лежит массив целых неповторяющихся чисел.

Необходимо отсортировать по возрастанию данный массив за минимальное количество операций (отсортированный массив
тоже должен лежать в стеке _A_).

### Run
_macos_: `make & ARG=$(python3 gen.py N); ./push_swap $ARG | ./checker [-g | -v | -c] $ARG`

или (например, если есть проблемы с _miniLibX_)

`make no-graph & ARG=$(python3 gen.py N); ./push_swap $ARG | ./checker [-v | -c] $ARG`

_linux_: в процессе тестирования

### Утилиты
 `gen.py N` генерирует массив из _N_ случайных неповторяющихся чисел в диапазоне _[-N, N]_

`./push_swap A` генерирует последовательность операций стека для сортировки массива _A_

`./checker A` принимает из командной строки операции стека и выполняет их на массиве _A_. При выходе из программы
в консоль печатается `OK` или `Error` - результат последней проверки массива на отсортированность. Доступны опции:
* `-g` графическая визуализация сортировки в отдельном окне (недоступна при компиляции `make no-graph`)
* `-v` распечатка стеков в консоль
* `-v -c` распечатка стеков в консоль + подсветка последнего действия

В графическом окне доступно управление - 
* `space` остановка
* `left` `right` замедление / ускорение визуализации
* `esc` выход

### Визуализация ./checker -g 
![Alt text](https://github.com/gerus66/push-swap/blob/master/readme/push_swap_vis.png)
### Визуализация ./checker -v -c 
![Alt text](https://github.com/gerus66/push-swap/blob/master/readme/push_swap_vc.png)

### Codestyle
Проект написан в строгом соответствии с [Norminette codestyle](https://github.com/gerus66/norme)
