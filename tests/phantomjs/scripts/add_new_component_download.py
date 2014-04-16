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
        testname = "add_new_component_download"
        self.driver.set_window_size(1920,1080)
# 01 - start screen
# 1
        self.driver.get("http://0.0.0.0:8001/")
        self.driver.save_screenshot("/tmp/" + testname + "_01_01.png")

# 02 - Basic project data
# 2
        self.driver.find_element_by_link_text('Basic project data').click()
        self.driver.save_screenshot("/tmp/" + testname + "_02_02.png")

# 3
        self.driver.find_element_by_id("projectname").clear();
        self.driver.find_element_by_id("projectname").send_keys("ProjectA")
        self.driver.find_element_by_id("binaryfilename").clear();
        self.driver.find_element_by_id("binaryfilename").send_keys("project_a")

        el = self.driver.find_element_by_id("licence_template")
        for option in el.find_elements_by_tag_name('option'):
            if option.text == 'AGPL3':
                option.click()

        self.driver.save_screenshot("/tmp/" + testname + "_02_03.png")

# 4
        self.driver.find_element_by_name("form_assume_licence").click()
        self.driver.save_screenshot("/tmp/" + testname + "_02_04.png")

# 5
        #self.driver.find_element_by_id("doxygen_templates").click()
        #self.driver.find_element_by_id("route_reverse").click()
        #self.driver.find_element_by_id("csrf_token").click()
        #self.driver.find_element_by_id("tntdb_support").click()
        #self.driver.find_element_by_id("flash_messages_support").click()
        self.driver.save_screenshot("/tmp/" + testname + "_02_05.png")

# 6
        self.driver.find_element_by_name("form_save_button").click()
        self.driver.save_screenshot("/tmp/" + testname + "_02_06.png")

# 03 - Create project core

        self.driver.find_element_by_link_text('Create project core').click()
        self.driver.save_screenshot("/tmp/" + testname + "_03_01.png")


        el = self.driver.find_element_by_id("cli_support")
        for option in el.find_elements_by_tag_name('option'):
            if option.text == 'YES':
                option.click()
        self.driver.save_screenshot("/tmp/" + testname + "_03_02.png")

        el = self.driver.find_element_by_id("config_format")
        for option in el.find_elements_by_tag_name('option'):
            if option.text == 'JSON':
                option.click()
        self.driver.save_screenshot("/tmp/" + testname + "_03_03.png")

        self.driver.find_element_by_id("host_ipv4").clear();
        self.driver.find_element_by_id("host_ipv4").send_keys("127.0.0.1")
        self.driver.find_element_by_id("port_no").clear();
        self.driver.find_element_by_id("port_no").send_keys("8088")
        self.driver.find_element_by_id("session_timeout").clear();
        self.driver.find_element_by_id("session_timeout").send_keys("14000")
        self.driver.save_screenshot("/tmp/" + testname + "_03_04.png")

        el = self.driver.find_elements_by_xpath("//*[contains(text(), 'Create')]")
        print el
        for option in el:
            print "option.text" + option.text
            if option.text == 'Create':
                print "TEST OKAY!"
                option.click()
        self.driver.save_screenshot("/tmp/" + testname + "_03_05.png")

# 04
        self.driver.find_element_by_link_text('New component').click()
        self.driver.save_screenshot("/tmp/" + testname + "_04_01.png")

        self.driver.find_element_by_id("namespace").clear();
        self.driver.find_element_by_id("namespace").send_keys("CompA")

        self.driver.find_element_by_id("ecppfilename").clear();
        self.driver.find_element_by_id("ecppfilename").send_keys("comp_a")

        self.driver.find_element_by_id("url_route").clear();
        self.driver.find_element_by_id("url_route").send_keys("compa/comp_a_view")

        self.driver.find_element_by_id("webform_support").click()

        self.driver.find_element_by_id("controllername").clear();
        self.driver.find_element_by_id("controllername").send_keys("CompAController")

        self.driver.find_element_by_id("modelname").clear();
        self.driver.find_element_by_id("modelname").send_keys("CompADataModel")

        # start item 1
        self.driver.find_element_by_id("property_name").clear();
        self.driver.find_element_by_id("property_name").send_keys("foo")

        el = self.driver.find_element_by_id("property_type")
        for option in el.find_elements_by_tag_name('option'):
            if option.text == 'int':
                option.click()
        self.driver.find_element_by_name("form_add_property").click()

        el = self.driver.find_elements_by_xpath("//*[contains(text(), 'Add property')]")
        print el
        for option in el:
            if option.text == 'Add property':
                option.click()

        # ende item 1

        # start item 2
        self.driver.find_element_by_id("property_name").clear();
        self.driver.find_element_by_id("property_name").send_keys("bar")

        el = self.driver.find_element_by_id("property_type")
        for option in el.find_elements_by_tag_name('option'):
            if option.text == 'std::string':
                option.click()

        el = self.driver.find_elements_by_xpath("//*[contains(text(), 'Add property')]")
        print el
        for option in el:
            if option.text == 'Add property':
                option.click()
        # ende item 2

        self.driver.find_element_by_id("destructor").click()
        self.driver.find_element_by_id("json_serialization").click()
        self.driver.find_element_by_id("xml_serialization").click()

        self.driver.save_screenshot("/tmp/" + testname + "_04_02.png")

        el = self.driver.find_elements_by_xpath("//*[contains(text(), 'Create component')]")
        print el
        for option in el:
            if option.text == 'Create component':
                option.click()

        self.driver.save_screenshot("/tmp/" + testname + "_04_03.png")


# 05 - download

        self.driver.find_element_by_link_text('Download').click()
        self.driver.save_screenshot("/tmp/" + testname + "_05_01.png")
# ende ...


    def tearDown( self ):
        self.driver.quit


if __name__ == "__main__":
    unittest.main()
