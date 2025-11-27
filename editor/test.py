import tkinter as tk
from level_view import LevelView
from code_editor import CodeEditor

def convert():
    miles = entry_int.get()
    km = miles * 1.61
    output_string.set(km)

# window
window = tk.Tk()
window.title("Demon")

level_view = LevelView(window)
level_view.grid(row = 0, column = 0, columnspan = 2)

code_editor = CodeEditor(window)
code_editor.grid(row = 0, column = 2, rowspan = 3, sticky=(tk.N, tk.S))


# title
# title_label = tk.Label(
#     master = window,
#     text = "Gamer funny time",
#     font = "Calibri 24 bold"
# )
# title_label.pack()
# 
# # input field
# input_frame = tk.Frame(master = window)
# entry_int = tk.IntVar()
# entry = tk.Entry(master = input_frame, textvariable = entry_int)
# button = tk.Button(master = input_frame, text = "convert", command = convert)
# entry.pack(side = "left", padx = 5)
# button.pack(side = "left", padx = 5)
# input_frame.pack(pady = 10)
# 
# # output
# output_string = tk.StringVar()
# output_label = tk.Label(
#     master = window,
#     text = "out",
#     font = "Calibri 24",
#     textvariable=output_string
# )
# output_label.pack(pady = 5)

# run
window.mainloop()
