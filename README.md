## Push-Swap
### Task 
_[full version in pdf](https://github.com/gerus66/push-swap/blob/master/readme/push_swap.en.pdf)_ \
There are two _'stacks'_ (not in the general meaning of this terms) - `A` is filled with unique numbers and `B` is empty. \
Given a list of permitted instructions, `A` should be sorted in ascending order with the _minimum_ number of instructions possible. 

Full list of instructions to manipulate with _'stacks'_: \
`sa` `sb` `ss` - __swap__ the first 2 elements at the top of `A` / `B` / both at once \
`pa` `pb` - take the first element at the top of `B` (or `A`) and __push__ it to the top of `A` (or `B`) \
`ra` `rb` `rr` __rotate__ all elements of `A` / `B` / both at once , the first element becomes the last one \
`rra` `rrb` `rrr` __reverse rotate__ all elements of `A` / `B` / both at once, the last element becomes the first one

### Run
_macos:_ \
`make & ARG=$(python3 gen.py N); ./push_swap $ARG | ./checker [-g|-v|-c] $ARG`

in case of problems with the _miniLibX_ graphic library, binary could be compiled without it: \
`make no-graph & ARG=$(python3 gen.py N); ./push_swap $ARG | ./checker [-v|-c] $ARG`

_linux: in progress_

### Utils
 `gen.py N` returns array of _N_ uniqie numbers in range _[-N, N]_

`push_swap A` returns sequence of instructions sorting the given array _A_

`checker [-g|-v|-c] A` reads instructions from the standart input (one at a time) and consequentially applies them to _A_. \
&nbsp;&nbsp; `-v` print `A` and `B` to the standart output \
&nbsp;&nbsp; `-c` last move is highlighted (use it with `-v`) \
&nbsp;&nbsp; `-g` graphic mode with animation (doesn't work with `make no-graph` compilation) \
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; control keys: `left`/`right` for speed control, `space` for pause, `esc`.

### ./checker -g 
![Alt text](https://github.com/gerus66/push-swap/blob/master/readme/push_swap_vis.png)
### ./checker -v -c 
![Alt text](https://github.com/gerus66/push-swap/blob/master/readme/push_swap_vc.png)

### Codestyle
Project was developed in strict accordance with [Norminette codestyle](https://github.com/gerus66/norme)
