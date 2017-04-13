import subprocess

TESTS = 1000
score = [0]*10 

#Customize the test so that you can test individual digits
print("Enter the test_digits you want to test (eg. '0 1 5 6 8')")
test_digits = input().strip().split()
test_digits = [int(i) for i in test_digits]
print("Running tests with ", end="")
print(test_digits)

#Tests everything inside ../digits/
for x in range(TESTS):

    #produces a $filename that matches the names of the pbm files
    filenumber = str(x) 
    number = x%100
    digit = int(x/100)
    filename = str("../digit/"+str(digit)+"_"+str(number)+".pbm")

    #Only runs the test if we specified it earlier
    if(digit in test_digits):
        run = subprocess.run(["../a.out", filename], stdout=subprocess.PIPE)
        output = run.stdout.strip()
        output = output.decode('ascii')
