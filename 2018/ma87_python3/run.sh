#!/bin/bash

set -e

DAY=$1

python3 src/adc_$DAY.py src/adc_$DAY.txt
