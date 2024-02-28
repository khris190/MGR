import sys, os
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

        with dpg.file_dialog(directory_selector=False, show=False, cancel_callback=self.file_select_cancel_cb, callback=self.file_select_cb, id="file_dialog_id", width=500 ,height=400):
            dpg.add_file_extension("", color=(255, 255, 255, 255))
            dpg.add_file_extension(".png", color=(0, 255, 255, 255))
            
        with dpg.window(label="ArtGen", autosize=True,no_resize=True, no_collapse=True, no_close=True):
            dpg.add_button(label="Save", callback=self.on_run_clicked)
            dpg.add_input_text(label="string")
            self.ShapeCount = dpg.add_slider_int(label="Liczba Tkójkątów: 1", min_value=1, max_value=48, callback=self.ShapeCountCallback, format='', default_value=1)
            self.PopCount = dpg.add_slider_int(label="Wielkość populacji: 16", min_value=1, max_value=9, callback=self.PopCountCallback, format='', default_value=1)
            dpg.add_slider_float(label="float", min_value=0.001, max_value=0.2)
            dpg.add_button(label="Directory Selector", callback=lambda: dpg.show_item("file_dialog_id"))

        dpg.show_viewport()
        dpg.start_dearpygui()
        dpg.destroy_context()
    
    def on_run_clicked(self, button):
        print('"Click me" button was clicked')
        prog =  os.path.dirname(__file__) + '/' + self.executable + ' -h'
        output = os.popen( prog).read()
    def PopCountCallback(self,sender, app_data):
        dpg.set_item_label(self.PopCount, "Wielkość populacji: " + str(self.GetPopCountValue()))
        
    def GetPopCountValue(self):
        return (dpg.get_value(self.PopCount)*16)
    
    def ShapeCountCallback(self,sender, app_data):
        dpg.set_item_label(self.ShapeCount, "Liczba Tkójkątów: " + str(self.GetShapeCountValue()))
        
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
