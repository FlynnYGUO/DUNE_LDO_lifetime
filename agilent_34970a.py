# -*- coding: utf-8 -*-
"""
Created on Wed Jun 14 15:29:17 2023

@author: Eraguzin
"""

class Agilent34970A:
    def __init__(self, rm, json_data):
        self.rm = rm
        self.json_data = json_data
        self.agilent = self.rm.open_resource(self.json_data['agilent'])
        print(f"Agilent 34970A --> Connected to {self.agilent.query('*IDN?')}")
        self.agilent.write("*RST")
        
    def initialize(self):
        print("Initializing Agilent")