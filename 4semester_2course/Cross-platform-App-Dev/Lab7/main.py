import base64
import tkinter as tk
from tkinter import PhotoImage
from tkinter import font as tkfont
from tkinter import messagebox
import random
import pygame
import json
from datetime import datetime
import time


pygame.init()

COLORS = {
    "MainMenu": {
        "bg": "#2c3e50",
        "bt_play": "#3498db",
        "bt_exit": "#e74c3c",
        "text": "white"
    },
    "GameFrame": {
        "left_panel": "#34495e",
        "bt_menu_bg": "#3498db",
        "bt_menu_text": "white",
        "score_bg": "#9198FF",
        "score_text": "white",
        "move_bg": "#2FA8FF",
        "move_text": "white",
        "timer_bg": "#B892FF",
        "timer_text": "white",
        "bt_restart_bg": "#DB3A91",
        "bt_restart_text": "black",
        "coord_bg": "#34495e",
        "coord_text": "white",
        "game_container_bg": "#9AEBFF",
        "canvas_bg": "white",
        "canvas_bd": "black",
        "selected_cell_bg": "#87CEFA"
    },
}
GAME_FIELD_SIZE = (10, 10)
CANVAS_PADDING = 10
EMOJI_BASE64 = [
    # apple.png
        "iVBORw0KGgoAAAANSUhEUgAAAEgAAABICAMAAABiM0N1AAADAFBMVEVHcEwAAABsJxwyEw9BGRMtEQ7GKysAAAASCQkAAABwLShMHRd9Khs1FRAAAAAjDQoAAAAAAAAAAAAAAAAAAAAAAABUFxNcIhxYGBVOHhhNHhcmDQpoJB9YGhRVFxNrJR5jKiA4FhF0KSJ3LSZHGxWSLynMMzPVKytJFhJwJh9uKCFlJx4AAABLHBcAAADPST1qKCAAAAAAAABUIRoAAAAAAABZGRRkHBdoLiNpJyBvIht5MSQ1Eg4wEg5oJx81FBFEEg9VIRlfJB1nHRduIBlYIhpuIBpGGxYrCwlzJR5qLB8rEQ2dOyc9EQ2FKR+TMyZhJx5MFRFEGRSnLy9aIxt9JR1sKyNGGBMVCAZGGxVzIRtEFRFSFhJPHhdMFBGVLSRjIx2LKCIAAAAAAAAuEg6wMScpEA1kJh1zLCIsEQ5tLCTaOjAAAAAAAAAAAAAAAAAAAAAOBQNgJB0AAABsKiAAAAA8FxMAAACNNisAAACXOy0WCAcAAADqWkfSLycAAACxzDMBAAAFAQEJAwIGAgLVNCsCAQHiSzzZU0HmVELTMCjqWEXkTz4NBQReJBwHCQLdQjVzGRURBANNHReMNSoMAwK5KSJaFBHFTDyuQjQgBwYcCwjbVEMSBgXgRznaPDDeRDflUUDbPjKpQTN0LCN5GxaEMigYBQRWExCjJB7WNixFDw2TOCydIx2oJR9qKSCjPzIUBQSnQDIxCwnRLycpEA2WOS3MLSbkWEXGLCUZCgi5RzgsCQjHTTxCGRRNEQ5iJh4cIQgfDAk4QRCDHRgmDgs7FxKrxjEmLAqvyjKbsyzgSTnoVkTYOzDUMinfVkRuGRQ6DQuGHhltGBQ/Dgx8jyTTLyi0KCGnwDCwJyE9DgtIHBblWEaSqSpnKB9gFRJSHxmeIx2zRTY1FBAwEg5YIhuHNCm+RDWvJyF2LiQKDAO/STrXUkFOWhfCSjvWUUDPUD/eVUOInSexRDbRUD/UUkBUIBpwKyIYHAcPEQSpwjEsMg2iui+BlSV3iiI/SRK6I52ZAAAAfXRSTlMA9w/q1/ADCwX0E8EJ7MH3FqzwCuPt4pPftLn5LeXpahviNCfIGAUG4E8pR4PFHApMpzS9MXrgxxaIlznv61vn9Kuv0rWIqtD9pDrxDfaWKHb01TGZp0Lj/dKy6vDF9ltQcicJ9NbzV1L1I9pGyfsi2tuFeX+K6K/7L3H2OlwE3iwAAANvSURBVFjD7dZ1VNVQHAfwB4iAICCiiIUgYIvd3R3Y3d2d25ftPR+IwFMEJe3u7kSxu7u7u2t3e3A4nm3vCvyhR75/7Gx7533Ovb+73f00mrSk5d9Jj1RyutsUt04VqGgWZEodqdRfKJVwQvHUKXiJwchsPLWySpFkAyuN9cDC9s5mgJl9accUQfYgMRiEg1nhHimAxsDw48hBP79L5/dxGOSYfMjRGT8P+4l58wlDh9D9M6eLrW9d12YZjJdOpNjjbLDvoCR9OwTnohSMm4VeLAiCfT3EGyNGkePELDh0RJK+fMUwk+tnno6DdteCsEU37gE630KJP/iMnwDD8+sEOvzdgPzp1Z08vaF9HMOIibglDM2hyPBiBQuMLDl6LBPwQRjmk717P5Ph7hjgrebYWSLuBZOYnSHBSMgB4fppSDQ55aJ279+6uZca5InoV0zSbFn3cVd8bPyBPZsCpBsBEREvl7FCZqK9stNHz29nTCeIQPuxtqkiZIHVDE3mCdCG9cim5HRFcAwVNPmCIC1FqJcC1Al7GLrMJpPbgVoKkAMiKSF/Ai1ENXmnAYKvUUJTAgXoIkLln8rauMrQ5jgZ0mIUkIVcKdeMZCqBTqOCLJQOYdTQUQItQVmFp2g+NSRW+xTKyEKVqRfNCE1D1hSPaJYaVBXrqKE5BDqr8JK4YxM1NE/aAGrKQrZYQA1NItBy1JGFXDCd1jlGHDYKbrJQFWz8o1pv5XhzWSiDTv+MEhL3yJWop/D2Z8QKOmeuOLObyK0A1aAt0mxjiZooQBW58JMM7Z7NrsJaH6W91hKLaDYjsULsbsWZaTTlsW0L5RbCzuD5LoqQdw6KcvsHstJj3VnlA9kS0a9NfUEk5xHPdVOB0vdEiAlHfDnIV62jahPRV8dFUjjCDrK4hXo7UhKxESoLf0JyVvJoZaI/srZA3HuldZ8q1YddpUUukw2bVz9sfCe/XMZpsUtD0Tyf6dYvrwO2vU0K3HkQ9nBu0JwEhl3Io3Ejml60vyX0IYn7wPa7pLVaPiOBuXwFXC47uq7WzpaH7v4aobWKWTNdj7bt2mihXXJ7s/A4nznHIbw+fWtdzJ10tlqtcNAVEdpkjw6ccBrOk5v5C/5Rl946e0Ohf9RauuaUrgt55tABsZWq501Gy29e7reW106TlrT8b/kFle6tH7J0xx4AAAAASUVORK5CYII=",
    # corn.png
        "iVBORw0KGgoAAAANSUhEUgAAAEgAAABICAMAAABiM0N1AAADAFBMVEVHcEw9OQp4bxNpYBEXIwsAAAATIQtShh80NAB1iyoHDwddeRxhWRAaGASAgB0NGAdwaRIAAAAjORIAAAAIDQRDPgwZKw0CAwEAAABLRgwAAAAzThteVxEIEAM2MgkfNREqSBYvUBV9cRft2yQIDQQyLgkfHQX76SttZRIAAAAAAAAAAAAAAAAgHgUAAAAdMg8kQRMVIwsnRBViWhEAAAAAAAAyLgkbLg4AAAAAAABiWhFOgCcxVhsRHQkdOhEjPRQvURgAAAAvUBg+ayIxVhotTBgmRBQ2YB0eNRBpYRIoShsmIwZrZBIfMxA5Yx8AAABOSQ5BbyAMFAZhWxF7cRMlQRNKRQwiOxENFgcUIgodMhCAbRIUIgokIgbw3ylqZBIpRRUsSRYWJgwJEAUrSBVcnjE+Whj86itcnjIAAAArShVcnjFzaRMAAABcnzF6bhdwaRRcnjA6Yh1GQQxQiitbnzMAAAACAgD86isAAADPwCQAAACxzDP86isAAABcnjECAwEOEQQBAQAECAIKDQMmLAuYrywoRRYhJgoGBQGvyjIJCAERDwP15CoGCgNfbRsNDALh0Sb55yqTqiofJAlOSA1OhyorKAekvi87RBGajxouNQ2rxTE7Zh9ZmS8OGAccGgWdti1hcBxkcx2KgBeQhhmowjAlQBQ2XB1MVxYjIAYqSRY9aSHYySX45iqrnx3y5CqPpSkWJgxXlS7v3imNoimpwjFDTRPRwiNYZhkXGgcxOA4THwmEmCZ7jiMxLghBPQs5QhBqeh+mmhxpeR5aaBo3PxAVEwRFTxSvoh5VUQ80WRsuTxkQHAlaZxoQEwWDsTBzahS4yi5cli1TjyxVZxr76StkXRFIfCYnJAfAvCWAdxbu3SlLRg0cIQg1QhElKgu4qx9RiyvKxCZufiCiuy+uyTIYFgRzhCFjXBHi0yd4bxRtZRO9ryBZUw/BsyEiOhJWYhdHeSYnRBVCcSM0PA9Wky7m1ic3Xx2CeRaUihl1hyIaLQ5HUhUbHwjKuyIczocLAAAAfHRSTlMA5TWHCMPtAQQGDQyf+wj5V1lM8/vd7fEZ0T4gpiPsuFEYFQ798Po7gctHoEn5+leG03yZhzDv3Ezily6C4iymiJSqYpuxcT3agSb3cNExOcs3+5gb09Nb6fjfDuj4xnO0Rub8PNtexWHqa/pQ2YIsZMhz+5AtEvnyt/RvCh2IGAAAAy1JREFUWMPtl3VYU1EchgciII2AgICAhN3d3d3d3d27393mBowYIF0CgmIBCooFiN1id3d3991gj2NjcLj7d++/57nvc+I7v/O7HI4WLVq0SBnsaFNFx76Rrqaecv6QIWja0kwTzzge8qLvpyeH+QGmjhVYewzG4CUlY0d0BNCrN1uRBRLSqEKupG+GYGhVdqJBeEP9J+CmGJ4WrEQmeE4psns//EwUxl3065OJeuB2EREV8AqwN5QPT3CHPukeXaeUiBZDZ1TB6ORJgDmZyMwfqcqm1/6oIttyV3NkQ0K4STZIVhZRu5/Cw43DMZyI+EwJehIGG5vXqJhSE4LGunGcIQmns9GVTFShDg6piKhbL6hpU3n4RNPecCYOQITqlBi2ZeMjTdNbSY+NY2yK9cWJ3iN+LSO6BIkeoak6goJVPQ9X4wMt5QwakqZbB2Gqort4J/PQp9GMVKQbpLq4GwLegwJROCSuxLVNIH6rJLqMFLqQDLQjvrr9kfC16JFd3JgpF8VhBHG9M/PA/h2Kogu0At5x04mnNM8TeQEKonPhW095p3hv2XhNGgF6CnkJ1jVFmLxUpp04KYQcXkYc45pLXuFm++OHTBN8/hjzPf/opnUHkwKPh/IAyZYvs5aQm+Yv+ivVXBUDoetCuHKyHokY1bcFBuSmasupgO9+4EXt5BZl+z7g1+Iy1O9qK5kHKcqLq8pPPvgLyZ+4VcvwJ4dbLIkiSGYSepauAH7HctUQewCrhxF5nOaAn8tVj+8uuLcl8PSbAZ9Ebkn47kOb0j2VrfA5i1sykULUK82jZwvcidqTu6FE01k0KE1kWL7wPoiOeKkXecG69Fga2jWxbFy+LiMTHVZ7dPlwIoyAUe1aVkB+oJol+qAiebz1LGsAwiRfjUUMNZkdE4UUIxLCoYxdU/MWEO95ouzZCesy919GHXiIeawk2oQ+LFq5yrbYWzQKITyBC5um0G44+IqVKTIU3dn1qUaj4ffsfyG5B3MHdiKO8UggJkcWhMhAIQZ2Y9/Nj5cwz0DMrigf5gmo1FeTH4wBQ+ILLmGl9gYczTDu1LlLx9attD+RWrSUmX/GoXyvPJzVfwAAAABJRU5ErkJggg==",
    # lemon.png
        "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",
    # lime.png
        "iVBORw0KGgoAAAANSUhEUgAAAEgAAABICAMAAABiM0N1AAADAFBMVEVHcEwAAACZzDMAAAAAAACwyzWxzDMAAAAAAAAAAACzzDMAAACxyzQAAQAAAAAAAAAAAAAAAABldR0AAAAAAACvzzAAAAAAAAAEBgKxyzSyyzSvyzOqxjmxyzQAAACxzDMAAAAAAAAAAAANEgUAAAAAAQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAOEQQAAAAAAAACAwEAAACnxzMAAAAhJwkDBAGwyzSmxjKtyjIAAACdwDOlxTIFCgOavzMJDgQAAAAEBwIAAACvzDMFCQIPGQgAAAAQFwcLFQaxzDMAAAAAAAAAAAAAAAANGAcQHAgAAAALEwawzDMAAAAGCwQIDgQAAAALEwYrShciMQ4LFwajxDM1QhCxzDM8RhEXIwkAAACtyjMAzDFcnjEAAACxzDNdnjEBAgCwyzOKtzJcnzGbwDN5rjGoxzJenzFfoDFppTFgoTGlxTKfwjKryTKAsTKixDKBsjKSvDJppjFjojF4rTGZvzJlozEAAACwzDMGCAJ1rDGpyDNbnTBspzEDBAFxqTGDszKdwTJ2rDGPuTJioTFMhClOhyorShf///88RxHy9+49aSFamjAJEAV5jySMuDJ8nSl9sDJuqDEQFgY0WhyHtTKgwzNsfh9XlS5kcxxVYhirxTE0PQ+PujJtiCRwgyFGVBXG3bdKfid5jCNxqjFFdiWtyjMlPxSItjKeti18slmWvjI7ZiCoy5K816pgcR2jyYvJ37suTxgICwNqeh+FtDI6ZB8XGwcxOw9HeiUsTBipwjAxVBogNxEnQxVBShN1lyiYvjJ4nyyJniiLuDJDdCSAlSWYryxJfSczWBtUkC0nNA4bIAhCcSMQHAkbLw8wUxpKgChecR1Xli6EtDI4QBCLrS6As15Vki05QhBvqDKJnid5r1V1rVEdMg+hui5EThR+sTHt9OhlpDd0rE9OWheuz5i31KRhoTdkozubw4CNu2+Ht2fc6tP8/fvV5srg7dgaLQ4yVhtebRsWJgwQGwg/bCJRXRcqSBZHcEw9achLAAABAHRSTlMAzQU0F0SzAv0BKBKZuwjciOv+cgwQOgr5dlnMEoDA/VoEXvZQ4RxoMcrUBbP7D33vQf2E9fle6tCY9ubp9sef/PAjkPPi5Ibz1pGqivf42PmSR/X8+fL5jVn1fOKh3aXo//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////8AsDngkAAAA3tJREFUWMPtllVUW0EQhqG0TWiLVKHeUnd3d3f3nv03CQmEkAQpVrRIcagbdXd3d3d3d3c73RsvDzH61vxP9+45892Zf2Z3r52dTTbZZNP/ILd/xBkRNirXv+DUqIDtI4sXzTloKML3rRR1LZAvh5zyFZB6nUinedbPmydHoGHAQsJJMCGhaeMcmDUa2yYQjXwDWlhtVm4hbvgSnQTBza00qwtQSM8h42b607JWmdUZOBWkySZ6tZyqVbKEpWbl52M69eQgAeuUK2cFxsZP5UB+CWNLl7IIVBGYT6nSOzJkdXwol5bUn0pCaAJ59mR4v/YWgDoAc6nCT8YQzzd+SPtM/Kho3HKq9Nm8ZW1EiAVmtQZmB6ot2vBpS8rmICVXaBwNFrxaQohsstlmtQROhmo6tvZj2psF1Nv37esIuk6z5hPQxCyzHPnAFG3rX6a9ix5PvQRP3xOFKEi7Ko5vZcZkucEAxHonoRLyIGUDCaaxBsO1g01WeRNzzUBH9RFezGlyP2UjEcu9pfrlCDrvXDsH42PEQId1ARMjVSO15BZhzQvWLYvjRLuBKkZBPCEwSRfBOa01WTlLt+xJF7PvlTNeW10gS+vrNBH1MojWngkz6VXEDER/4yAn4NBUTQVspvW+hIr8BarUAukiYdj6wahqHNQAqBWnDo3lnNbrCD3O4BFyxsHla/xBzsZB9Vj1y1QFyUSc04YdpHKJN6WzhdhKVqCaiUHiVQIayn3YZlXonVa3cLzqQNkUhv2EDEF3UyNZh6VUKFBMJlMDp1XDyYHmpSLsDCFRA1DMFKh2QaDRMUUIpZGCv0B3GefeLoSns+cLcHE0uUs8WEruk2h2kFRCHy0W4mIie47qiMJm7NuajITHayi9bsCRSdbMDYdwbwb3shOdnM04AYrYc6SY1GX7FH7RoVLxRNnygJuL5rOZf5iogia5w8O8G8kFyGRxwl27f33L2p714s55jnxgjzq5Ob3Qw9HMG8AJwgN7v8dAp/BLM25rijzbG9WLmHvg8lz5yEzPSPq5P/n3qoNf05dG6cw63Rd9KltwCThUA37szCDZNCeZD/vcFt1LvCpsxjMP7okywCQltwW/p7Old24Nj+rMnW1ftq5fkXhl6YkZq6azVycHq34Eqrq6wEAF21iHUalyRdcxZbrZ25dpVrgYz/afbpNNNv1P+gM7ktPK16/z9gAAAABJRU5ErkJggg==",
    # orange.png
        "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",
]

