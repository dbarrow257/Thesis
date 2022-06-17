import os

Total = 0

Files = os.listdir(os.getcwd())
for File in Files:
    if (File[-4:] == ".tex" and File[0:4] == "Chap"):
        CommandInText = "texcount "+File+" | grep \"Words in text\""
        ResultInText = os.popen(CommandInText).read()
        WordsInText = ((ResultInText.split(":"))[1]).rstrip()

        CommandInCaps = "texcount "+File+" | grep \"Words outside text (captions, etc.)\""
        ResultInCaps = os.popen(CommandInCaps).read()
        WordsInCaps = ((ResultInCaps.split(":"))[1]).rstrip()

        String = File+"\t\t"
        if (len(File)<16):
            String += "\t"
        if (len(File)<24):
            String += "\t"
        String += str(int(WordsInText)+int(WordsInCaps))

        Total += int(WordsInText)+int(WordsInCaps)
        
        print(String)


print("-------------")
print("Total:"+str(Total))
