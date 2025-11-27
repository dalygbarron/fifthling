import tkinter as tk

class CodeEditor(tk.Frame):
    def __init__(self, master):
        tk.Frame.__init__(self, master)
        self.button_bar = tk.Frame(self)
        self.validate_button = tk.Button(self, text = "Validate")
        self.validate_button.pack(side = "left")
        self.button_bar.pack()
        self.txt = tk.Text(self, width = 80, height = 25)
        self.txt.pack()
