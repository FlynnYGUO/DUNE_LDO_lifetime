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
        print(f"Agilent 34970A --> Connected to {self.agilent.query('*IDN?', delay=1)}")
        self.agilent.write("*RST")
        #time.sleep(1)
        #Unit self test
        #print("Agilent 34970A --> Performing self test")
        # self_test = self.agilent.query("*TST?", delay=15).strip()
        # if (self_test == "+0"):
        #     print("Agilent 34970A --> Self test passed!")
        # else:
        #     import sys
        #     sys.exit("Agilent 34970A --> Self test failed!")
    def initialize(self):
        self.slot = self.json_data['agilent_slot']
        
        #Build the string for the scanning list
        self.vout_lp = int(self.slot) + int(self.json_data['agilent_vout_lp'])
        self.vout_adm = int(self.slot) + int(self.json_data['agilent_vout_adm'])
        self.vout_ref_adm = int(self.slot) + int(self.json_data['agilent_ref_adm'])
        self.vout_byp_adm = int(self.slot) + int(self.json_data['agilent_byp_adm'])
        self.vout_vreg_adm = int(self.slot) + int(self.json_data['agilent_vreg_adm'])
        self.channel_list = f"(@{self.vout_lp},{self.vout_adm},{self.vout_ref_adm},{self.vout_byp_adm},{self.vout_vreg_adm})"
        
        #Get ID of multiplexer unit in slot 1
        self.slot_name = self.agilent.query(f":SYSTem:CTYPe? {self.slot}")
        #print(f":ROUTe:SCAN {self.channel_list}")
        #Set these channels up to measure DC volts with autorange and maximum resolution
        self.agilent.write(f"CONFigure:VOLTage:DC {self.json_data['agilent_autorange']},{self.json_data['agilent_resolution']},{self.channel_list}")
        self.line_freq = self.agilent.query(":SYSTem:LFRequency?")
        #Set the integration time for the ADC
        self.agilent.write(f"SENSe:VOLTage:DC:NPLC {self.json_data['agilent_NPLcycles']}")
        #Creates the scan list, redundant
        self.agilent.write(f":ROUTe:SCAN {self.channel_list}")
        
        #4 wire is only available with an external DMM
        
        #Set front panel
        self.agilent.write(f"DISPlay:TEXT '{self.json_data['agilent_front_panel']}'")
        
        #Can't lockout front panel on the 34970A
        
        
    def measure(self):
        voltage_array = self.agilent.query("READ?").strip()
        voltages = [float(v) for v in voltage_array.split(",")]
        return voltages