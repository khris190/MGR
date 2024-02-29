import os
import dearpygui.dearpygui as dpg

# import xdialog
# print(xdialog.open_file("Select image", filetypes=[("Images", "*.png")], multiple=False))

print(os.name)
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
        print(os.path.expanduser("~"))
        self.FileSelector = dpg.file_dialog(modal=True, width=600, height=600,directory_selector=False, show=False, cancel_callback=self.file_select_cancel_cb, callback=self.file_select_cb, tag='fileSelector', default_path=os.path.expanduser("~"))
        with self.FileSelector: 
            dpg.add_file_extension("", color=(255, 255, 255, 255))
            dpg.add_file_extension(".png", color=(0, 255, 255, 255))
        # filename = fd.askopenfilename(filetypes=[("Image", ".png")])
        with dpg.window(label="ArtGen",no_resize=True, no_collapse=True,no_move=True, no_close=True, width=600, height=600,):
            dpg.add_button(label="Save", callback=self.on_run_clicked)
            self.ShapeCount = dpg.add_slider_float(label="Liczba Trójkątów: 10", min_value=0.8, max_value=3.8, callback=self.ShapeCountCallback, format='', default_value=0.3)
            self.PopCount = dpg.add_slider_int(label="Wielkość populacji: 16", min_value=1, max_value=9, callback=self.PopCountCallback, format='', default_value=1)
            self.MutationRate = dpg.add_slider_int(label="Szansa mutacji: 0.01%", min_value=1, max_value=100, callback=self.MutationCallback, format='', default_value=1)
            self.FileSelectorButton = dpg.add_button(label="Directory Selector", callback=lambda: dpg.show_item('fileSelector'))
            self.FileSelectorText = dpg.add_text(label="Directory Selector", default_value="hello", pos=[-100, -100]) #start offscreen

        dpg.setup_dearpygui()
        dpg.show_viewport()
        dpg.start_dearpygui()
        dpg.destroy_context()
    
    def on_run_clicked(self, button):
        print('"Click me" button was clicked')
        print( dpg.get_item_pos(self.FileSelectorButton))
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
        return int(20**(dpg.get_value(self.ShapeCount)))
            
    #region file selector callbacks
    def file_select_cb(self, sender, app_data):
        #file_path_name/file_name/current_path/current_filter/min_size/max_size/selections
        print(app_data)
        print(app_data['file_path_name'])
        print(app_data['selections'])
        # tile_name == '.png' znaczy brak selekcji z jakiegoś powodu po zaznaczeniu pliku selekcja nie jest pod tym względem poprawna
        FileSelectorButtonPos = dpg.get_item_pos(self.FileSelectorButton)
        FileSelectorButtonPos[0] += 150
        dpg.set_item_pos(self.FileSelectorText, FileSelectorButtonPos)
        for x in app_data['selections']:
            dpg.set_value(self.FileSelectorText, str(app_data['selections'][x]))
        
        
    def file_select_cancel_cb(sender, app_data):
        print('Cancel was clicked.')
        print("Sender: ", sender)
        print("App Data: ", app_data)
    #endregion
    
        
myWindow()
