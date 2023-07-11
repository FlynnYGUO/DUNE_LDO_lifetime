#!/usr/bin/env python3
#Script by Eric to test the instruments necessary for the DUNE FD2 LDO lifetime measurement

import sys, os, json, subprocess, csv
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from datetime import datetime, timedelta
import pyvisa
from keithley_2460 import Keithley2460
from keithley_2470 import Keithley2470
from agilent_34970a import Agilent34970A

class LDOmeasure:
    def __init__(self, config_file, name):
        print("Main --> Welcome to the DUNE FD2 LDO Measurement Script")
        with open(config_file, "r") as jsonfile:
            self.json_data = json.load(jsonfile)
        self.rm = pyvisa.ResourceManager()
        self.name = name
        self.begin_measurement()

    def initialize_keithley_2460(self):
        print("Main --> Initializing Keithley 2460")
        self.keithley2460 = Keithley2460(self.rm, self.json_data)
        self.keithley2460.initialize()

    def initialize_keithley_2470(self):
        print("Main --> Initializing Keithley 2470")
        self.keithley2470 = Keithley2470(self.rm, self.json_data)
        self.keithley2470.initialize()

    def initialize_agilent_34970(self):
        print("Main --> Initializing Agilent 34970A")
        self.agilent = Agilent34970A(self.rm, self.json_data)
        self.agilent.initialize()

    def measure_keithley_2460(self):
        v,c = self.keithley2460.measure()
        print(v)
        print(c)

    def measure_keithley_2470(self):
        v,c = self.keithley2470.measure()
        print(v)
        print(c)

    def measure_agilent_2460(self):
        voltages = self.agilent.measure()
        print(voltages)

    def stress_keithley_2470(self):
        print("Main --> Set Keithley 2470 for stress test")
        self.keithley2470.stress()

    def unstress_keithley_2470(self):
        print("Main --> Set Keithley 2470 for unstress test")
        self.keithley2470.unstress()

    def begin_measurement(self):
        header_array = ["Time"]
        data_array = ["{time}"]
        if (int(self.json_data['test_lp'])):
            self.initialize_keithley_2470()
            header_array.extend(["keithley2470_voltage", "keithley2470_current"])
            data_array.extend(["{k2470_v}", "{k2470_c}"])

        if (int(self.json_data['test_adm'])):
            self.initialize_keithley_2460()
            header_array.extend(["keithley2460_voltage", "keithley2460_current"])
            data_array.extend(["{k2460_v}", "{k2460_c}"])

        self.initialize_agilent_34970()
        header_array.extend(["agilent_vout_lp", "agilent_vout_adm", "agilent_ref_adm", "agilent_byp_adm", "agilent_vreg_adm"])
        data_array.extend(["{voltages[0]}", "{voltages[1]}", "{voltages[2]}", "{voltages[3]}", "{voltages[4]}"])

        print("Main --> Instruments Initialized")

        curr_file = os.path.dirname(os.path.abspath(__file__))
        # New dir automatically created to save data and plots
        data_path = os.path.join(curr_file, "..\\DATA\\" + self.name, "")
        if not os.path.exists(data_path):
            os.makedirs(data_path)
        output_path = os.path.join(data_path, self.name + ".csv")

        self.seconds = int(self.json_data['measurement_period'])
        time = datetime.now()
        next_time = time
        tot_stress_time = int(self.json_data['stress_test_period'])
        tot_unstress_time = int(self.json_data['unstress_test_period'])
        stress_cycle = 0
        unstress_cycle = 0
        isstress = False

        with open(output_path, 'a', newline='') as csvfile:
            spamwriter = csv.writer(csvfile, delimiter=',', quoting=csv.QUOTE_MINIMAL)
            spamwriter.writerow(header_array)

        print("Main --> Test beginning. Press Ctrl+C on the keyboard to end")
        # Ctrl+C is the only way to stop this while loop measurement
        while True:
            try:
                time = datetime.now()
                # Start stress test if an unstress test period is over
                if ( int(self.json_data['stress_test_period']) > 0 && tot_unstress_time >= int(self.json_data['unstress_test_period']) ):
                    if (int(self.json_data['test_lp'])):  self.stress_keithley_2470()
                    if (int(self.json_data['test_adm'])): self.stress_keithley_2460()
                    # reset counter
                    tot_stress_time = 0
                    tot_unstress_time = 0
                    stress_cycle = stress_cycle + 1
                    isstress = True

                # Start unstress test if a stress test period is over
                if ( int(self.json_data['unstress_test_period']) > 0 && tot_stress_time >= int(self.json_data['stress_test_period']) ):
                    if (int(self.json_data['test_lp'])):  self.unstress_keithley_2470()
                    if (int(self.json_data['test_adm'])): self.unstress_keithley_2460()
                    # reset counter
                    tot_unstress_time = 0
                    tot_stress_time = 0
                    unstress_cycle = unstress_cycle + 1
                    isstress = False

                if (time > next_time):
                    if (int(self.json_data['test_adm'])):
                        k2460_v,k2460_c = self.keithley2460.measure()
                        print(f"Keithley 2460 voltage is {k2460_v}, Keithley current is {k2460_c}")
                    if (int(self.json_data['test_lp'])):
                        k2470_v,k2470_c = self.keithley2470.measure()
                        print(f"Keithley 2470 voltage is {k2470_v}, Keithley current is {k2470_c}")
                    voltages = self.agilent.measure()
                    print(f"Agilent voltages are {voltages}")
                    print("Tot stress cycles: ", stress_cycle, ", unstress cycles: ", unstress_cycle, ", current cycle is stress: ", isstress)
                    with open(output_path, 'a', newline='') as csvfile:
                        spamwriter = csv.writer(csvfile, delimiter=',', quoting=csv.QUOTE_MINIMAL)
                        data_row = []
                        for i in data_array:
                            x = (eval(f"f'{i}'"))
                            data_row.append(x)
                        spamwriter.writerow(data_row)

                    next_time = time + timedelta(seconds=self.seconds)
                    self.analyze_data(output_path)

                if (isstress): tot_stress_time = tot_stress_time + (datetime.now() - time).total_seconds()
                else: tot_unstress_time = tot_unstress_time + (datetime.now() - time).total_seconds()
            except KeyboardInterrupt:
                print("Keyboard interrupt to finish test")
                break

    def analyze_data(self, output_path):
        df = pd.read_csv(output_path)
        #saved_column = df.column_name #you can also use df['column_name']
        name_list = []
        data_list = []
        time_column = []
        for num,(columnName, columnData) in enumerate(df.iteritems()):
            if (num == 0):
                for i in columnData.values:
                    time_column.append(datetime.strptime(i, '%Y-%m-%d %H:%M:%S.%f'))
            else:
                name_list.append(columnName)
                data_list.append([float(i) for i in columnData])

        for num,i in enumerate(name_list):
            self.plot(time_column, i, data_list[num])

    def plot(self, time, name, data):
        fig = plt.figure(figsize=(16, 12), dpi=80)
        ax = fig.add_subplot(1,1,1)
        ax.tick_params(axis='x', colors='black',labelsize='medium')
        ax.tick_params(axis='y', colors='black',labelsize='medium')
        fig.suptitle(f"{name}", fontsize = 36)

        ax.set_xlabel("Time (Hours:Minutes)", fontsize = 24)
        ax.set_ylabel("Value", fontsize = 24)
        ax.plot(time, data)
        fig.savefig(f'plot_{name}.png')
        plt.close(fig)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit(f"Main Error: You need to supply a config file for this test as the argument! You had {len(sys.argv)-1} arguments!")
    name = input("Input the name of this test\n")
    x = LDOmeasure(sys.argv[1], name)
