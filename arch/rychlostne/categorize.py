from html.parser import HTMLParser
from enum import Enum
import os
import unicodedata
def strip_accents(s):
   return ''.join(c for c in unicodedata.normalize('NFD', s)
                  if unicodedata.category(c) != 'Mn')

class State(Enum):
    INIT = 1
    NAME = 2
    TASKS = 3
    TASK = 4

class MyHTMLParser(HTMLParser):
    def __init__(self):
        super(MyHTMLParser,self).__init__()
        self.field = State.INIT

    def handle_starttag(self, tag, attrs):
        if (tag == "li"):
            self.field = State.NAME
        if tag == 'a' and self.field == State.TASKS:
            self.field = State.TASK

    def handle_endtag(self, tag):
        if (tag == "li"):
            self.field = State.INIT
        if tag == "a" and self.field == State.TASK:
            self.field = State.TASKS

    def handle_data(self, data):
        if self.field == State.NAME:
            self.field = State.TASKS
            self.contest = strip_accents(data).split(" (")[0].replace(' ','-').replace('.','').lower()
            if not os.path.exists(self.contest):
                os.mkdir(self.contest)
        elif self.field == State.TASK:
            fname = "%s.cpp" % data
            if os.path.exists(fname):
                os.rename(fname, "%s/%s" % (self.contest, fname))

with open('tasks.html','r') as f:
    x = f.read()
    parser = MyHTMLParser()
    parser.feed(x)
