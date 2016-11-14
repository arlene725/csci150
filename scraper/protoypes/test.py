#!/usr/bin/python

import string

#python script that will add information to a file 
'''
 how to call python from c++
 python file needs to be in the same directory as main.cpp
 additional library to include : #include <cstdlib>
 python script call: system("python test.py");

'''

'''
to scrape a javascript website
requires selenium and a webdriver (firefox, or chrome potentially)
Firefox is used in this example

***Note: this does not fit our project needs but demonstrates how to 
go through a website that contains javascript and manipulate it 
with the help of a browser 

'''
#importing lxml to use the commmands to scrape 
from lxml.html as lh

from time import sleep
from selenium import webdriver
from selenium.webdriver.common.keys import Keys

SITE_ADDR = 'https://www.ratemyprofessors.com/campusRatings.jsp?sid='
#link_xpath leads to the Enter Your Department search box that will be filled out 
LINK_XPATH= '//*[@id="mainContent"]/div[1]/div/div[3]/div/div/input'
#csci is what you will be filling into the department search box
CSCI= 'computer science'
#school variable is just in case you need to re-enter the fresno state web portion 
#SCHOOL= 'fresno state'
#upc is the code that goes at the end of the site_addr where the fresno state content page resides
UPC= '161'


#using inheritance.
class ScrapingBrowser(webdriver.Firefox):
	def _init_(self, addr, upc, *args, **kwargs):
		super('''requires arguments for python 2.7, needs no arguments if you use python 3.0'''), _init_(*args, **kwargs)
		#inheriting from the firefox class, has mathod implicitly wait
		#makes code wait for html to appear
		self.implicity_wait(10)
		#get method also from firefox class
		self.get(addr +upc)

		#defining eneter school methods that takes the department name, 
		#looks for an element by xpath and then clicks
		#self.find_element_by_xpath(LINK_XPATH).click()
		#looking for element by name  self.find_element_by_name('').send_keys(zipcode, Keys.RETURN)
	def enter_school(self, csci):
		self.find_element_by_xpath(LINK_XPATH).send_keys(csci, Keys.RETURN)

	def get_data():
		self.find_elements_by_tag_name('side-panel') 

#all of this code below commented out is not necessary for our project, 
#still useful to keep as a reference for now
'''
	def switch_to_target_form(self):
		iframe = None

		while not iframe:
			sleep(0.3)
			for frame in self.find_elements_by_tag_name('iframe'):
				if 'reservation.js' in str(fream.get_attribute('src')):
					iframe= frame

		self.switch_to.frame(iframe)

	def scroll_to_button(self):
		stores_div = self.find_element_by_id('')

		previous_last_phone = None
		while True:
			last_store_div = stores_div.find_elements_by_class_name('ng-scope')[-1]
		#last_span has the teacher rating
			last_span = last_store_div.find_element_by_tag_name('')[2].find_elements_by_tag_name('span')[-1]

			if last_span.text == previous_last_phone:
				return

			else:
				previous_last_phone = last_span.text
				self.execute_script('',last_span)
				sleep(2.5)
'''

if _name_ =='__main__':
	browser = ScrapingBrowser(SITE_ADDR, UPC)
	browser.enter_school(CSCI)
	browser.get_data
	#browser.switch_to_target_form()
	#browser.scroll_to_button
	data=browser.page_source
	browser.quit()




#obtaining data from certain xpath, 
#we print out the results to make sure all the information is available
#will later be placed into a new file for use
doc= lh.fromstring(data)
for elt in doc.xpath('//*[@id="mainContent"]/div[1]/div/div[5]'): #xpath of the result-list class 
	print elt



#example of how to write to a file:
#file object is file 
#writing to text file text.txt or creating one if it hasnt been created 

data = 'this stuff will be data pulled from scraper'

file = open('text.txt', 'w')
file.write('it will be over written everytime it gets called.\n')
file.write(data)
file.close()

#file object is filer to read from it 
#text.txt is the file we will read from it 

filer = open('text.txt','r')

#we cant work with files directly, needs to be stored into a variable
#t is the variable 

t=filer.read()
print(t)
filer.close()

#end of python script
 