GAME_MOVE_COUNT = 15
DROP_TIME_ANIM = 250


class Application(tk.Tk):
    def __init__(self):
        super().__init__()

        self.title("Гра із фігурою")
        self.geometry("600x400")
        self.resizable(False, False)
        self.minsize(400, 300)

        container = tk.Frame(self)
        container.pack(side="top", fill="both", expand=True)
        container.grid_rowconfigure(0, weight=1)
        container.grid_columnconfigure(0, weight=1)

        self.frames = {}

        for F in (MainMenu, GameFrame):
            frame = F(container, self)
            self.frames[F] = frame
            frame.grid(row=0, column=0, sticky="nsew")

        self.show_frame(MainMenu)

    def show_frame(self, frame_class):
        frame = self.frames[frame_class]
        frame.tkraise()


class MainMenu(tk.Frame):
    def __init__(self, parent, controller):
        super().__init__(parent)
        self.controller = controller

        sound_player.play_music()

        self.sound_button_var = tk.StringVar(value="🔊")

        def toggle_sound():
            sound_player.toggle_sound()
            self.sound_button_var.set("🔊" if sound_player.enabled else "🔇")

        sound_btn = tk.Button(self, textvariable=self.sound_button_var,
                              font=("Helvetica", 16), command=toggle_sound,
                              bg=COLORS["MainMenu"]["bt_play"], fg=COLORS["MainMenu"]["text"],
                              bd=0, highlightthickness=0)
        sound_btn.place(relx=1.0, rely=0.0, anchor="ne", x=-10, y=10)

        self.configure(bg=COLORS["MainMenu"]["bg"])

        self.grid_rowconfigure(0, weight=1)
        self.grid_rowconfigure(4, weight=1)
        self.grid_columnconfigure(0, weight=1)

        title_font = tkfont.Font(family="Helvetica", size=36, weight="bold")
        title = tk.Label(self, text="Фігура на сітці", font=title_font, bg=COLORS["MainMenu"]["bg"], fg=COLORS["MainMenu"]["text"])
        title.grid(row=1, column=0, pady=(20, 40))

        btn_font = tkfont.Font(family="Helvetica", size=16)
        play_btn = tk.Button(self, text="Грати", font=btn_font, bg=COLORS["MainMenu"]["bt_play"], fg=COLORS["MainMenu"]["text"],
                             width=15, height=2, bd=0, highlightthickness=0,
                             command=lambda: controller.show_frame(GameFrame))
        play_btn.grid(row=2, column=0, pady=10)

        exit_btn = tk.Button(self, text="Вийти", font=btn_font, bg=COLORS["MainMenu"]["bt_exit"], fg=COLORS["MainMenu"]["text"],
                             width=15, height=2, bd=0, highlightthickness=0,
                             command=self.quit)
        exit_btn.grid(row=3, column=0, pady=10)

    def quit(self):
        self.controller.destroy()

