#!/usr/bin/python

import time
import unittest
from selenium import webdriver

class TestOne( unittest.TestCase ):

    def setUp(self):
        self.driver = webdriver.PhantomJS()

    def test_url(self):
        self.driver.set_window_size(1920,1080)
# start screen
# 1
        self.driver.get("http://0.0.0.0:8001/")
        self.driver.save_screenshot("createcore_01.png")

# Basic project data
# 2
        #self.driver.find_elements_by_partial_link_text("Basic project data")[0].click()
        self.driver.find_element_by_link_text('Basic project data').click()
        #self.driver.get("../core/basicprojectdata")
        self.driver.save_screenshot("createcore_02.png")

# 3
        self.driver.find_element_by_id("projectname").send_keys("ProjectA")
        self.driver.find_element_by_id("binaryfilename").send_keys("project_a")
        #self.driver.find_element_by_id("licence_template").select_by_visible_text("AGPL3")
        #self.driver.find_element_by_id("licence_template").deselect_by_value("AGPL3")

        el = self.driver.find_element_by_id("licence_template")
        for option in el.find_elements_by_tag_name('option'):
            print "option.text" + option.text
            if option.text == 'AGPL3':
                print "TEST OKAY!"
                option.click()

        self.driver.save_screenshot("createcore_03.png")

# 4
        self.driver.find_element_by_name("form_assume_licence").click()
        self.driver.save_screenshot("createcore_04.png")

# 5
        self.driver.find_element_by_id("doxygen_templates").click()
        self.driver.find_element_by_id("route_reverse").click()
        self.driver.find_element_by_id("csrf_token").click()
        self.driver.find_element_by_id("tntdb_support").click()
        self.driver.save_screenshot("createcore_05.png")

# 6
        self.driver.find_element_by_name("form_save_button").click()
        self.driver.save_screenshot("createcore_06.png")



# ende ...


    def tearDown( self ):
        self.driver.quit

    def wait_for_element_visibility( self, element ):
        if element.is_displayed():
            return element
        else:
            for i in range(10):
                if not element.is_displayed():
                    time.sleep(.5)
                else:
                    return element


if __name__ == "__main__":
    unittest.main()
