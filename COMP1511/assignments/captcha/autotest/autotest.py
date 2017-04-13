import subprocess

TESTS = 1000

for x in range(TESTS):
    filenumber = str(x) 
    number = x%100
    digit = int(x/100)
    subprocess.run(["../a.out", "../digit/"+str(digit)+"_"+str(number)+".pbm"])
