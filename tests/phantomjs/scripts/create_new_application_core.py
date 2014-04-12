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
        self.driver.get("http://0.0.0.0:8001/")
        self.driver.save_screenshot("createcore_01.png")

# Basic project data
        self.driver.find_elements_by_link_text("Basic project data").click()
        self.driver.save_screenshot("createcore_02.png")

        self.driver.find_element_by_id("projectname").send_keys("ProjectA")
        self.driver.find_element_by_id("binaryfilename").send_keys("project_a")
        self.driver.find_element_by_id("licence_template").select_by_visible_text("AGPL3")
        self.driver.save_screenshot("createcore_03.png")

        self.driver.find_element_by_name("form_assume_licence").click()
        self.driver.save_screenshot("createcore_03.png")

        self.driver.find_element_by_id("doxygen_templates").click()
        self.driver.find_element_by_id("route_reverse").click()
        self.driver.find_element_by_id("csrf_token").click()
        self.driver.find_element_by_id("tntdb_support").click()
        self.driver.save_screenshot("createcore_04.png")

        self.driver.find_element_by_name("form_save_button").click()
        self.driver.save_screenshot("createcore_05.png")



# ende ...
        self.driver.find_element_by_id("os_username").send_keys("olaf")
        self.driver.find_element_by_id("os_password").send_keys("xxxxxxxxx")
        self.driver.find_element_by_id("loginButton").click()
        self.assertIn("https://confluence.atix.de/", self.driver.current_url)
        self.driver.save_screenshot("02_desktop.png")

# Persoenlichen Bereich oeffnen...
        self.driver.get("https://confluence.atix.de/spaces/viewspace.action?key=~olaf")
        self.assertIn("https://confluence.atix.de/display/~olaf/Home", self.driver.current_url)
        self.driver.save_screenshot("03_persoenlicher_bereich.png")
# Neue Seite anlegen...
        self.driver.find_element_by_id("create-page-button").click()
        self.driver.save_screenshot("04_dialog.png")
#        self.driver.find_element_by_class_name("create-dialog-create-button aui-button aui-button-primary").click()
#        self.driver.find_element(by="class", value="create-dialog-create-button aui-button aui-button-primary").click()
#        create_button = self.driver.find_element_by_class_name("create-dialog-create-button aui-button aui-button-primary")
#        create_button = self.driver.find_element_by_tag_name("button")

        create_button = self.driver.find_elements_by_link_text("Erstellen")

        print create_button
        create_button.click()
        self.wait_for_element_visibility( create_button ).click()
        self.driver.save_screenshot("05_dialog.png")
        self.driver.find_element_by_id("content-title").send_keys("bot fake site")
        self.driver.find_element_by_id("rte-button-publish").click()
        self.driver.save_screenshot("06_dialog.png")

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
