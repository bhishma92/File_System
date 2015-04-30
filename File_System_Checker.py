import math
import time

#Question1

# The following code checks if the device id is correct

myfile = open ("C:\\Users\\Admin\\Desktop\\FS\\fusedata.0"  , "r")
a=myfile.read()

check_devId = "devId:20"
if check_devId in open("C:\\Users\\Admin\\Desktop\\FS\\fusedata.0").read():
    print "devId checked"
    
else:
    print "Not your filesystem"
    
myfile.close()

print ""

# Question2

# The following code checks the atime, ctime and mtime of the directories or files

for i in range(26,31): #range of directories or files
    f = open("C:\\Users\\Admin\\Desktop\\FS\\fusedata.%d" %i , "r")
    l = f.read()

    current_time = time.time()
    str_cur = str(current_time)
    
    s1=l.find("atime:")
    if s1 != -1:
        s2=l.find("ctime:")
        if s2 != -1:
            s3=l.find("mtime:")
            if s3 != -1:
                s4=l.find("linkcount:")
                if s4 != -1:
                    t1= l.index('atime:') 
                    t2= l.index('ctime:') 
                    t3= l.index('mtime:')
                    t4= l.index('linkcount:')
                    r1=t1+6
                    r2=t2-2
                    str1 = l[r1:r2]
                    r3=t2+6
                    r4=t3-2
                    str2 = l[r3:r4]
                    #print str2
                    r5=t3+6
                    r6=t4-2
                    str3 = l[r5:r6]

                # Comparing with the current time and updating if required
                
                    if str1 > str_cur:
                        print 'Error Found in atime'
                        w=l.replace(str1,str_cur)
                        f = open ("C:\\Users\\Admin\\Desktop\\FS\\fusedata.%d" %i  , "w")
                        f.write(w)
                        print 'Error Resolved'
                    else:
                        print 'atime is right for directory %d' %i

                    if str2 > str_cur:
                        print 'Error Found in ctime'
                        w1=l.replace(str2,str_cur)
                        f = open ("C:\\Users\\Admin\\Desktop\\FS\\fusedata.%d" %i  , "w")
                        f.write(w1)
                        print 'Error Resolved'
                    else:
                        print 'ctime is right for directory %d' %i

                    if str3 > str_cur:
                        print 'Error Found in mtime'
                        w2=l.replace(str3,str_cur)
                        f = open ("C:\\Users\\Admin\\Desktop\\FS\\fusedata.%d" %i  , "w")
                        f.write(w2)
                        print 'Error Resolved'
                    else:
                        print 'mtime is right for directory %d' %i

                    f.close()

print ""

# Question 4

# The following code checks if directory contains . and .., and checks if the values are correct

for j in range(26,31): # go through freeblocks 
    print "%d" %j
    fi = open("C:\\Users\\Admin\\Desktop\\FS\\fusedata.%d" %j , "r+")
    l = fi.read()
    var=l.find("filename_to_inode_dict:")
    fi.close()
    
    if var != -1:
        le = len(l)-2
        l1=l.index('filename_to_inode_dict:')
        m1=l1+25
        str1= l[m1:le] 
        


        n = str1.index(":.:")
        n1 = n+3
        n2 = n1+2
        str4 = "%d" %j      


        i1= str1.index("..")   
        i2 = i1+3
        i3 = i2+2
        str2 = str1[i2:i3]

        if (str2== "26"):
             print "No error in dot dot"
        else:
            str3 = "26"
            
            fi = open ("C:\\Users\\Admin\\Desktop\\FS\\fusedata.%d" %j  , "w")
            d =l.replace(str2, str3)
            fi.write(d)
            print 'Error Resolved'

        fi.close()

print "dot dot checking over"
print ""

#Question 3 and 5

# The follwing code creates the directory and file lists, Traverse through them to  update the freeblock list.

# Also it checks and corrects the linkcount according to the number of links in file_to_inode_dict: 

def make_dirlist(x, filelist, dirlist):
    q=int(x)
    
    fi = open("C:\\Users\\Admin\\Desktop\\FS\\fusedata.%d" %q , "r+")

    
    lz = fi.read()
    le = len(lz)-2
    l1=lz.index('filename_to_inode_dict:')
    m1=l1+25
    str1= lz[m1:le] 

    #Question 5
    
    count=0
    for i in str1:
        if i==",":
            count= count+1  #to count linkcounts

    


    count=count+1
    rep="%d" %count
    lc=lz.find("linkcount:")
    lci=lz.index('linkcount:')
    lci=lci+10
    if lc != -1:
        if lz[lci] != rep:              
            lz1=lz.replace(lz[lci], rep)
            fw = open("C:\\Users\\Admin\\Desktop\\FS\\fusedata.%d" %q , "w")
            fw.write(lz1)
            fw.close()
            print "linkcount corrected"
            
        else:
            print "linkcount ok"
            
    print ""   

