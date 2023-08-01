'''
연수청학도서관 자동휴일check를 위한 python program
written by jwshin
'''


import pymysql
from datetime import datetime
import numpy as np
import re
import sys
import subprocess


'''
list search function

'''

#----------------------------------
def linearSearch(lst,key):
	for i in range(len(lst)):
		if key == lst[i]:
			return 1
	return 0
#----------------------------------


# 내부 111번 mysql server 접속
conn=pymysql.connect(host='10.10.10.111',user='libx',password='libx01',db='libx', charset='utf8', autocommit=True)

curs = conn.cursor()

# 올해 변수
yearnow = datetime.today().year

# 이번 달 변수
monthnow = datetime.today().month

# 오늘 날짜 변수
todaynow = datetime.today().day
 

# lib_holiday table에서 해당 도서관 코드, 년, 달의 날짜 데이터만 취득
# me : 얀수청학 , ml : 동춘나래 , mh : 해돋이 , md : 송도국제 , mk : 선학별빛
curs.execute("select days from lib_holiday where manage_code='me' and year=%s and month=%s",(yearnow,monthnow))

rows = curs.fetchall()

conn.close()

#print(rows)
#test=list(rows[0])
#print(test)

#holiday_liststr = list(rows[0])

#print(type(holiday_liststr))

# 튜플 데이터를 list로 변환
conv = list(rows[0])

# list데이터를 문자열로 변환
conv2 = ' '.join(conv)

#문자열 데이터에서 공백 제거
conv3 = conv2.replace(" ", "")
print(conv3)

#문자열 데이터를 다시 정형화된 list로 변환
data_list = conv3.split(",")
print(data_list)

#list 데이터가 문자열 이므로, int로 변환
data_listint = list(map(int,data_list))

# int로 변환된 list에서 오늘 날짜와 비교하여 휴일이 있는지 검색
print(data_listint)
result = linearSearch(data_listint,todaynow)
print(result)

# 만약 휴일이면 1, wol.sh를 wol.xxx로 mv 하며
# 평일 이면 0, wol.xxx를 wol.sh로 mv 한다.
if(result==1):
	print("holiday!!!")
#	subprocess.call(["sudo","mv","/home/pi/wol.sh","/home/pi/wol.xxx"])
else:
	print("normal")
#	subprocess.call(["sudo","mv","/home/pi/wol.xxx","/home/pi/wol.sh"])

#f = open('holy.txt','w')
#f.write(str(result))
#f.write("\n")
#f.close()



