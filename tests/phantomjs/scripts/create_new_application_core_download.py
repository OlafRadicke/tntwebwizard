#!/usr/bin/python

import time
import unittest
from selenium import webdriver

class TestOne( unittest.TestCase ):

    def setUp(self):
        fp = webdriver.FirefoxProfile()
        fp.set_preference('browser.helperApps.neverAsk.saveToDisk',
                  'application/vnd.ms-excel, application/msword')
        self.driver = webdriver.Firefox(fp)

        #self.driver = webdriver.PhantomJS()

    def test_url(self):
        self.driver.set_window_size(1920,1080)
# 01 - start screen
# 1
        self.driver.get("http://0.0.0.0:8001/")
        self.driver.save_screenshot("/tmp/createcore_01_01.png")

# 02 - Basic project data
# 2
        self.driver.find_element_by_link_text('Basic project data').click()
        self.driver.save_screenshot("/tmp/createcore_02_02.png")

# 3
        self.driver.find_element_by_id("projectname").clear();
        self.driver.find_element_by_id("projectname").send_keys("ProjectA")
        self.driver.find_element_by_id("binaryfilename").clear();
        self.driver.find_element_by_id("binaryfilename").send_keys("project_a")

        el = self.driver.find_element_by_id("licence_template")
        for option in el.find_elements_by_tag_name('option'):
            if option.text == 'AGPL3':
                option.click()

        self.driver.save_screenshot("/tmp/createcore_02_03.png")

# 4
        self.driver.find_element_by_name("form_assume_licence").click()
        self.driver.save_screenshot("/tmp/createcore_02_04.png")

# 5
        #self.driver.find_element_by_id("doxygen_templates").click()
        #self.driver.find_element_by_id("route_reverse").click()
        #self.driver.find_element_by_id("csrf_token").click()
        #self.driver.find_element_by_id("tntdb_support").click()
        self.driver.save_screenshot("/tmp/createcore_02_05.png")

# 6
        self.driver.find_element_by_name("form_save_button").click()
        self.driver.save_screenshot("/tmp/createcore_02_06.png")

# 03 - Create project core

        self.driver.find_element_by_link_text('Create project core').click()
        self.driver.save_screenshot("/tmp/createcore_03_01.png")


        el = self.driver.find_element_by_id("cli_support")
        for option in el.find_elements_by_tag_name('option'):
            if option.text == 'YES':
                option.click()
        self.driver.save_screenshot("/tmp/createcore_03_02.png")

        el = self.driver.find_element_by_id("config_format")
        for option in el.find_elements_by_tag_name('option'):
            if option.text == 'JSON':
                option.click()
        self.driver.save_screenshot("/tmp/createcore_03_03.png")

        self.driver.find_element_by_id("host_ipv4").clear();
        self.driver.find_element_by_id("host_ipv4").send_keys("127.0.0.1")
        self.driver.find_element_by_id("port_no").clear();
        self.driver.find_element_by_id("port_no").send_keys("8088")
        self.driver.find_element_by_id("session_timeout").clear();
        self.driver.find_element_by_id("session_timeout").send_keys("14000")
        self.driver.save_screenshot("/tmp/createcore_03_04.png")

        el = self.driver.find_elements_by_xpath("//*[contains(text(), 'Create')]")
        print el
        for option in el:
            print "option.text" + option.text
            if option.text == 'Create':
                print "TEST OKAY!"
                option.click()
        self.driver.save_screenshot("/tmp/createcore_03_05.png")

# 04 - download

        self.driver.find_element_by_link_text('Download').click()
        self.driver.save_screenshot("/tmp/createcore_04_01.png")

# ende ...


    def tearDown( self ):
        self.driver.quit


if __name__ == "__main__":
    unittest.main()
