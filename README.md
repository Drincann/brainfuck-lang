# brainfuck

## c

### interpreter

build:

```shell
gcc -o bf interpreter.c
```

run the example:

```shell
bf src.bf
# > Hello world!
```

### compiler

build:

```shell
gcc -o bfc compiler.c
```

run the example:

```shell
bfc src.bf
./out
# > Hello world!
```
