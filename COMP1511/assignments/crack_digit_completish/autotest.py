import subprocess

TESTS = 1000
score = [0]*10 
tests = [0]*10
failed = []
attribute = [[0]*100 for _ in range(10)]

#Customize the test so that you can test individual digits 
print("Enter the test_digits you want to test (eg. '0 1 5 6 8')") 
test_digits = input().strip().split()
test_digits = [int(i) for i in test_digits]
print("Running tests with ", end="")
print(test_digits)

#Tests everything inside ../digits/
for x in range(TESTS):

    #produces a $filename that matches the names of the pbm files
    number = x%100
    digit = int(x/100)
    if number < 10:
        filename = str("./digit/"+str(digit)+"_0"+str(number)+".pbm")
    else:
        filename = str("./digit/"+str(digit)+"_"+str(number)+".pbm")

    #Only runs the test if we specified it earlier
    if(digit in test_digits):
        run = subprocess.run(["./a.out", filename], stdout=subprocess.PIPE, stderr=subprocess.PIPE)

        #get the output of the program and determine if it is valid or an error
        output = run.stdout.strip()
        output = output.decode('ascii')
        error = run.stderr.strip()
        error = error.decode('ascii')
        print(filename,output)
        attribute[digit][number] = float(output)
        if(error == ''):
            #if it is a valid guess, record if it is correct or not
            tests[digit] += 1
            if(output == str(digit)):
                score[digit] += 1
            else:
                failed.append(filename)

print("Would you like to see (a)nalysis or (s)cores? (a/s)")
mode = input().strip()
if(mode == 'a'):
    digit = 0
    for x in attribute:
        avg = sum(x)/len(x)
        highest = max(x)
        lowest = min(x)
        print(str("Digit("+str(digit)+"): attribute avg = "+str(avg)+" highest = "+str(highest)+" lowest = "+str(lowest)))
        digit += 1
elif(mode == 's'):
#print the scores for each digit
    print("Here are your scores")
    for x in range(10):
        if(x in test_digits):
            percent = score[x]*100/tests[x]
            print("%d: %d/%d for a score of %.2lf" % (x, score[x], tests[x], percent) + "%")

    print("Would you like to see the images you failed? (y/n)")
    confirm = input().strip()
    if(confirm == "y"):
        for x in failed:
            print(x)
            check = subprocess.run(["./print", x])
            #print useful attributes of the digit in question
