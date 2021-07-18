#!/bin/bash

set -euo pipefail

gcc donut.c logging.c -o donut -lm 

DONUT_STEP_LOG_FILE=test/data/steps-tmp.txt
GOLDEN_FILE=test/data/steps-golden.txt
rm -f $DONUT_STEP_LOG_FILE

DONUT_STEP_LOG_FILE=$DONUT_STEP_LOG_FILE ./donut > /dev/null &

sleep 1
PID="$!"
kill $PID

echo "Comparing results..."

diff $GOLDEN_FILE $DONUT_STEP_LOG_FILE

echo "Success!"
