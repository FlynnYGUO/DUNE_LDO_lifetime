# -*- coding: utf-8 -*-
"""
Created on Wed Jun 14 10:51:58 2023

@author: Eraguzin
"""
import time
class Keithley2470:
    def __init__(self, rm, json_data):
        self.rm = rm
        self.json_data = json_data
        self.keithley = self.rm.open_resource(self.json_data['keithley2470'])
        print(f"Keithley 2470 --> Connected to {self.keithley.query('*IDN?', delay=5)}")
        self.keithley.write("*RST")

    def initialize(self):
        self.voltage = self.json_data['keithley2470_voltage']

        #Set the instrument to source voltage as opposed to current
        self.keithley.write(":SOURce1:FUNCtion:MODE VOLTage")

        #Write the actual desired voltage
        self.keithley.write(f":SOURce1:VOLT:LEVel:IMMediate:AMPLitude {self.voltage}")
        print(f"Keithley 2470 --> Wrote voltage to {self.voltage}")

        #Turn on autorange
        self.keithley.write(":SOURce1:CURRent:RANGe:AUTO ON")
        #Always read back measured voltage, not the set voltage
        self.keithley.write(":SOURce1:VOLTage:READ:BACK ON")

        #Lock front screen and require password
        #self.keithley.write(":SYST:ACC LOCK")
        #self.keithley.write(f":SYST:PASS:NEW '{self.json_data['keithley_password']}'")

        #Set measurement time for best accuracy
        self.line_freq = self.keithley.query(":SYSTem:LFRequency?")
        self.keithley.write(f":SENSe1:VOLTage:NPLCycles {self.json_data['keithley2470_voltage_NPLcycles']}")
        self.keithley.write(f":SENSe1:CURRent:NPLCycles {self.json_data['keithley2470_current_NPLcycles']}")
        #Set Autozero on
        self.keithley.write(f":SENSe1:VOLTage:AZERo {self.json_data['keithley2470_autozero']}")

        #2 or 4 wire sensing
        self.keithley.write(f":SENSe1:CURRent:RSENse {self.json_data['keithley2470_4wire_measurement']}")
        self.keithley.write(f":SENSe1:VOLTage:RSENse {self.json_data['keithley2470_4wire_measurement']}")

        #Voltage source setting can't be limited by measurement limits
        self.keithley.write(f":SENSe1:VOLTage:RANGe:AUTO {self.json_data['keithley2470_voltage_autorange']}")
        #Something wrong with this function in the 2470
        #self.keithley.write(f":SENSe1:VOLTage:RANGe:AUTO:REBound {self.json_data['keithley2470_voltage_autorange_rebound']}")

        #Current measurements are auto
        self.keithley.write(f":SENSe1:CURRent:RANGe:AUTO {self.json_data['keithley2470_current_autorange']}")

        #Set current limit for voltage measurements
        self.keithley.write(f":SOUR:VOLT:ILIM {self.json_data['keithley2470_ilimit']}")

        #Should we have a voltage limit or current limit? On Source or Measurement side?
        #Number of digits in ASCII response
        self.keithley.write(f":FORMat:ASCii:PRECision {self.json_data['keithley2470_ascii_digits']}")

        #When off, be in the normal state
        self.keithley.write(":OUTPut1:VOLTage:SMODe NORM")
        self.keithley.write(":OUTPut1:STATe ON")

        #Display on front screen
        self.keithley.write(":DISPlay:CLEar")
        self.keithley.write(f":DISPlay:USER1:TEXT:DATA '{self.json_data['keithley2470_front_panel1']}'")
        self.keithley.write(f":DISPlay:USER2:TEXT:DATA '{self.json_data['keithley2470_front_panel2']}'")
        self.keithley.write(":DISPlay:SCReen SWIPE_USER")

        #Get the slow reads out of the way
        self.keithley.query(":MEASure:VOLTage?")
        self.keithley.query(":MEASure:CURRent?", delay=5)

    # Always stress after above initialization is done to keep all other settings unchanged
    def stress(self):
        self.stressvoltage = self.json_data['keithley2470_stress_voltage']

        # Need to set source voltage here?

        # Write the stress voltage
        self.keithley.write(f":SOURce1:VOLT:LEVel:IMMediate:AMPLitude {self.stressvoltage}")
        print(f"Keithley 2470 --> Wrote stress voltage to {self.stressvoltage}")

    def unstress(self):
        self.voltage = self.json_data['keithley2470_voltage']

        self.keithley.write(f":SOURce1:VOLT:LEVel:IMMediate:AMPLitude {self.voltage}")
        print(f"Keithley 2470 --> Wrote unstress voltage to {self.voltage}")

    def measure(self):
        #Make measurements, results come in like '7.999993E+00\n'
        #Remove newline at end
        try:
            voltage = self.keithley.query(":MEASure:VOLTage?").strip()
        except:
            print("Keithley 2470 --> Error polling voltage")
            voltage = -1
        try:
            current = self.keithley.query(":MEASure:CURRent?").strip()
        except:
            print("Keithley 2470 --> Error polling current")
            current = -1
        return float(voltage),float(current)