#Question 5 ends
    
    k=0
    l=0
    cnt=0    
    sm=str1;

    for i in str1:
        
        cnt=cnt+1
        if i==",":
            a= str1[0:cnt-1]
            b=a.split(':')
            if b[0]=='f':
                filelist.insert(k, b[2])
                k=k+1
                
            else:  #b[0]==d:
                if l>1:
                    dirlist.insert(l-1, b[2])
                    if dirlist[l-1]!=26:
                        make_dirlist(dirlist[l-1], filelist, dirlist)
                else:
                    l=l+1
            
            str1=str1.strip(a)
            str1=str1.strip(' ,')                                   
            cnt=-1
            
        elif sm.index(i)==len(sm)-1:
            a= str1[0:cnt]
            b=a.split(':')
            
            if b[0]=='f':
                filelist.insert(k, b[2])
                k=k+1
            else:  #b[0]==d:
                if l>1:
                    dirlist.insert(l-1, b[2])
                    if dirlist[l-1]!=26:
                        make_dirlist(dirlist[l-1], filelist, dirlist)
                else:
                    l=l+1 
            str1=str1.strip(a)
            str1=str1.strip(' ,')
            cnt=-1
    


filelist=["0"]*5
dirlist=['26',0,0,0,0]
x=dirlist[0]
make_dirlist(x, filelist, dirlist)


# Updates free block list

for i in filelist:
    i1=int(i)
    if i1 !=0:
        fn=math.floor((i1/400)+1)
        fn1=int(fn)
        fs = open("C:\\Users\\Admin\\Desktop\\FS\\fusedata.%d" %fn1 , "r+")
        r=fs.read()
        fs.close()
        s1=" %d," %i1
        index=r.find(s1)
        
        if index!= -1:
            rp=r.replace(s1, "")
            fs = open("C:\\Users\\Admin\\Desktop\\FS\\fusedata.%d" %fn1 , "w")
            fs.write(rp)
            fs.close()
            print "error found in free block list"
            print "error resolved in free block list"
            print ""

        else:
            
            print "no error in free block list"
            print ""
            
        
    
for i in dirlist:
    i1=int(i)
    if i1 !=0:
        fn=math.floor((i1/400)+1)
        fn1=int(fn)
        fs = open("C:\\Users\\Admin\\Desktop\\FS\\fusedata.%d" %fn1 , "r+")
        r=fs.read()
        fs.close()
        s1=" %d," %i1
        index=r.find(s1)
        if index!= -1:
            rp=r.replace(s1, "")
            fs = open("C:\\Users\\Admin\\Desktop\\FS\\fusedata.%d" %fn1 , "w")
            fs.write(rp)
            fs.close()
            print "error found in free block list"
            print "error resolved in free block list"
            print ""

        else:
            print "no error in free block list"
            print ""

print ""

#Question 3 ends and file list and directory list is updated

#Question 6

# Check if the data contained in a location pointer is an array, updates indirect to 1, else update it to 0

def loc_ptr(lp,ar):
            fl = open("C:\\Users\\Admin\\Desktop\\FS\\fusedata.%d" %lp , "r")
            fb=fl.read()
            fl.close()
            
            for k in range(26,31): #block list range
                k1= "%d" %k
                if k1==fb:
                    ar=ar+1
                    loc_ptr(k,ar)
                else:
                    ar=0
                    
                    
                if ar>0:
                    vr1=lz.find("indirect:")
                    vri=lz.index("indirect:")
                    vri=vri+9
                    lz2=lz.replace(lz[vri], "1")
                    fm = open("C:\\Users\\Admin\\Desktop\\FS\\fusedata.%d" %j , "w")
                    fm.write(lz2)
                    fm.close()
                    print "indirect is updated to 1"            

for j in range(26,31): # go through freeblocks
    fi = open("C:\\Users\\Admin\\Desktop\\FS\\fusedata.%d" %j , "r+")
    lz = fi.read()
    fi.close()
    ld=lz.find(" location:")
    if ld != -1:
        ldi=lz.index('location:')
        ldi=ldi+9
        lp= lz[ldi:ldi+2]
        var1=int(lp)
        if var1 != j:  
            xx=int(lp)
            loc_ptr(xx,0)
        else:
            vr1=lz.find("indirect:")
            vri=lz.index("indirect:")
            vri=vri+9
            lz2=lz.replace(lz[vri], "0")
            fm = open("C:\\Users\\Admin\\Desktop\\FS\\fusedata.%d" %j , "w")
            fm.write(lz2)
            fm.close()
            print "indirect is updated to 0" 


        



        
     
