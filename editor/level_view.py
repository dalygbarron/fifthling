import tkinter as tk
from PIL import Image, ImageTk
from enum import Enum

class LevelView(tk.Frame):
    class EditType(Enum):
        SELECT = "SELECT"
        MOVE = "MOVE"
        SCALE = "SCALE"

    def __init__(self):
        self.edit_mode = tk.StringVar(
            master = self,
            value = LevelView.EditType.SELECT)
        self.label = tk.Label(master = self, text = "This is where pic goes")
