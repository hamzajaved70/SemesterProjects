#Computer Networks
#End Semester Project
#Group Members:
#M. Ibtesam   (32141)
#Hamza Javed  (32976)

from socket import *            #import socket
from random import randint
import time
import Image                    #image library
import binascii                 #used for conversions between utf-8 characters and binary

#Functions for binary to string and vice versa conversions
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




#Encoding function
def Encode(text):
    
        myFile=open(text,'r')                                           #Open file

        stringFile=myFile.read()                                        #Convert file contents to string and store

        numOfChars=len(stringFile)                                      #get number of characters in file and store it as binary
        print(numOfChars)
        binPoint=0
    
        binCh='{0:08b}'.format(numOfChars)

        binNumCh=[]

        for x in xrange(24):                                            #for storing number of characters in 24 bit binary form
            if(x<24-len(binCh)):
                binNumCh.append('0')

            else:
                binNumCh.append(binCh[binPoint])
                binPoint+=1

        print(binNumCh)                                                 #print binary form of number of characters
        
        if(numOfChars==0):
            binaryFile=[]
        else:
            binaryFile=text_to_bits(stringFile)

        binPoint2=0
        count=0
        count2=0
        binPointFile=0
        randNo = str(randint(1,6))
        img=Image.open('image'+randNo+'.png').convert("RGB")            #open image
        checkstr=''
        print('Number of Pixels: ', img.size[0]*img.size[1])            #print number of pixels in image
        count=0
        for x in xrange(img.size[0]):
            for y in xrange(img.size[1]):
                r,g,b=img.getpixel((x,y))
                rCh=list('{0:08b}'.format(r))                           #the encoding part
                gCh=list('{0:08b}'.format(g))
                bCh=list('{0:08b}'.format(b))

                if (x<8 and y<8 and x==y):                              #store size in the diagonal 8 pixels
                    print('check')
                    rCh[7]=binNumCh[binPoint2]
                    binPoint2+=1
                    r=int(''.join(rCh),2)

                    gCh[7]=binNumCh[binPoint2]
                    binPoint2+=1
                    g=int(''.join(gCh),2)

                    bCh[7]=binNumCh[binPoint2]
                    binPoint2+=1
                    b=int(''.join(bCh),2)
                    print(rCh,gCh,bCh)

                else:                                                   #store the actual text data in the other pixels
                    if(binPointFile<len(binaryFile)):
                        rCh[7]=binaryFile[binPointFile]
                        binPointFile+=1
                        count2+=1
                        r=int(''.join(rCh),2)
                        checkstr+=(rCh[7])


                    if(binPointFile<len(binaryFile)):
                        gCh[7]=binaryFile[binPointFile]
                        binPointFile+=1
                        count2+=1
                        g=int(''.join(gCh),2)
                        checkstr+=(gCh[7])



                    if(binPointFile<len(binaryFile)):
                        bCh[7]=binaryFile[binPointFile]
                        binPointFile+=1
                        b=int(''.join(bCh),2)
                        checkstr+=(bCh[7])
        
                img.putpixel((x,y),(r,g,b))                             #will put pixels back one by one
        
        print(text_from_bits(checkstr))                                 #displays the text that was encoded.
        img.save("imageEncoded.png","PNG")                              #saves the encoded image


        
#####################################################################
serverPort = 55555              #port number
serverSocket = socket(AF_INET,SOCK_STREAM) 
serverSocket.bind(('',serverPort))          #bind ip with port number
serverSocket.listen(1)
s = ''
print 'The server is ready to receive'
request = ''
#header string
header = 'HTTP/1.1 200 OK\nHost: localhost:'+str(serverPort)+'\nConnection: keep-alive\nCache-Control: max-age=0, no-cache, no-store\nDate: ' + str(time.time()) + '\n'
while 1:
    connectionSocket, addr = serverSocket.accept() 
    s = connectionSocket.recv(1024)
    #extract request from browser message
    if (s[s.find("GET /")+5: s.find("HTTP/1.1") - len(s)] != "favicon.ico "):
        request = s[s.find("GET /")+5: s.find("HTTP/1.1") - len(s)]
        print s
        print request
    #if browser requests the encoded image
    if request == 'imageEncoded.png ':
        http_response1 = file(r"C:\Python27\imageEncoded.png", "rb").read()
        connectionSocket.send(header+'Content-Type: image\n'+'\n'+http_response1)
        #connectionSocket.close()
    #if browser requests homepage
    elif request == ' ':
        #send html file
        connectionSocket.send(header + 'Content-Type: text/html\n' + '\n' + """
            <html>
              <head>
                <title>IMAGE ENCODING</title>
              </head>
              <body bgcolor=white>
                <table border="0" cellpadding="10">
                  <tr>
                    <td>
                      <h1>SELECT TEXT FILE TO ENCODE IN RANDOM IMAGE</h1>
                      <td><a href="text1.txt">TEXT FILE 1 </a>
                      </td>
                      <td><a href="text2.txt">TEXT FILE 2 </a>
                      </td>
                      <td><a href="text3.txt">TEXT FILE 3 </a></td>
                      <td><a href="text4.txt">TEXT FILE 4 </a></td>
                      <td><a href="text5.txt">TEXT FILE 5 </a></td>
                      <td><a href="text6.txt">TEXT FILE 6 </a></td>
                    </td>
                  </tr>
                </table>
                <p>To view the encoded image, click on the following link:</p>
                <ul>
                  <li>View <a href="imageEncoded.png">Encoded Image</a>.
                </ul>
              </body>
            </html>
        """)
    #encode the requested text file in random image and send it back to the browser
    elif request == 'text1.txt ' or request == 'text2.txt ' or request == 'text3.txt ' or request == 'text4.txt 'or request == 'text5.txt ' or request == 'text6.txt ':
        Encode(request)
        http_response1 = file(r"C:\Python27\imageEncoded.png", "rb").read()
        connectionSocket.send(header+'Content-Type: image\n'+'\n'+http_response1)
    #if the request is invalid   
    else:
        #send error 404 message
        connectionSocket.send('HTTP/1.1 404 Not Found\n\n' + """
             <head>
	<title>ERROR 404</title>
        </head>
        <body>
            <h1>ERROR 404 PAGE NOT FOUND</h1>
        </body>
        </html>""")
    connectionSocket.close()



