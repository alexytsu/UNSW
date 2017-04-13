import subprocess

TESTS = 1000

score = [0]*10 

for x in range(TESTS):
    filenumber = str(x) 
    number = x%100
    digit = int(x/100)
    
    if(digit == 3 and number == 0):
        print("Tests for digit 3")
    if(digit == 3): 
        filename = str("../digit/"+str(digit)+"_"+str(number)+".pbm")
        run = subprocess.run(["../a.out", filename], stdout=subprocess.PIPE)
        output = run.stdout.strip()
        output = output.decode('ascii')
        if(output == "3"):
            score[3] += 1

    if(digit ==4):
        filename = str("../digit/"+str(digit)+"_"+str(number)+".pbm")
        run = subprocess.run(["../a.out", filename], stdout=subprocess.PIPE)
        output = run.stdout.strip()
        output = output.decode('ascii')
        if(output == "4"):
            score[4] += 1

    if(digit == 6):
        filename = str("../digit/"+str(digit)+"_"+str(number)+".pbm")
        run = subprocess.run(["../a.out", filename], stdout=subprocess.PIPE)
        output = run.stdout.strip()
        output = output.decode('ascii')
        if(output == "6"):
            score[6] += 1


print(str(score[3]))
print(str(score[4]))
print(str(score[6]))
