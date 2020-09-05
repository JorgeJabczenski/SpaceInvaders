#!/bin/bash

delay=$(xset q | grep "auto repeat delay" | cut -d':' -f2 | cut -d' ' -f3)
rate=$(xset q | grep "auto repeat delay" | cut -d':' -f3 | cut -d' ' -f3)

xset r rate 120 20

./space

xset r rate $delay $rate

