import tkinter as tk
from PIL import Image
from enum import StrEnum

class LevelView(tk.Frame):
    class EditType(StrEnum):
        SELECT = "SELECT"
        MOVE = "MOVE"
        SCALE = "SCALE"

    def __init__(self, master):
        tk.Frame.__init__(self, master)
        self.edit_mode = tk.StringVar(
            master = self,
            value = self.EditType.SELECT)
        self.button_bar = tk.Frame(self)
        self.edit_buttons = []
        for i, et in enumerate(self.EditType):
            b = tk.Button(self.button_bar, text = et)
            self.edit_buttons.append(b)
            b.pack(side = "left")
        self.button_bar.pack()
        self.canvas = tk.Canvas(self, bg = 'white', width = 640, height = 360)
        self.canvas.pack()
