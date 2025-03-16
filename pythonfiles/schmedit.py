import tkinter as tk
from tkinter import filedialog, messagebox
from moviepy.editor import VideoFileClip, TextClip, CompositeVideoClip, vfx

class BasicVideoEditor:
    def __init__(self, root):
        self.root = root
        self.root.title("Basic Video Editor")
        self.video = None

        # GUI Elements
        self.load_btn = tk.Button(root, text="Load Video", command=self.load_video)
        self.load_btn.pack()

        self.trim_start = tk.Entry(root)
        self.trim_start.pack()
        self.trim_start.insert(0, "Start Time (s)")

        self.trim_end = tk.Entry(root)
        self.trim_end.pack()
        self.trim_end.insert(0, "End Time (s)")

        self.trim_btn = tk.Button(root, text="Trim Video", command=self.trim_video)
        self.trim_btn.pack()

        self.crop_x = tk.Entry(root)
        self.crop_x.pack()
        self.crop_x.insert(0, "Crop x")

        self.crop_y = tk.Entry(root)
        self.crop_y.pack()
        self.crop_y.insert(0, "Crop y")

        self.crop_w = tk.Entry(root)
        self.crop_w.pack()
        self.crop_w.insert(0, "Crop width")

        self.crop_h = tk.Entry(root)
        self.crop_h.pack()
        self.crop_h.insert(0, "Crop height")

        self.crop_btn = tk.Button(root, text="Crop Video", command=self.crop_video)
        self.crop_btn.pack()

        self.text_entry = tk.Entry(root)
        self.text_entry.pack()
        self.text_entry.insert(0, "Text to add")

        self.text_btn = tk.Button(root, text="Add Text", command=self.add_text)
        self.text_btn.pack()

        self.speed_entry = tk.Entry(root)
        self.speed_entry.pack()
        self.speed_entry.insert(0, "Speed Factor")

        self.speed_btn = tk.Button(root, text="Change Speed", command=self.change_speed)
        self.speed_btn.pack()

        self.save_btn = tk.Button(root, text="Save Video", command=self.save_video)
        self.save_btn.pack()

    def load_video(self):
        file_path = filedialog.askopenfilename()
        if file_path:
            self.video = VideoFileClip(file_path)
            messagebox.showinfo("Info", "Video loaded successfully!")

    def trim_video(self):
        try:
            start = float(self.trim_start.get())
            end = float(self.trim_end.get())
            self.video = self.video.subclip(start, end)
            messagebox.showinfo("Info", "Video trimmed successfully!")
        except Exception as e:
            messagebox.showerror("Error", str(e))

    def crop_video(self):
        try:
            x = int(self.crop_x.get())
            y = int(self.crop_y.get())
            w = int(self.crop_w.get())
            h = int(self.crop_h.get())
            self.video = self.video.crop(x1=x, y1=y, x2=x + w, y2=y + h)
            messagebox.showinfo("Info", "Video cropped successfully!")
        except Exception as e:
            messagebox.showerror("Error", str(e))

    def add_text(self):
        try:
            txt = self.text_entry.get()
            txt_clip = TextClip(txt, fontsize=70, color='white').set_duration(self.video.duration)
            self.video = CompositeVideoClip([self.video, txt_clip.set_position('center')])
            messagebox.showinfo("Info", "Text added successfully!")
        except Exception as e:
            messagebox.showerror("Error", str(e))

    def change_speed(self):
        try:
            speed = float(self.speed_entry.get())
            self.video = self.video.fx(vfx.speedx, speed)
            messagebox.showinfo("Info", "Speed changed successfully!")
        except Exception as e:
            messagebox.showerror("Error", str(e))

    def save_video(self):
        file_path = filedialog.asksaveasfilename(defaultextension=".mp4",
                                                 filetypes=[("MP4 files", "*.mp4")])
        if file_path:
            self.video.write_videofile(file_path)
            messagebox.showinfo("Info", "Video saved successfully!")

if __name__ == "__main__":
    root = tk.Tk()
    app = BasicVideoEditor(root)
    root.mainloop()
