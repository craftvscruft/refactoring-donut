
Credit to Andy Sloane.

https://www.a1k0n.net/2006/09/15/obfuscated-c-donut.html

## Build

```
gcc donut.c logging.c -o donut -lm && ./donut
```

## Test

```
DONUT_STEP_LOG_FILE=test/data/steps-tmp.txt ./donut

# Control C out of this

diff test/data/steps-golden.txt test/data/steps-tmp.txt
```
