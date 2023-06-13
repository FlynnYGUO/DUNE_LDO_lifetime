#!/usr/bin/env python3
#Script by Eric to test the instruments necessary for the DUNE FD2 LDO lifetime measurement

import sys, os, json, subprocess
import numpy as np
import matplotlib.pyplot as plt
from datetime import datetime, timedelta
import pyvisa

class LDOmeasure:
    def __init__(self, config_file):
        print("Python --> Welcome to the DUNE FD2 LDO Measurement Script")
        with open(config_file, "r") as jsonfile:
            self.json_data = json.load(jsonfile)

        print(self.json_data["example1"])

    def initialize_keithley_2460(self):
        print("Python --> Initializing Keithley 2460")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit(f"Error: You need to supply a config file for this test as the argument! You had {len(sys.argv)-1} arguments!")
    x = LDOmeasure(sys.argv[1])
    x.initialize_keithley_2460()
