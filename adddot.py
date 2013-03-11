f=open("sets.txt", "r")
g=open("set.txt", "w")

while(1):
	a=f.readline().split()
	if not a:
		break
	for i in range(len(a)):
		if a[i].isupper():print "chut"
		else: a[i] = a[i].lower()
	a = " ".join(a)
	a += "\n"
	g.write(a)
