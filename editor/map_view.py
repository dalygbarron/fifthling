import tkinter as tk

class MapView(tk.Canvas):
    def __init__(self, master):
        tk.Canvas.__init__(self, master, bg = 'white', width = 360, height = 360)