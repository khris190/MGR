import os
import dearpygui.dearpygui as dpg

class myWindow:
    def __init__(self):
        dpg.create_context()

        #region fonts
        # add a font registry
        with dpg.font_registry():
            # first argument ids the path to the .ttf or .otf file
            with dpg.font("AbhayaLibre-Regular.ttf", 18)  as defaultFont:
                dpg.add_font_range_hint(dpg.mvFontRangeHint_Default)
                dpg.add_font_range(0x0104, 0x017C)
                dpg.bind_font(defaultFont)
        #endregion

        dpg.create_viewport(title='Custom Title', width=600, height=600, resizable=False)
        dpg.setup_dearpygui()
        print(os.path.expanduser("~"))
        self.FileSelector = dpg.file_dialog(modal=True, width=600, height=600,directory_selector=False, show=False, cancel_callback=self.file_select_cancel_cb, callback=self.file_select_cb, tag='fileSelector', default_path=os.path.expanduser("~"))
        with self.FileSelector: 
            dpg.add_file_extension("", color=(255, 255, 255, 255))
            dpg.add_file_extension(".png", color=(0, 255, 255, 255))
        # filename = fd.askopenfilename(filetypes=[("Image", ".png")])

        with dpg.window(label="ArtGen",no_resize=True, no_collapse=True,no_move=True, no_close=True, width=600, height=600,):
            dpg.add_button(label="Save", callback=self.on_run_clicked)
            self.ShapeCount = dpg.add_slider_int(label="Liczba Trójkątów: 1", min_value=3, max_value=48, callback=self.ShapeCountCallback, format='', default_value=3)
            self.PopCount = dpg.add_slider_int(label="Wielkość populacji: 16", min_value=1, max_value=9, callback=self.PopCountCallback, format='', default_value=1)
            self.MutationRate = dpg.add_slider_int(label="Szansa mutacji: 0.01%", min_value=1, max_value=100, callback=self.MutationCallback, format='', default_value=1)
            self.FileSelectorButton = dpg.add_button(label="Directory Selector", callback=lambda: dpg.show_item('fileSelector'))

        dpg.show_viewport()
        dpg.start_dearpygui()
        dpg.destroy_context()
    
    def on_run_clicked(self, button):
        print('"Click me" button was clicked')
        prog =  os.path.dirname(__file__) + '/' + self.executable + ' -h'
        output = os.popen( prog).read()
        
    def PopCountCallback(self,sender, app_data):
        dpg.set_item_label(sender, "Wielkość populacji: " + str(self.GetPopCountValue()))
    def GetPopCountValue(self):
        return (dpg.get_value(self.PopCount)*16)
        
    def MutationCallback(self,sender, app_data):
        dpg.set_item_label(sender, "Szansa mutacji: " + str("%.2f" % (self.GetMutationValue()*100) )+ "%")
    def GetMutationValue(self):
        return dpg.get_value(self.MutationRate)/10000
        
    
    def ShapeCountCallback(self,sender, app_data):
        dpg.set_item_label(sender, "Liczba Tkójkątów: " + str(self.GetShapeCountValue()))
    def GetShapeCountValue(self):
        return int(10**(dpg.get_value(self.ShapeCount)/10))
            
    #region file selector callbacks
    def file_select_cb(sender, app_data):
        print('OK was clicked.')
        print("Sender: ", sender)
        print("App Data: ", app_data)

    def file_select_cancel_cb(sender, app_data):
        print('Cancel was clicked.')
        print("Sender: ", sender)
        print("App Data: ", app_data)
    #endregion
    
        
myWindow()
