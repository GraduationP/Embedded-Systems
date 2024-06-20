import subprocess

with open('blink.txt', 'r') as file:
    with open('processd_image.txt', 'w') as output_file:  
        line = file.readline()    
        while line:        
            if len(line) >= 15 and line[1] == '3':                               
                output_file.write(line[12:-3] )  
            line = file.readline()

# subprocess.run(["./can_bootloader"], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
