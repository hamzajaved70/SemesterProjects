#Computer Networks
#End Semester Project
#Group Members:
#M. Ibtesam   (32141)
#Hamza Javed  (32976)

import Image
import binascii
import msvcrt               #for the getch function on windows

##   Functions for converting string to binary and vice versa 
def text_to_bits(text, encoding='utf-8', errors='surrogatepass'):
    bits = bin(int(binascii.hexlify(text.encode(encoding, errors)), 16))[2:]
    return bits.zfill(8 * ((len(bits) + 7) // 8))

def text_from_bits(bits, encoding='utf-8', errors='surrogatepass'):
    n = int(bits, 2)
    return int2bytes(n).decode(encoding, errors)

def int2bytes(i):
    hex_string = '%x' % i
    n = len(hex_string)
    return binascii.unhexlify(hex_string.zfill(n + (n & 1)))


img=Image.open("imageDownloaded.png").convert("RGB")                #opens image

count=0
findSize=[]

for i in xrange(8):                                                 #for finding the size(number of characters) of the encoded text file
    r,g,b=img.getpixel((i,i))
    rCh=list('{0:08b}'.format(r))
    gCh=list('{0:08b}'.format(g))
    bCh=list('{0:08b}'.format(b))
    print(rCh,gCh,bCh)
    findSize.append(rCh[7])
    findSize.append(gCh[7])
    findSize.append(bCh[7])

fSize=''.join(findSize)

print(fSize)                                                        #prints number of characters in binary

size=int(fSize,2)                                                   #converts binary atring to int.

print(size)                                                         #prints number of characters in int
BinNum=0

messageBin=''

if (size==0):                                                       #if no message was encoded
    print("No Encoded message")
    print "\n\n\nPress any key to continue..."
    msvcrt.getch()
    
else:
    for x in xrange(img.size[0]):                                   #decoding part
        for y in xrange(img.size[1]):                               #other than the diagonal 8, pixels within size range are used
            r,g,b=img.getpixel((x,y))                               #for decoding the text, 
            if((x,y)!=(0,0) and (x,y)!=(1,1) and (x,y)!=(2,2) and (x,y)!=(3,3)
               and (x,y)!=(4,4) and (x,y)!=(5,5) and (x,y)!=(6,6) and (x,y)!=(7,7)):
                rCh=list('{0:08b}'.format(r))
                gCh=list('{0:08b}'.format(g))
             
                bCh=list('{0:08b}'.format(b))
                if(BinNum<(size*8)):
                    messageBin+=(rCh[7])
                    BinNum+=1
                if(BinNum<(size*8)):
                    messageBin+=(gCh[7])
                    BinNum+=1
                if(BinNum<(size*8)):
                    messageBin+=(bCh[7])
                    BinNum+=1
                if(BinNum>=(size*8)):
                    break

        if(BinNum>=(size*8)):    
            break


    print(text_from_bits(messageBin))                               #for displaying the decoded text.
    
    print "\n\n\nPress any key to continue..."
    msvcrt.getch()




