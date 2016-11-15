#!/usr/bin/python

from time import sleep
import lxml.html as lh
from lxml import html
import requests

from bs4 import BeautifulSoup

from selenium import webdriver
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.support import expected_conditions as EC

'''
-To scrape a website with javascript we require a method to execute the javascript before
you can collect the data.

-Selemnuim is a webdriver used in this case to execute all comands to obtain an HTML with the
required information

-Firefox is used for the webdriver to call (This is also the reason that a firefox window will pop up)

-BeautifulSoup and lxml are used to parse through the HTML file

-Calling python script from a C++ program:
#include <cstlib>
system("python scraper.py");

'''


#LINK PATH TO COOKIE NOTIFICATION 
LINKPATH= '//*[@id="cookie_notice"]/a[1]'

#SCHOOL VARIABLE TO INPUT WITHIN SEARCH BOX AND OBTAIN PROFESSOR RESULTS
#WITHIN THE SITE
SCHOOL= 'computer science'

#SET BROWSER TO OPEN FIREFOX WITH SELENIUM WEBDRIVER
browser = webdriver.Firefox()

#GET THE INITAL PAGE FOR FRESNO STATE
browser.get('https://www.ratemyprofessors.com/campusRatings.jsp?sid=161')

#WAIT UNTIL THE COOKIE NOTIFICATION ID IS PRESENT
wait = WebDriverWait(browser, 10)
wait.until(EC.presence_of_element_located((By.ID, 'cookie_notice')))

#FIND THE LOCATION FOR THE BUTTON ON THE COOKIE NOTIFICATION AND CLICK IT
browser.find_element_by_xpath(LINKPATH).click()
#FIND THE SEARCH BOX TO SPECIFY SCHOOL DEPARTMENT, INSERT SCHOOL AND HIT RETURN
browser.find_element_by_xpath('//*[@id="mainContent"]/div[1]/div/div[3]/div/div/input').send_keys(SCHOOL, Keys.RETURN)
#WAIT AGAIN UNITL THE MAIN CONTENTS OF THE PAGE APPEAR SIDE BAR APPEAR
wait.until(EC.presence_of_element_located((By.XPATH, '//*[@id="mainContent"]/div[1]')))
#LOAD ALL OF THE PROFESSORS (THIS XPATH LINK DOES NOT WORK YET), UNKNOWN AS TO WHY. 
#browser.find_element_by_xpath('//*[@id="mainContent"]/div[1]/div/div[5]/div/div[1]').click()

#SLEEP THE PROGRAM TO ALLOW FOR ALL HTML CONTENT TO APPEAR FROM EXECUTED JAVASCRIPT
sleep(0.3)

#PUT THE PAGE CONTENTS(UNICODE) FROM THE CURRENT BROWSER INTO 'content'  
content= browser.page_source
#CONVERT UNICODE INTO STRING FORMAT TO BE ABLE TO PARSE USING LXML
string_content= content.encode("utf-8")

#TYPE CHECKING TO MAKE SURE THE CONVERSION WAS SUCCESSFUL 
#print (type(content))
#print(type(string_content))

#OPEN A FILE TO WRITE ALL DATA TO
file = open('resultlist.txt', 'w')

#USING BEAUTIFULSOUP SEARCH FOR THE CLASS RESULT-LIST AND FIND ALL 'a'
#ATTRIBUTES
soup= BeautifulSoup(string_content, "lxml")
list_of_ratings= soup(class_='result-list')[1].find_all('a')
#PRINT THE LENGTH OF HOW MANY RATINGS THERE ARE
#print len(list_of_ratings)

#WRITE INTO THE OPEN FILE ALL TEXT IN THE SECOND AND THIRD SPAN
for a in list_of_ratings:
	spans= a.find_all('span')
	file.write(spans[1].text)
	file.write("*")
	file.write(spans[2].text)

#CLOSE THE FILE AND QUIT THE BROWSER FIREFOX
file.close()
browser.quit()

#PROGRAM END


### THE REMAINDER CODE
'''
browser.find_element(By.CLASS_NAME, "side-panel")

#POSSIBLY Need to scroll down side bar panel to load more 
browser.execute_script("window.scrollTo(0, document.body.scrollHeight);")
'''


'''
file = open('elt.txt', 'w')
#SEARCH THROUGH THE STRING_CONTENT TO FIND THE RESULT LIST AND PLACE INTO A FILE
doc = lh.fromstring(string_content)
for elt in doc.text_content():
	file.write(elt.encode("utf-8"))
#THIS FILE OBTAINS EVERYTHING FROM THE WEBSITE PAGE, IT IS NOT ABLE TO DISTINGUISH THE RESULT-LIST YET. 
file.close()

#CLOSE THE BROWSER
browser.quit()

'''