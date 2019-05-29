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

### Утилиты
 `gen.py N` генерирует массив из N случайных неповторяющихся чисел в диапазоне [-N, N]

`./push_swap [array]` генерирует последовательность операций стека для сортировки массива

`./checker [array]` принимает из командной строки операции стека и выполняет их. Доступны опции:
* `-g` графическая визуализация сортировки в отдельном окне
* `-v` распечатка стеков в консоль
* `-v -c` распечатка стеков в консоль + подсветка последнего действия

В графическом окне доступно управление - 
* `space` остановка
* `<>` замедление / ускорение визуализации
* `esc` выход

### Запустить
`make`
  
`ARG=$(python3 gen.py 100); ./push_swap $ARG | ./checker -g $ARG`

### Визуализация
![Alt text](https://github.com/gerus66/push-swap/blob/master/readme/push_swap_vis.png)
![Alt text](https://github.com/gerus66/push-swap/blob/master/readme/push_swap_vc.png)

### Codestyle
Проект написан в строгом соответствии с [Norminette codestyle](https://github.com/gerus66/norme)
