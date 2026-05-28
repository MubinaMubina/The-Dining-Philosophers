*This project has been created as part of the 42 curriculum by mmubina.*

# Philosophers

## Description

A C implementation of the classic **dining philosophers** concurrency problem,
solved with POSIX threads and mutexes.

N philosophers sit around a round table. Between every pair of neighbors lies a
single fork, so there are N forks total. Each philosopher repeatedly thinks,
picks up the two forks adjacent to them, eats for a fixed time, then puts both
forks down and sleeps. A philosopher who has not started a meal within
`time_to_die` milliseconds since their last meal dies, and the simulation ends.

The goal of the project is to learn:

- How to create and join POSIX threads (`pthread_create`, `pthread_join`).
- How to protect shared state with mutexes to avoid data races.
- How to design lock acquisition to avoid deadlock and starvation.
- How to measure time and sleep precisely enough to meet a 10 ms deadline.

## Instructions

### Build

```sh
cd philo
make
```

The Makefile compiles with `cc -Wall -Wextra -Werror -pthread` and produces a
`philo` binary in the same directory.

Other Makefile targets:

| Target  | Effect                                       |
| ------- | -------------------------------------------- |
| `all`   | Default target. Builds `philo`.              |
| `clean` | Removes object files.                        |
| `fclean`| Removes object files and the `philo` binary. |
| `re`    | `fclean` followed by `all`.                  |

### Run

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep \
        [number_of_times_each_philosopher_must_eat]
```

All time values are in milliseconds. The last argument is optional: if given,
the simulation stops once every philosopher has eaten that many times; if
omitted, the simulation runs until a philosopher dies.

### Usage examples

```sh
# 5 philosophers; nobody should die under these timings
./philo 5 800 200 200

# 5 philosophers; stop after each has eaten 7 times
./philo 5 800 200 200 7

# 4 philosophers; tight timing - a philosopher dies eventually
./philo 4 410 200 200

# 1 philosopher; only 1 fork exists, so they must die
./philo 1 800 200 200
```

### Log format

Each state change prints a line in the form:

```
<timestamp_in_ms> <philosopher_id> <event>
```

Where `<event>` is one of: `has taken a fork`, `is eating`, `is sleeping`,
`is thinking`, `died`. Timestamps are milliseconds since simulation start.

## Technical choices

- **One thread per philosopher.** Each philosopher runs the same routine,
  cycling through take-forks → eat → drop-forks → sleep → think.
- **One mutex per fork.** Acquired in a deterministic order (odd philosophers
  pick up the right fork first, even philosophers pick up the left fork first)
  to break the circular-wait condition and prevent deadlock.
- **Separate monitor thread.** Polls each philosopher's last-meal timestamp and
  meal counter, sets a shared stop flag when someone dies or when everyone has
  eaten enough.
- **Per-philosopher meal mutex** protecting `last_meal_time` and `meals_eaten`,
  so the monitor never races the philosopher updating its own counters.
- **Dedicated print mutex** wrapping `printf` so log lines never overlap, and
  so no state message can be printed after a `died` message.
- **Precise sleep loop.** `usleep` alone is too imprecise, so sleeping is
  implemented as a loop of short `usleep` calls that also re-checks the stop
  flag, allowing threads to exit promptly when the simulation ends.

## Resources

Classic references on the problem itself:

- E. W. Dijkstra, *Hierarchical Ordering of Sequential Processes* (1971) —
  the original formulation of the dining philosophers problem.
- *The Little Book of Semaphores* by Allen B. Downey — Chapter 5 covers the
  philosophers problem with multiple solution patterns.
- `pthread` man pages: `pthread_create(3)`, `pthread_join(3)`,
  `pthread_mutex_init(3)`, `pthread_mutex_lock(3)`, `gettimeofday(2)`,
  `usleep(3)`.

### AI usage

AI (Anthropic Claude, via Claude Code) was used as a learning and scaffolding
aid in the following ways:

- **Conceptual explanation:** Walking through the problem statement, the
  shared-state model, deadlock conditions (Coffman's four), and lock-ordering
  strategies before any code was written.
- **Project scaffolding:** Generating the initial file layout, the Makefile,
  the header with struct definitions, and stub `.c` files containing only
  function signatures and comments describing what each function must
  implement. The scaffold compiles but does nothing — the implementation of
  every function is written by hand.

AI was **not** used to generate the implementation of any function. The
algorithmic logic (thread routine, monitor, fork acquisition, timing,
cleanup) is written and owned by the author.
