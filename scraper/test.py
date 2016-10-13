#!/usr/bin/python

import string

#python script that will add information to a file 

# how to call python from c++
# python file needs to be in the same directory as main.cpp
# additional library to include : #include <cstdlib>
# python script call: system("python test.py");
# 

'''

to scrape a javascript website
requires selenium and a webdriver (firefox, or chrome potentially)
Firefox is used in this example

***Note: this does not fit our project needs but demonstrates how to 
go through a website that contains javascript and manipulate it 
with the help of a browser 

'''

from time import sleep
from selenium import webdriver
from selenium.webdriver.common.keys import Keys

SITE_ADDR = 'https://www.ratemyprofessors.com/campusRatings.jsp?sid='
LINK_XPATH= '//*[@id="mainContent"]/div[1]/div/div[3]/div/div/input'
CSCI= 'computer science'
SCHOOL= 'fresno state'
UPC= '161'


class ScrapingBrowser(webdriver.Firefox):
	def _init_(self, addr, upc, *args, **kwargs):
		super('''requires arguments for python 2.7, needs no arguments if you use python 3.0'''), _init_(*args, **kwargs)
		self.implicity_wait(10)
		self.get(addr +upc)

	def enter_school(self, school)
		self.find_element_by_xpath(LINK_XPATH).click()
		self.finc_element_by_name('').send_keys(zipcode, Keys.RETURN)

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

if _name_ =='__main__':
	browser = ScrapingBrowser(SITE_ADDR, UPC)
	browser.enter_school(SCHOOL)
	browser.switch_to_target_form()
	browser.scroll_to_button


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
 
