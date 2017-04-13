import subprocess
for x in range(1000):
    filenumber = str(x) 
    number = x%100
    digit = int(x/100)
    subprocess.call(["../a.out", "../digit/"+str(digit)+"_"+str(number)+".pbm"])
