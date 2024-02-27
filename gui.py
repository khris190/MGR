import sys, os

import gi
import subprocess
import re

gi.require_version("Gtk", "3.0")
from gi.repository import GLib, Gtk
import numpy as np

from matplotlib.backends.backend_gtk3agg import  FigureCanvasGTK3Agg
from matplotlib.figure import Figure

def Extract(lst, pos):
    return list(list(zip(*lst))[pos])

class MyWindow(Gtk.Window):
    def __init__(self):
        super().__init__(title="Button Demo")
        self.set_border_width(10)

        hbox = Gtk.Box(orientation=Gtk.Orientation.VERTICAL,spacing=5)
        self.add(hbox)
        
        buttonBox = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL,spacing=2)
        self.runButton = Gtk.Button("Run")
        self.runButton.connect("clicked", self.on_click_me_clicked)
        buttonBox.pack_start(self.runButton, True, True, 0)
        hbox.add(buttonBox)
        
        buttonBox = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL,spacing=2)
        label = Gtk.Label("Liczba trójkątów:")
        buttonBox.pack_start(label, True, True, 0)
        
        self.shapeAmountEntry = Gtk.Entry()
        self.shapeAmountEntry.set_text("20000")
        self.shapeAmountEntry.connect("changed", self.on_text_change_int)
        buttonBox.pack_start(self.shapeAmountEntry, True, True, 0)
        hbox.add(buttonBox)
        
        buttonBox = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL,spacing=2)
        label = Gtk.Label("Populacja:")
        buttonBox.pack_start(label, True, True, 0)
        
        self.populationEntry = Gtk.Entry()
        self.populationEntry.set_text("64")
        self.populationEntry.connect("changed", self.on_text_change_int)
        buttonBox.pack_start(self.populationEntry, True, True, 0)
        hbox.add(buttonBox)
        
        buttonBox = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL,spacing=2)
        label = Gtk.Label("Rozmiar trójkątów:")
        buttonBox.pack_start(label, True, True, 0)
        
        self.shapeSizeEntry = Gtk.Entry()
        self.shapeSizeEntry.set_text("0.05")
        self.shapeSizeEntry.connect("changed", self.on_text_change_float)
        buttonBox.pack_start(self.shapeSizeEntry, True, True, 0)
    
        hbox.add(buttonBox)
        
        buttonBox = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL,spacing=2)
        label = Gtk.Label("Obraz:")
        buttonBox.pack_start(label, True, True, 0)
        self.chooseFileButton = Gtk.Button("Wybierz plik")
        self.chooseFileButton.connect("clicked", self.choose_file_clicked)
        buttonBox.pack_start(self.chooseFileButton, True, True, 0)
        hbox.add(buttonBox)
    
        
        files = os.listdir(os.path.dirname(__file__) + '/bin')
        self.executable = 'GenerativeArt.exe'
        if 'GenerativeArt' in files: 
          self.executable = 'GenerativeArt'
    
    def choose_file_clicked(self, button):
        self.filechooserdialog = Gtk.FileChooserDialog(title="Open...",
            parent=None,
            action=Gtk.FileChooserAction.OPEN)
        self.filechooserdialog.add_buttons("_Open", Gtk.ResponseType.OK)
        self.filechooserdialog.add_buttons("_Cancel", Gtk.ResponseType.CANCEL)
        self.filechooserdialog.set_default_response(Gtk.ResponseType.OK)
        response = self.filechooserdialog.run()

        if response == Gtk.ResponseType.OK:
            print("File selected: %s" % self.filechooserdialog.get_filename())

        self.filechooserdialog.destroy()
    
    def on_text_change_int(self, entry):
        entry_context = entry.get_style_context()
        try:
            int(entry.get_text())
            entry_context.remove_class("error")
            self.runButton.set_sensitive(True)
        except ValueError:
            entry_context.add_class("error")
            self.runButton.set_sensitive(False)
    def on_text_change_float(self, entry):
        entry_context = entry.get_style_context()
        try:
            float(entry.get_text())
            entry_context.remove_class("error")
            self.runButton.set_sensitive(True)
        except ValueError:
            entry_context.add_class("error")
            self.runButton.set_sensitive(False)
    
    
    def on_click_me_clicked(self, button):
        print('"Click me" button was clicked')
        prog =  os.path.dirname(__file__) + '/' + self.executable + ' -h'
        output = os.popen( prog).read()

css = '.error { border-color: #f00; }'
css_provider = Gtk.CssProvider()
css_provider.load_from_data(css)

win = MyWindow()
win.set_resizable(False)
win.connect("destroy", Gtk.main_quit)
win.show_all()
Gtk.main()