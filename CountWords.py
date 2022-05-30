import os

Total = 0

Files = os.listdir(os.getcwd())
for File in Files:
    if (File[-4:] == ".tex" and File[0:4] == "Chap"):
        Command = "texcount "+File+" | grep \"Words in text\""
        Result = os.popen(Command).read()
        Words = ((Result.split(":"))[1]).rstrip()

        String = File+"\t\t"
        if (len(File)<16):
            String += "\t"
        String += Words

        Total += int(Words)
        
        print(String)


print("-------------")
print("Total:"+str(Total))