class GameFrame(tk.Frame):
    def __init__(self, parent, controller):
        super().__init__(parent)

        self.score_var = tk.StringVar(value="0")
        self.move_var = tk.StringVar(value="0")
        self.mouse_coord_var = tk.StringVar(value="x: 0, y: 0\ncol: 0, row: 0")
        self.sound_button_var = tk.StringVar(value="🔊")
        self.highscore_var = tk.StringVar(value=str(GameCanvas.load_highscore()))
        self.timer_var = tk.StringVar(value="00:00")

        self.start_time = time.time()
        self.is_timer_running = False
        self.update_timer()

        sound_player.play_music()

        left_panel = tk.Frame(self, bg=COLORS["GameFrame"]["left_panel"])
        left_panel.pack(side="left", fill="both")
        left_panel.grid_rowconfigure(0, weight=1)
        left_panel.grid_columnconfigure(0, weight=1)

        menu_btn = tk.Button(left_panel, text="← До меню", bg=COLORS["GameFrame"]["bt_menu_bg"], fg=COLORS["GameFrame"]["bt_menu_text"],
                             command=lambda: controller.show_frame(MainMenu))
        menu_btn.pack(pady=5, padx=5, fill="x")

        score_frame = tk.Frame(left_panel, bg=COLORS["GameFrame"]["score_bg"], bd=2, relief="groove")
        score_frame.pack(pady=5, padx=5, fill="x")
        lb_score_title = tk.Label(score_frame, text="SCORE",
                                  bg=COLORS["GameFrame"]["score_bg"], fg=COLORS["GameFrame"]["score_text"])
        lb_score_title.pack()
        lb_score_value = tk.Label(score_frame, textvariable=self.score_var,
                                  bg=COLORS["GameFrame"]["score_bg"], fg=COLORS["GameFrame"]["score_text"])
        lb_score_value.pack()

        # Highscore display
        highscore_frame = tk.Frame(left_panel, bg=COLORS["GameFrame"]["score_bg"], bd=2, relief="groove")
        highscore_frame.pack(pady=5, padx=5, fill="x")
        lb_highscore_title = tk.Label(highscore_frame, text="RECORD",
                                      bg=COLORS["GameFrame"]["score_bg"], fg=COLORS["GameFrame"]["score_text"])
        lb_highscore_title.pack()
        lb_highscore_value = tk.Label(highscore_frame, textvariable=self.highscore_var,
                                      bg=COLORS["GameFrame"]["score_bg"], fg=COLORS["GameFrame"]["score_text"])
        lb_highscore_value.pack()

        move_frame = tk.Frame(left_panel, bg=COLORS["GameFrame"]["move_bg"], bd=2, relief="groove")
        move_frame.pack(pady=5, padx=5, fill="x")
        lb_move_title = tk.Label(move_frame, text="MOVES",
                                 bg=COLORS["GameFrame"]["move_bg"], fg=COLORS["GameFrame"]["move_text"])
        lb_move_title.pack()
        lb_move_value = tk.Label(move_frame, textvariable=self.move_var,
                                 bg=COLORS["GameFrame"]["move_bg"], fg=COLORS["GameFrame"]["move_text"])
        lb_move_value.pack()

        timer_frame = tk.Frame(left_panel, bg=COLORS["GameFrame"]["timer_bg"], bd=2, relief="groove")
        timer_frame.pack(pady=5, padx=5, fill="x")
        lb_timer_title = tk.Label(timer_frame, bg=COLORS["GameFrame"]["timer_bg"], text="TIMER", fg=COLORS["GameFrame"]["timer_text"])
        lb_timer_title.pack()
        lb_timer_value = tk.Label(timer_frame, bg=COLORS["GameFrame"]["timer_bg"], textvariable=self.timer_var, fg=COLORS["GameFrame"]["timer_text"])
        lb_timer_value.pack()

        bt_restart = tk.Button(
            left_panel, text="⟳",
            bg=COLORS["GameFrame"]["bt_restart_bg"], fg=COLORS["GameFrame"]["bt_restart_text"])
        bt_restart.pack(pady=5, padx=5, fill="x")

        def toggle_sound():
            sound_player.toggle_sound()
            self.sound_button_var.set("🔊" if sound_player.enabled else "🔇")

        sound_btn = tk.Button(left_panel, textvariable=self.sound_button_var, command=toggle_sound,
                              font=("Helvetica", 12), bg=COLORS["GameFrame"]["bt_menu_bg"], fg=COLORS["GameFrame"]["bt_menu_text"],
                              bd=2, relief="groove")
        sound_btn.pack(pady=5, padx=5, fill="x")

        lb_coord = tk.Label(left_panel, textvariable=self.mouse_coord_var, width=15, anchor="center",
                            bg=COLORS["GameFrame"]["coord_bg"], fg=COLORS["GameFrame"]["coord_text"])
        lb_coord.pack(side="bottom")

        game_container = tk.Frame(self, bg=COLORS["GameFrame"]["game_container_bg"])
        game_container.pack(side="left", fill="both", expand=True)
        game_container.grid_rowconfigure(0, weight=1)
        game_container.grid_columnconfigure(0, weight=1)

        emoji = []
        for base64_string in EMOJI_BASE64:
            emoji.append(self.get_image_from_base64(base64_string))

        self.canvas = GameCanvas(
            game_container, emoji, score_var=self.score_var, move_var=self.move_var,
            field_size=GAME_FIELD_SIZE, padding=CANVAS_PADDING,
            bg = COLORS["GameFrame"]["canvas_bg"],
            highlightbackground = COLORS["GameFrame"]["canvas_bd"],
            highlightthickness=1,
        )
        self.canvas.grid(row=0, column=0, padx=CANVAS_PADDING, pady=CANVAS_PADDING)

        self.canvas.bind("<Motion>", lambda event: self.mouse_coord_var.set(
            f"x: {event.x}, y: {event.y}\ncol: {min(GAME_FIELD_SIZE[0], event.x // self.canvas.block_size + 1)}, row: {min(GAME_FIELD_SIZE[1], event.y // self.canvas.block_size + 1)}"
        ))

        bt_restart.config(command=self.restart_game)

    def update_timer(self):
        elapsed_time = int(time.time() - self.start_time)
        minutes = elapsed_time // 60
        seconds = elapsed_time % 60
        self.timer_var.set(f"{minutes:02d}:{seconds:02d}")

        self.after(1000, self.update_timer)

    def restart_game(self):
        self.score_var.set("0")
        self.move_var.set(str(GAME_MOVE_COUNT))
        self.mouse_coord_var.set("x: 0, y: 0\ncol: 0, row: 0")

        self.start_time = time.time()
        self.update_timer() 

        self.canvas.restart_game()

    @staticmethod
    def get_image_from_base64(base64_string):
        img_data = base64.b64decode(base64_string)
        img = PhotoImage(data=img_data)
        return img


