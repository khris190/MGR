import os
import dearpygui.dearpygui as dpg
from tkinter import filedialog as fd


print(os.name)


class myWindow:
    def __init__(self):
        dpg.create_context()

        # region fonts
        # add a font registry
        with dpg.font_registry():
            # first argument ids the path to the .ttf or .otf file
            with dpg.font("AbhayaLibre-Regular.ttf", 18) as defaultFont:
                dpg.add_font_range_hint(dpg.mvFontRangeHint_Default)
                dpg.add_font_range(0x0104, 0x017C)
                dpg.bind_font(defaultFont)
        # endregion

        dpg.create_viewport(
            title="Custom Title", width=600, height=600, resizable=False
        )
        with dpg.window(
            label="ArtGen",
            no_resize=True,
            no_collapse=True,
            no_move=True,
            no_close=True,
            width=600,
            height=600,
        ):
            self.runButton = dpg.add_button(
                label="Uruchom", callback=self.on_run_clicked, enabled=False
            )
            self.ShapeCount = dpg.add_slider_float(
                label="Liczba Trójkątów: 10",
                min_value=0.8,
                max_value=3.8,
                callback=self.ShapeCountCallback,
                format="",
                default_value=0.3,
            )
            self.PopCount = dpg.add_slider_int(
                label="Wielkość populacji: 16",
                min_value=1,
                max_value=9,
                callback=self.PopCountCallback,
                format="",
                default_value=1,
            )
            self.MutationRate = dpg.add_slider_int(
                label="Szansa mutacji: 0.01%",
                min_value=1,
                max_value=100,
                callback=self.MutationCallback,
                format="",
                default_value=1,
            )
            self.FileSelectorButton = dpg.add_button(
                label="Directory Selector", callback=self.fileSelectorCallback
            )
            self.FileSelectorText = dpg.add_text(
                label="Directory Selector", default_value="hello", pos=[-100, -100]
            )  # start offscreen

        dpg.setup_dearpygui()
        dpg.show_viewport()
        dpg.start_dearpygui()
        dpg.destroy_context()

    def on_run_clicked(self, button):
        prog = (
            os.path.dirname(__file__)
            + f'/bin/GenerativeArt -t 16 -i "{self.selectedFilename}" -p {self.GetPopCountValue()} -s {self.GetShapeCountValue()} -m {self.GetMutationValue()} --hours 0.15'
        )
        print(prog)
        dpg.disable_item(self.runButton)
        output = os.popen(prog).read()
        print(output)
        dpg.enable_item(self.runButton)

    def PopCountCallback(self, sender, app_data):
        dpg.set_item_label(
            sender, "Wielkość populacji: " + str(self.GetPopCountValue())
        )

    def GetPopCountValue(self):
        return dpg.get_value(self.PopCount) * 16

    def MutationCallback(self, sender, app_data):
        dpg.set_item_label(
            sender,
            "Szansa mutacji: " + str("%.2f" % (self.GetMutationValue() * 100)) + "%",
        )

    def GetMutationValue(self):
        return dpg.get_value(self.MutationRate) / 10000

    def ShapeCountCallback(self, sender, app_data):
        dpg.set_item_label(
            sender, "Liczba Tkójkątów: " + str(self.GetShapeCountValue())
        )

    def GetShapeCountValue(self):
        return int(20 ** (dpg.get_value(self.ShapeCount)))

    def fileSelectorCallback(self):
        self.filename = fd.askopenfilename(
            filetypes=(("Images", "*.png"), ("All files", "*.*"))
        )
        if isinstance(self.filename, str):
            dpg.enable_item(self.runButton)
            self.selectedFilename = self.filename
            FileSelectorButtonPos = dpg.get_item_pos(self.FileSelectorButton)
            FileSelectorButtonPos[0] += 150
            dpg.set_item_pos(
                self.FileSelectorText, [float(x) for x in FileSelectorButtonPos]
            )
            dpg.set_value(self.FileSelectorText, self.selectedFilename)


myWindow()
