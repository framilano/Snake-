import os
import tkinter as tk
import tkinter.font as font

if (os.name == "posix"): difficulty_folder = "configs/"
else: difficulty_folder = "configs\\"

def option_selected(choice, window):
    difficulty_file = open(difficulty_folder + "difficulty.txt", "w")
    difficulty_file.write(str(choice.get()))
    window.destroy()
    return

def main():
    window = tk.Tk()
    window.geometry("400x100")
    window.configure(bg="#181818")
    window.title("Choose game difficulty")
    v = tk.IntVar()
    tk.Radiobutton(window, bg="#181818", fg="#FFFFFF", selectcolor="#000000", width=10, text="Easy",
        variable=v, value=0, command=lambda: option_selected(v, window)).pack()
    tk.Radiobutton(window, bg="#181818", fg="#FFFFFF", selectcolor="#000000", width=10, text="Medium",
        variable=v, value=1, command=lambda: option_selected(v, window)).pack()
    tk.Radiobutton(window, bg="#181818", fg="#FFFFFF", selectcolor="#000000", width=10, text="Hard",
        variable=v, value=2, command=lambda: option_selected(v, window)).pack()
    tk.Radiobutton(window, bg="#181818", fg="#FFFFFF", selectcolor="#000000", width=10, text="Extreme",
        variable=v, value=3, command=lambda: option_selected(v, window)).pack()
    window.mainloop()

main()