class GameCanvas(tk.Canvas):
    def __init__(self, parent, emoji: list, score_var=None, move_var=None, field_size=(10, 10), padding=0, **kwargs):
        super().__init__(parent, **kwargs)
        self.parent = parent
        self.original_emoji = emoji
        self.field_size = field_size
        self.block_size = 0
        self.padding = padding
        self.is_timer_running = False
        self.score_var = score_var
        self.move_var = move_var
        
        if self.move_var:
            self.move_var.set(str(GAME_MOVE_COUNT))

        self.score = 0
        self.moves_left = GAME_MOVE_COUNT
        self.selected_cells = []  
        self.is_animating = False
        self.is_game_over = False
        
        self.emoji = []
        self.field = []
        self.initialize_field()

        self.bind("<Configure>", self.handle_resize)
        self.bind("<Button-1>", self.handle_click)

        self.update_field()

    def initialize_field(self):
        self.field = [[random.randint(0, len(self.original_emoji) - 1)
                       for _ in range(self.field_size[1])]
                      for _ in range(self.field_size[0])]


        for i in range(self.field_size[0]):
            for j in range(self.field_size[1]):
                if j >= 2:
                    while (self.field[i][j] == self.field[i][j - 1] == self.field[i][j - 2]):
                        self.field[i][j] = random.randint(0, len(self.original_emoji) - 1)

                if i >= 2:
                    while (self.field[i][j] == self.field[i - 1][j] == self.field[i - 2][j]):
                        self.field[i][j] = random.randint(0, len(self.original_emoji) - 1)

    def resize_images(self):

        self.emoji = []

        original_size = 88

        for img in self.original_emoji:
            # Calculate approximate factors
            subsample_factor = max(1, original_size // self.block_size)
            zoom_factor = max(1, self.block_size // (original_size // subsample_factor))

            resized_img = img.subsample(subsample_factor).zoom(zoom_factor)
            self.emoji.append(resized_img)
    
    def update_field(self):
        self.delete("all")

        width = self.parent.winfo_width() - self.padding * 2
        height = self.parent.winfo_height() - self.padding * 2

        max_block_width = width // self.field_size[0]
        max_block_height = height // self.field_size[1]
        self.block_size = min(max_block_width, max_block_height)

        canvas_width = self.block_size * self.field_size[0]
        canvas_height = self.block_size * self.field_size[1]
        self.config(width=canvas_width, height=canvas_height)
        self.resize_images()

        for row in range(self.field_size[0]):
            for col in range(self.field_size[1]):
                x = col * self.block_size + self.block_size / 2
                y = row * self.block_size + self.block_size / 2

                img_id = self.field[row][col]

                if img_id is not None:
                    self.create_image(x, y, image=self.emoji[img_id])

        self.draw_selected_cell()

    def handle_resize(self, event):
        self.update_field()

    def handle_click(self, event):
        if self.is_animating or self.is_game_over:
            return

        sound_player.play("sound/click.mp3")

        col = event.x // self.block_size
        row = event.y // self.block_size

        if 0 <= row < self.field_size[0] and 0 <= col < self.field_size[1]:
            clicked_cell = (row, col)

            if clicked_cell in self.selected_cells:
                self.selected_cells.remove(clicked_cell)
            elif len(self.selected_cells) < 2:
                self.selected_cells.append(clicked_cell)
            else:
                return

            self.update_field()  

            if len(self.selected_cells) == 2:
                row1, col1 = self.selected_cells[0]
                row2, col2 = self.selected_cells[1]

                if ((abs(row1 - row2) == 1 and col1 == col2) or
                        (abs(col1 - col2) == 1 and row1 == row2)):
                    self.make_move(row1, col1, row2, col2)
                else:
                    self.selected_cells.clear()
                    self.update_field()
                    
    def draw_selected_cell(self):
        self.delete("selected_cell_highlight")
        for row, col in self.selected_cells:
            x1 = col * self.block_size
            y1 = row * self.block_size
            x2 = x1 + self.block_size
            y2 = y1 + self.block_size
            self.create_rectangle(x1, y1, x2, y2, outline=COLORS["GameFrame"]["selected_cell_bg"], width=3, tags="selected_cell_highlight")

    def clear_selected_cell(self):
        self.delete("selected_cell_highlight")  
        
    def make_move(self, row1, col1, row2, col2):
        self.field[row1][col1], self.field[row2][col2] = self.field[row2][col2], self.field[row1][col1]

        matches = self.find_matches()

        if not matches:
            self.field[row1][col1], self.field[row2][col2] = self.field[row2][col2], self.field[row1][col1]
            self.selected_cells.clear() 
            self.update_field()
            return

        self.moves_left -= 1
        self.selected_cells.clear() 

        self.process_matches(matches)

    def find_matches(self):
        matches = []
        matched = set()

        for row in range(self.field_size[0]):
            col = 0
            while col < self.field_size[1] - 2:
                if (self.field[row][col] is not None and
                        self.field[row][col] == self.field[row][col + 1] == self.field[row][col + 2]):
                    match_length = 3
                    while (col + match_length < self.field_size[1] and
                        self.field[row][col] == self.field[row][col + match_length]):
                        match_length += 1

                    if match_length >= 5:
                        matches.append(("all", None))  
                        return matches  
                    elif match_length == 4:
                        matches.append(("row", row))
                        for i in range(self.field_size[1]):
                            matched.add((row, i))
                        col = self.field_size[1]
                    else:
                        for i in range(match_length):
                            if (row, col + i) not in matched:
                                matches.append(("cell", (row, col + i)))
                                matched.add((row, col + i))
                        col += match_length
                else:
                    col += 1

        for col in range(self.field_size[1]):
            row = 0
            while row < self.field_size[0] - 2:
                if (self.field[row][col] is not None and
                        self.field[row][col] == self.field[row + 1][col] == self.field[row + 2][col]):
                    match_length = 3
                    while (row + match_length < self.field_size[0] and
                        self.field[row][col] == self.field[row + match_length][col]):
                        match_length += 1

                    if match_length >= 5:
                        matches.append(("all", None))  
                        return matches  
                    elif match_length == 4:
                        matches.append(("col", col)) 
                        for i in range(self.field_size[0]):
                            matched.add((i, col))
                        row = self.field_size[0]
                    else:
                        for i in range(match_length):
                            if (row + i, col) not in matched:
                                matches.append(("cell", (row + i, col)))
                                matched.add((row + i, col))
                        row += match_length
                else:
                    row += 1
                    

        for row in range(self.field_size[0] - 1):
            for col in range(self.field_size[1] - 1):
                if (self.field[row][col] == self.field[row + 1][col] ==
                        self.field[row][col + 1] == self.field[row + 1][col + 1] and
                        self.field[row][col] is not None):
                    matches.append(("square", (row, col)))

        return matches

    def process_matches(self, matches):
        self.is_animating = True
        sound_player.play("sound/match.mp3")

        cells_to_remove = set()
        if ("all", None) in matches:
            self.score += self.field_size[0] * self.field_size[1] * 20
            for r in range(self.field_size[0]):
                for c in range(self.field_size[1]):
                    cells_to_remove.add((r, c))
        else:
            for match_type, coord in matches:
                if match_type == "row":
                    self.score += self.field_size[1] * 10
                    for i in range(self.field_size[1]):
                        cells_to_remove.add((coord, i))
                elif match_type == "col":
                    self.score += self.field_size[0] * 10
                    for i in range(self.field_size[0]):
                        cells_to_remove.add((i, coord))
                elif match_type == "square":
                    self.score += 50
                    row, col = coord

                    for r in range(max(0, row - 1), min(self.field_size[0], row + 3)):
                        for c in range(max(0, col - 1), min(self.field_size[1], col + 3)):
                            cells_to_remove.add((r, c))
                elif match_type == "cell":
                    self.score += 10
                    cells_to_remove.add(coord)

        if self.score_var:
            self.score_var.set(str(self.score))

        for row, col in cells_to_remove:
            self.field[row][col] = None

        self.update_field()
        self.after(DROP_TIME_ANIM, self.drop_candies)
        
    def drop_candies(self):
        dropped = False

        for col in range(self.field_size[1]):
            for row in range(self.field_size[0] - 1, 0, -1):
                if self.field[row][col] is None:
                    for check_row in range(row - 1, -1, -1):
                        if self.field[check_row][col] is not None:
                            self.field[row][col] = self.field[check_row][col]
                            self.field[check_row][col] = None
                            dropped = True
                            break

        for row in range(self.field_size[0]):
            for col in range(self.field_size[1]):
                if self.field[row][col] is None:
                    self.field[row][col] = random.randint(0, len(self.original_emoji) - 1)
                    dropped = True

        self.update_field()

        new_matches = self.find_matches()

        if new_matches:
            self.after(DROP_TIME_ANIM, lambda: self.process_matches(new_matches))
        else:
            self.is_animating = False

            if self.move_var:
                self.move_var.set(str(self.moves_left))

            if self.moves_left <= 0:
                self.game_over()

    @staticmethod
    def save_highscore(score, filename="highscore.json"):
        try:
            data = {
                "highscore": score,
                "date": datetime.now().strftime("%Y-%m-%d")
            }
            with open(filename, "w") as f:
                json.dump(data, f)
        except Exception as e:
            print(f"Помилка при збереженні рекорду: {e}")

    @staticmethod
    def load_highscore(filename="highscore.json"):
        import json
        try:
            with open(filename, "r") as f:
                data = json.load(f)
                return data.get("highscore", 0)
        except Exception:
            return 0
    
        
    def game_over(self):
        self.is_game_over = True

        sound_player.play("sound/gameover.mp3")

        prev_highscore = self.load_highscore()
        if self.score > prev_highscore:
            self.save_highscore(self.score)
            message = f"🎉 Новий рекорд!\nВаш рахунок: {self.score}"
        else:
            message = f"Добре зіграно!\nВаш рахунок: {self.score}"

        messagebox.showinfo("Кінець гри", message)
        self.ask_restart()

        
    def ask_restart(self):
        restart = messagebox.askyesno("Нова гра", "Бажаєте розпочати нову гру?")
        if restart:
            self.restart_game()


    def restart_game(self):
        self.score = 0  
        self.moves_left = GAME_MOVE_COUNT 
        self.field = []  
        self.initialize_field()  
        self.update_field() 
        self.selected_cells = []  
        self.is_game_over = False 
        
        if self.score_var:
            self.score_var.set("0")
        if self.move_var:
            self.move_var.set(str(GAME_MOVE_COUNT))


class SoundPlayer:
    def __init__(self, volume=1.0):
        self.volume = volume
        self.enabled = True

    def play(self, file):
        if not self.enabled:
            return
        try:
            sound = pygame.mixer.Sound(file)
            sound.set_volume(self.volume)
            sound.play()
        except Exception as e:
            print(f"Помилка при відтворенні {file}: {e}")

    def mute(self):
        self.enabled = False
        pygame.mixer.music.pause()

    def unmute(self):
        self.enabled = True
        pygame.mixer.music.unpause()

    def set_volume(self, volume: float):
        self.volume = max(0.0, min(volume, 1.0))

    def play_music(self, music_file="sound/background_music.mp3", volume=0.3):
        if self.enabled and not pygame.mixer.music.get_busy():
            try:
                pygame.mixer.music.load(music_file)
                pygame.mixer.music.set_volume(volume)
                pygame.mixer.music.play(-1)
            except Exception as e:
                print(f"Не вдалося запустити музику: {e}")

    def toggle_sound(self):
        if self.enabled:
            self.mute()
        else:
            self.unmute()


sound_player = SoundPlayer(volume=0.5)


if __name__ == "__main__":
    app = Application()
    app.mainloop()