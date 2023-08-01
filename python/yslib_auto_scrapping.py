'''
연수청학도서관용 Web Scrapping Tool
2019/08/28 written by jwshin
dnpsystem
'''

## import part
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.support.ui import WebDriverWait
import time
import re
import sys

# 책 건수 카운팅을 위한 광역변수
mainCount  = 1
##########################################
## function : 책 정보 읽기 함수
##########################################
def booklist_display():
    global mainCount
    book_search = drive.find_elements_by_xpath("//div[@class='book_data_wrap clearfix  book_data_web']")
    for li in book_search:
        print(li.text)
        print("건수 : %d" % mainCount)
        mainCount += 1
        print("-"*100)

##########################################
## function : 검색 도서의 마지막 페이지 검색
##########################################
def lastPage_search():
    lastdata = drive.find_elements_by_xpath("//html/body/form[1]/div/a")
    loopCount = 0
    for lst in lastdata:
    #    print("lst : %s " %lst.text)
    #    print("loopCount %d : " %loopCount)
        if lst.text == ">>":
            storedata = lastdata[loopCount].get_attribute("href")
    #       print(storedata)
            break
        loopCount += 1
    p = re.compile("[0-9]")
    #numdata = print("".join(p.findall(storedata)))
    returndata = ("".join(p.findall(storedata)))
    return(returndata)

##########################################
## function : 검색 데이터가 있는지 없는지 확인
##########################################
def searchData_exist():
    existData = drive.find_element_by_xpath("//html/body/form/div/div/div")
    searchStr = existData.find_element_by_class_name("search_count_section")
    print(searchStr.text)
    return(searchStr.text)

#chrome silent mode
chrome_options = webdriver.ChromeOptions()
chrome_options.add_argument('headless')
chrome_options.add_argument("--disable-gpu")
chrome_options.add_argument("lang=ko_KR")
drive = webdriver.Chrome('D:\develop_notebook\python_work\chromedriver.exe', chrome_options=chrome_options) # for windows
#drive = webdriver.Chrome('/Users/jungwookshin/Downloads/python_work/chromedriver', chrome_options=chrome_options) # for mac
drive.implicitly_wait(10)
# 연수청학도서관 검색 page  주소
drive.get("http://59.17.153.229:8480/search/search.jsp")
drive.implicitly_wait(10)

# chrome visible mode
#drive = webdriver.Chrome() # for windows
#drive = webdriver.Chrome('/Users/jungwookshin/Downloads/python_work/chromedriver')  # for mac
#drive.get("http://59.17.153.229:8480/search/search.jsp")

#도서관 선택2
# 전체 check box를 해제
linksource = drive.find_element_by_xpath("//html/body/form/div/div/div/table/tbody/tr[2]")
directclick = linksource.find_element_by_id('all')
directclick.click()
# 해당 도서관 check box만 check
# 128058 연수청학 / 128005 연수어린이 / 128047 송도국제어린이 / 128099 해돋이 / 128104 선학별빛
linksource2 = drive.find_element_by_xpath("//html/body/form/div/div/div/table/tbody/tr[2]")
directclick2 = linksource2.find_element_by_id('128099')
directclick2.click()

# 검색어 입력
elem = drive.find_element_by_name('VALUE_1')
keyword = input("검색어를 입력하세요\n")
#keyword = '아두이노'
elem.send_keys(keyword)
elem.send_keys(Keys.RETURN)

# 도서관 선택
#linksource = drive.find_element_by_xpath("//div[@id='totalBox_wrap']")
#directclick = linksource.find_element_by_partial_link_text("해돋이 ")
#print(directclick.text)
#directclick.click()

# 검색건수가 0일 경우, 루틴을 끝낸다.
if(searchData_exist()=="검색결과 - 0건"):
    exit()

#현재 페이지 검색

pageNum = drive.find_element_by_xpath("//html/body/form[1]/input[24]")
print(pageNum.get_attribute('value'))
currentNum = int(pageNum.get_attribute('value'))
numdata = lastPage_search()  # 전체 page 수 검색

print("numdata= %d" %int(numdata))
pagecount = 0
firstflag = 1  # 첫번째 page는 동일한 page이기 때문에 버리기 위해서 firstflag 사용
# 단일 페이지일 경우에는 전체 page 수 만큼만 looping 그렇지 않으면 looping+1
if(int(numdata)==1):
    firstflag = 0   # 단일 페이지일 경우 첫번 째 페이지를 버리지 않는다.
    addVal = 0
else :
    addVal = 1
# 전체 page 갯수까지 looping
while(currentNum <= int(numdata)+addVal):
    #pagecount = currentNum%11
    tt1 = drive.find_element_by_xpath("//html/body/form[1]/div/a"+"["+str(pagecount+2)+"]")
    tempval = str(pagecount+2)
    #print("tempval %s" %tempval)
    if(firstflag == 1):         # 첫번 째 페이지 버린다.
        firstflag = 0
    else:
        booklist_display()
    print("="*100)
    print('\n')
    print("tt1 %s" %tt1.text)
    if(tt1.text == ">"):
        pagecount = 0
    #print("pagecount = %d" %pagecount)
    print("cur: %d" %currentNum)
    tt1.click()
    pagecount += 1
    currentNum += 1
    print("*"*100)

print("검색완료")
time.sleep(1)
drive.quit()
