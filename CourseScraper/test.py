def validNumber(number):
    for char in number:
        try:
            int(char)
        except ValueError:
            return False
    return True

def validMajor(major):
    for char in major:
        try:
            int(char)
            return False
        except ValueError:
            pass
    return True

def validCourse(course):
    course_array = course.split()
    if len(course_array) != 2:
        return False
    for char in course_array[0]:
        try:
            int(char)
            return False
        except ValueError:
            pass
    return True


def validFnameLname(name):
    for char in name:
        try:
            int(char)
            return False
        except ValueError:
            pass
    return True

def validStimeEtime(time):
    try:
        time_array = time.split(':')
        for char in time_array[0]:
            int(char)
        for char in time_array[1]:
            int(char)
    except ValueError:
        return False
    return True

def validDays(days):
    try:
        if len(days) != 5:
            return False
        for day in days:
            if int(day) != 1 and int(day) != 0:
                return False
    except ValueError:
        return False
    return True

def validTerm(term):
    try:
        if len(term) != 1:
            return False
        if int(term) != 1 and int(term) != 0:
            return False
    except ValueError:
        return False
    return True

def validUnits(units):
    try:
        for char in units:
            int(char)
    except ValueError:
        return False
    return True

def testCourse(courseInfo):
    for each in courseInfo:
        course = each.split('*')
        if (
            validNumber(course[0])
            and validMajor(course[1])
            and validCourse(course[2])
            and validFnameLname(course[3])
            and validFnameLname(course[4])
            and validStimeEtime(course[5])
            and validStimeEtime(course[6])
            and validDays(course[7])
            and validTerm(course[8])
            and validUnits(course[9][len(course[9])-2]) #removes hidden newline
            ):
            pass
        else:
            return "INVALID COURSE: " + str(course)
    return "VALID COURSES"


f = open('courseInfo.txt', 'r')

print testCourse(f)
