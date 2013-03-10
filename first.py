f = open("RULES.txt","r")
f1 = open("grammar2.txt","w")
while(1):
    l = f.readline()
    if not l:break
    l=l.split()
    
    l1 = ""
    l1+=l[0].upper()
    l1+=" "
    l1+="-> "
    for i in range(1,len(l)):
        if l[i].isupper():
            l1+=l[i].lower()
        elif l[i] == "eps":
            print ""
        else:
             l1+=l[i].upper()
        l1+=" "
    l1+=" .\n"
    print l1
    f1.write(l1)

