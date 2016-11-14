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

#LINK PATH TO COOKIE NOTIFICATION 
LINKPATH= '//*[@id="cookie_notice"]/a[1]'

#SCHOOL VARIABLE TO INPUT WITHIN SEARCH BOX AND OBTAIN PROFESSOR RESULTS
#WITHIN THE SITE
SCHOOL= 'computer science'

#SET BROWSER TO OPEN FIREFOX WITH SELENIUM WEBDRIVER
browser = webdriver.Firefox()

#GET THE INITAL WEBSITE FOR FRESNO STATE
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
sleep(0.3)

#PUT THE PAGE CONTENTS(UNICODE) FROM THE CURRENT BROWSER INTO 'CONTENT'  
content= browser.page_source
#CONVERT UNICODE INTO STRING FORMAT TO BE ABLE TO PARSE USING LXML
string_content= content.encode("utf-8")

#TYPE CHECKING TO MAKE SURE THE CONVERSION WAS SUCCESSFUL 
print (type(content))
print(type(string_content))

file = open('resultlist.txt', 'w')

soup= BeautifulSoup(string_content, "lxml")
list_of_ratings= soup(class_='result-list')[1].find_all('a')
print len(list_of_ratings)
for a in list_of_ratings:
	spans= a.find_all('span')
	file.write(spans[1].text)
	file.write(spans[2].text)


browser.quit()

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
