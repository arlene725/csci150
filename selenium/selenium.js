// This requires installing npm, selenium-webdriver, phantomjs, and probably some other things I'm forgetting

var webdriver = require('selenium-webdriver'),
    By = webdriver.By,
    until = webdriver.until;

var driver = new webdriver.Builder()
    .forBrowser('phantomjs')
    .build();

driver.get('https://my.fresnostate.edu/psp/mfs/EMPLOYEE/HRMS/c/SA_LEARNER_SERVICES.CLASS_SEARCH.GBL?PORTALPARAM_PTCNAV=FR_CLASS_SEARCH_GBL2&EOPP.SCNode=EMPL&EOPP.SCPortal=EMPLOYEE&EOPP.SCName=FR_VIEW_SOC&EOPP.SCLabel=Class%20Schedule&EOPP.SCPTfname=FR_VIEW_SOC&FolderPath=PORTAL_ROOT_OBJECT.FR_VIEW_SOC.FR_CLASS_SEARCH_GBL2&IsFolder=false');
driver.switchTo().frame(0);
driver.findElement(By.name('SSR_CLSRCH_WRK_SUBJECT$0')).sendKeys('CSCI');
driver.findElement(By.name('CLASS_SRCH_WRK2_SSR_PB_CLASS_SRCH')).click();
driver.wait(until.elementLocated(By.name('#ICSave')), 10*1000).then(function(elm) {
  elm.click();
});
driver.wait(until.elementLocated(By.id('ACE_SSR_CLSRSLT_WRK_GROUPBOX1')), 10*1000).then(function(elm) {
  driver.findElement(By.id('ACE_$ICField$4$$0')).getText().then(function(table) {
    var fs = require('fs');
    var stream = fs.createWriteStream("courseInfo.txt");
    stream.once('open',function(fd){
      stream.write(table);
      stream.end();
    });
  });
});
