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

#Takes a string ex. "7:00AM" and converts to military time
# Returns a string
def standard_to_military(time_str):
    hour = int(time_str[:len(time_str)-2].split(':')[0])

    if (time_str[len(time_str)-2] == 'A' and hour != 12) or (time_str[len(time_str)-2] == 'P' and hour == 12):
        return time_str[:len(time_str)-2]
    elif (time_str[len(time_str)-2] == 'A' and hour == 12) or (time_str[len(time_str)-2] == 'P' and hour != 12):
        temp_array = time_str[:len(time_str)-2].split(':')
        temp_array[0] = str(int(temp_array[0])+12)
        return ':'.join(temp_array)
    else:
        return "ERROR - unable to convert time"

#Takes a string representing days that a section is on ex. "MoWeFr" and converts it to an ancient and terrifying language
# Returns a string ex. if a section is on "MoWeFr" then this will return "10101"
def days_to_robot_language(days_str):
    days_array = []
    while days_str:
        days_array.append(days_str[:2])
        days_str = days_str[2:]

    robo_days = list('00000')
    if "Mo" in days_array:
        robo_days[0] = "1"
    if "Tu" in days_array:
        robo_days[1] = "1"
    if "We" in days_array:
        robo_days[2] = "1"
    if "Th" in days_array:
        robo_days[3] = "1"
    if "Fr" in days_array:
        robo_days[4] = "1"

    return "".join(robo_days)

# Takes dates in this format "08/22/2016 - 12/15/2016"
# Returns a string of how many number of months that is
def dates_to_num_months(dates_str):
    dates_array = dates_str.split("/")
    start_month = int(dates_array[0])
    start_year = int(dates_array[2].split(" ")[0])
    end_month = int(dates_array[2].split(" ")[2])
    end_year = int(dates_array[4][:4])

    return str(end_month - start_month + ((end_year - start_year) * 12))

browser = webdriver.PhantomJS()
browser.get('https://my.fresnostate.edu/psp/mfs/EMPLOYEE/HRMS/c/SA_LEARNER_SERVICES.CLASS_SEARCH.GBL?PORTALPARAM_PTCNAV=FR_CLASS_SEARCH_GBL2&EOPP.SCNode=EMPL&EOPP.SCPortal=EMPLOYEE&EOPP.SCName=FR_VIEW_SOC&EOPP.SCLabel=Class%20Schedule&EOPP.SCPTfname=FR_VIEW_SOC&FolderPath=PORTAL_ROOT_OBJECT.FR_VIEW_SOC.FR_CLASS_SEARCH_GBL2&IsFolder=false')
browser.switch_to_frame(0);
browser.find_element_by_name('SSR_CLSRCH_WRK_SUBJECT$0').send_keys('CSCI')
browser.find_element_by_name('CLASS_SRCH_WRK2_SSR_PB_CLASS_SRCH').click()

wait = WebDriverWait(browser, 5)
wait.until(EC.presence_of_element_located((By.NAME, '#ICSave')))
browser.find_element_by_name('#ICSave').click()
wait.until(EC.presence_of_element_located((By.ID, 'ACE_SSR_CLSRSLT_WRK_GROUPBOX1')))

major = browser.find_element_by_xpath('//*[@id="win0divDERIVED_CLSRCH_SSR_CLSRCH_CRIT"]/div/table/tbody/tr/td/strong[1]').text
content = browser.page_source.encode("utf-8")

file = open('courseInfo.txt', 'w')
soup = BeautifulSoup(content, "lxml")
table = soup.find(id='ACE_$ICField$4$$0')
courses = table.find_all(class_ = 'PSHYPERLINK PTCOLLAPSE_ARROW')
for i in range(len(courses)):
    temp = courses[i].get('title').replace("Collapse section", "")
    course_name = " ".join(temp.split())
    courses[i] = course_name

section_count = 0
for i in range(len(courses)):
    course_sections = table.find(id = 'ACE_SSR_CLSRSLT_WRK_GROUPBOX2$'+str(i))
    sections = course_sections.find_all(class_ = 'PSLEVEL1GRIDNBONBO')

    for j in range(len(sections)):
        number = course_sections.find(id = 'MTG_CLASS_NBR$'+str(section_count)).get_text()
        section = course_sections.find(id = 'MTG_CLASSNAME$span$'+str(section_count)).get_text()
        time = course_sections.find(id = 'MTG_DAYTIME$'+str(section_count)).get_text()
        room = course_sections.find(id = 'MTG_ROOM$'+str(section_count)).get_text()
        instructor = course_sections.find(id = 'MTG_INSTR$'+str(section_count)).get_text()
        dates = course_sections.find(id = 'MTG_TOPIC$'+str(section_count)).get_text()

    # COURSE NAME FORMATTING #
        course = " ".join(courses[i].split()[:2])
    # END COURSE NAME FORMATTING #

    # INSTRUCTOR FORMATTING #
        inst_fname = ""
        inst_lname = ""
        instructor_array = instructor.split()
        if len(instructor_array) == 1:
            inst_fname = "Staff"
            inst_lname = instructor_array[0]
        elif len(instructor_array) > 2:
            inst_fname = instructor_array[0]
            inst_lname = instructor_array[1]
        elif len(instructor_array) == 2:
            inst_fname = instructor_array[0]
            inst_lname = instructor_array[1]
        else:
            inst_fname = "ERROR"
            inst_lname = "ERROR"
    # END INSTRUCTOR FORMATTING #

    # DAY AND TIME FORMATTING #
        start_time = ""
        end_time = ""
        days = ""
        daytime_array = time.split()

        # If no day or time is present
        if len(daytime_array) == 1:
            start_time = "0:00"
            end_time = "0:00"
            days = "00000"

        # If days/start_time/end_time are all present
        elif len(daytime_array) >= 4:
            temp_days = daytime_array[0]
            temp_start = daytime_array[1]
            temp_end = daytime_array[3]

            start_time = standard_to_military(temp_start)
            end_time = standard_to_military(temp_end)
            days = days_to_robot_language(temp_days)

        # error
        else:
            start_time = "ERROR"
            end_time = "ERROR"
            days = "ERROR"

    # END DAY AND TIME FORMATTING #

    # TERM FORMATTING #
        term = ""
        if dates_to_num_months(dates) >= 4:
            term = "1"
        else:
            term = "0"
    # END TERM FORMATTING #

    # UNIT FORMATTING #
    # Couldn't come up with a feasible way to do this, the units aren't available on the page
    # where I scraped all this info from, it would be possible to pull it from a different
    # source but that just seemed like too much effort.
        units = "0"
    # END UNIT FORMATTING #

        section_count+=1
        file.write(number+"*"+major+"*"+course+"*"+inst_lname+"*"+inst_fname+"*"+start_time+"*"+end_time+"*"+days+"*"+term+"*"+units+"\n")

browser.quit()
