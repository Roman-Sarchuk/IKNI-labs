import thinkdsp as dsp
import tkinter as tk
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import numpy as np


# TODO: file: save wav, import file | window func: | gener wave: |
def display_dual_plots_with_controls():
    # Створюємо вікно Tkinter
    root = tk.Tk()
    root.title("Аналіз сигналів")
    root.geometry("1200x600")

    # Створюємо фрейм для елементів керування вгорі
    control_frame = tk.Frame(root)
    control_frame.pack(side=tk.TOP, fill=tk.X, padx=10, pady=10)

    # Додаємо кнопку, поле вводу та ще одну кнопку
    first_button = tk.Button(control_frame, text="Генерувати сигнал", command=lambda: generate_signal())
    first_button.pack(side=tk.LEFT, padx=5)

    input_field = tk.Entry(control_frame, width=20)
    input_field.pack(side=tk.LEFT, padx=5)
    input_field.insert(0, "880")  # Значення за замовчуванням (частота в Гц)

    second_button = tk.Button(control_frame, text="Аналізувати спектр", command=lambda: analyze_spectrum())
    second_button.pack(side=tk.LEFT, padx=5)

    input_file_field = tk.Entry(control_frame, width=40)
    input_file_field.pack(side=tk.LEFT, padx=5)
    input_file_field.insert(0, "D:\\Roman\\ІКНІ\\ПП-24\\DigitalSignalPprocessing\\92002__jcveliz__violin-origional.wav")

    third_button = tk.Button(control_frame, text="Аналізувати файл", command=lambda: analyze_wav_file())
    third_button.pack(side=tk.LEFT, padx=5)

    # Створюємо фрейм для графіків
    plots_frame = tk.Frame(root)
    plots_frame.pack(side=tk.TOP, fill=tk.BOTH, expand=True, padx=10, pady=10)

    # Фрейм для першого графіка (зліва)
    left_frame = tk.Frame(plots_frame)
    left_frame.pack(side=tk.LEFT, fill=tk.BOTH, padx=5, expand=True)

    # Фрейм для другого графіка (справа)
    right_frame = tk.Frame(plots_frame)
    right_frame.pack(side=tk.RIGHT, fill=tk.BOTH, padx=5, expand=True)

    # Створюємо перший графік (хвильова форма)
    fig1 = Figure(figsize=(4, 4))
    ax1 = fig1.add_subplot(111)
    ax1.set_title("Хвильова форма")
    ax1.set_xlabel("Час (с)")
    ax1.set_ylabel("Амплітуда")

    canvas1 = FigureCanvasTkAgg(fig1, master=left_frame)
    canvas1.draw()
    canvas1.get_tk_widget().pack(fill=tk.BOTH, expand=True)

    # Створюємо другий графік (спектр)
    fig2 = Figure(figsize=(4, 4))
    ax2 = fig2.add_subplot(111)
    ax2.set_title("Частотний спектр")
    ax2.set_xlabel("Частота (Гц)")
    ax2.set_ylabel("Амплітуда")

    canvas2 = FigureCanvasTkAgg(fig2, master=right_frame)
    canvas2.draw()
    canvas2.get_tk_widget().pack(fill=tk.BOTH, expand=True)

    # Глобальні змінні для збереження даних хвилі
    wave_data = {"wave": None}

    def generate_signal():
        try:
            frequency = float(input_field.get())
            # Створюємо синусоїдальний сигнал
            sin_sig = dsp.SinSignal(freq=frequency, amp=0.5, offset=0)
            wave = sin_sig.make_wave(duration=0.5, start=0, framerate=11025)
            wave_data["wave"] = wave

            # Оновлюємо перший графік
            ax1.clear()
            ax1.plot(wave.ts, np.real(wave.ys))
            ax1.set_title(f"Хвильова форма (частота: {frequency} Гц)")
            ax1.set_xlabel("Час (с)")
            ax1.set_ylabel("Амплітуда")
            canvas1.draw()

        except ValueError:
            tk.messagebox.showerror("Помилка", "Введіть коректне числове значення для частоти")

    def analyze_spectrum():
        if wave_data["wave"] is None:
            tk.messagebox.showinfo("Інформація", "Спочатку згенеруйте сигнал")
            return

        # Обчислюємо спектр
        spectrum = wave_data["wave"].make_spectrum()

        # Оновлюємо другий графік
        ax2.clear()
        ax2.plot(spectrum.fs, spectrum.amps)
        ax2.set_title("Частотний спектр")
        ax2.set_xlabel("Частота (Гц)")
        ax2.set_ylabel("Амплітуда")
        # Обмежимо відображення частотного діапазону для кращої видимості
        ax2.set_xlim(0, 2000)
        canvas2.draw()

    def analyze_wav_file():
        try:
            wave = dsp.read_wave(input_file_field.get())
            wave_data["wave"] = wave

            # Оновлюємо перший графік
            ax1.clear()
            ax1.plot(wave.ts, np.real(wave.ys))
            ax1.set_title(f"Хвильова форма")
            ax1.set_xlabel("Час (с)")
            ax1.set_ylabel("Амплітуда")
            canvas1.draw()

            analyze_spectrum()
        except BaseException as ex:
            tk.messagebox.showerror(str(ex))

    # Генеруємо початковий сигнал
    generate_signal()

    # Запускаємо головний цикл Tkinter
    root.mainloop()


if __name__ == '__main__':
    display_dual_plots_with_controls()