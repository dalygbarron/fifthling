import tkinter as tk
from level_view import LevelView
from code_editor import CodeEditor
from map_view import MapView

# window
window = tk.Tk()
window.title("Demon")

window.columnconfigure(1, weight=1)

level_view = LevelView(window)
level_view.grid(row = 0, column = 0)

map_view = MapView(window)
map_view.grid(row = 1, column = 0)

code_editor = CodeEditor(window)
code_editor.grid(row = 0, column = 1, rowspan = 2)

window.mainloop()
