import numpy as np
import dlib
import time
import cv2
import os
import face_recognition
from datetime import datetime
import pyttsx3
from serial import Serial

# import serial
path = 'ImageAuthentication'
images=[]
classNames = []
p=[]
mylist = os.listdir(path)
print(mylist)

for cl in mylist:
    curImg = cv2.imread(f'{path}/{cl}')
    images.append(curImg)
    classNames.append(os.path.splitext(cl)[0])
print(classNames)

def findEncodings(images):
    encodeList = []
    for img in images:
        img = cv2.cvtColor(img,cv2.COLOR_BGR2RGB)
        encode = face_recognition.face_encodings(img)[0]
        encodeList.append(encode)
    return encodeList
# def markration(name):
#     with open('Data.csv','r+') as f:
#         myDataList = f.readlines()
#         nameList = []
#         for line in myDataList:
#             entry = line.split(',')
#             nameList.append(entry[0])
#         if name not in nameList:
#             now = datetime.now()
#             dtString = now.strftime('%H:%M:%S')
#             datem = datetime.today().strftime("%Y-%m")
#             f.writelines(f'\n{name},{dtString},{datem}')
def speak(audio):
    engine.say(audio)
    engine.runAndWait()
engine = pyttsx3.init('sapi5')
voices=engine.getProperty('voices')
engine.setProperty("voice",voices[0].id)
engine.setProperty("rate",140)
engine.setProperty("volume",1000)

encodeListKnown = findEncodings(images)
print(len(encodeListKnown))
speak('encoding completed')
cap = cv2.VideoCapture(0)
count = 10
s=''


while count>0:
    count =count-1
    success , img = cap.read()
    imgs = cv2.resize(img,(0,0),None,0.25,0.25)
    imgs = cv2.cvtColor(imgs,cv2.COLOR_BGR2RGB)
    facesCurFrame = face_recognition.face_locations(imgs)
    encodeCurFrame = face_recognition.face_encodings(imgs,facesCurFrame)
    for encodeFace , faceLoc in zip(encodeCurFrame,facesCurFrame):
        matches = face_recognition.compare_faces(encodeListKnown,encodeFace)
        faceDis = face_recognition.face_distance(encodeListKnown,encodeFace)
        matchIndex = np.argmin(faceDis)
        print(matchIndex)

        if matches[matchIndex]:
            name = classNames[matchIndex].upper()
            print(name)
            s=name
            y1,x2,y2,x1 = faceLoc
            y1,x2,y2,x1 = y1*4,x2*4,y2*4,x1*4
            cv2.rectangle(img,(x1,y1),(x2,y2),(0,255,0),2)
            cv2.rectangle(img,(x1,y2-35),(x2,y2),(0,255,0),cv2.FILLED)
            cv2.putText(img,name,(x1+6,y2-6),cv2.FONT_HERSHEY_COMPLEX,1,(255,255,255),2)
            # markration(name)
            cv2.imshow('webcam',img)
            cv2.waitKey(1)
            a=1

        else:
            a=0
if a==1:
    ard = Serial('com3', 9600)
    speak("Authentication successfull")
    time.sleep(2)
    var = 'a'
    c = var.encode()
    ard.write(c)
    time.sleep(4)
    #speak("your ration is dispatched")
    # account_sid = "ACcd5c41cbb33f280e74d8c1fd5bd0d6e6"
    # auth_token = "926ae887bc50b0ac45e556bfe83fdac8"
    # client = Client(account_sid, auth_token)
    # message = client.messages \
    #     .create(
    #     body="Your ration is dispatched",
    #     from_='+19104773048',
    #     to='+919010079639'
    # )
    # print(message.sid)
else:
    speak('Authentication failed')



