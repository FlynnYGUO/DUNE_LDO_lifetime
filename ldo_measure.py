#!/usr/bin/env python3
#Script by Eric to test the instruments necessary for the DUNE FD2 LDO lifetime measurement

import sys, os, json, subprocess
import numpy as np
import matplotlib.pyplot as plt
from datetime import datetime, timedelta
import pyvisa
from keithley_2460 import Keithley2460
from agilent_34970a import Agilent34970A

class LDOmeasure:
    def __init__(self, config_file):
        print("Main --> Welcome to the DUNE FD2 LDO Measurement Script")
        with open(config_file, "r") as jsonfile:
            self.json_data = json.load(jsonfile)
        self.rm = pyvisa.ResourceManager()

    def initialize_keithley_2460(self):
        print("Main --> Initializing Keithley 2460")
        self.keithley = Keithley2460(self.rm, self.json_data)
        self.keithley.initialize()
        
    def initialize_agilent_34970(self):
        print("Main --> Initializing Agilent 34970A")
        self.agilent = Agilent34970A(self.rm, self.json_data)
        self.agilent.initialize()
        
    def measure_keithley_2460(self):
        v,c = self.keithley.measure()
        print(v)
        print(c)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit(f"Main Error: You need to supply a config file for this test as the argument! You had {len(sys.argv)-1} arguments!")
    x = LDOmeasure(sys.argv[1])
    #x.initialize_keithley_2460()
    #x.measure_keithley_2460()
    
    x.initialize_agilent_34970()