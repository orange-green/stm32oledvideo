import time

import cv2
import serial
from PIL import Image

COM_PORT = "COM3"
WIDTH = 128
HEIGHT = 64
VIDEO_PATH = "video/kun.mp4"
THRESHOLD = 128
SKIP_STEP = 3
# 不再依靠SEND_DELAY延时，删掉它


def frame2ssd1306_bin(cv_frame):
    img = Image.fromarray(cv_frame).convert("L")
    img = img.resize((WIDTH, HEIGHT), Image.Resampling.LANCZOS)
    bw = img.point(lambda p: 255 if p > THRESHOLD else 0).convert("1")

    buf = bytearray([0] * 1024)
    for page in range(8):
        for x in range(WIDTH):
            byte_val = 0
            for bit in range(8):
                y = page * 8 + bit
                if bw.getpixel((x, y)):
                    byte_val |= 1 << bit
            buf[page * 128 + x] = byte_val
    return buf


if __name__ == "__main__":
    ser = serial.Serial(COM_PORT, 115200, timeout=0.5)
    cap = cv2.VideoCapture(VIDEO_PATH)
    if not cap.isOpened():
        print("视频打开失败！")
        exit()

    frame_cnt = 0
    print("应答同步模式：AA 55 + 1024data + BB CC，等待STM32返回OK")
    try:
        while True:
            ret, frame = cap.read()
            if not ret:
                # 视频播放完毕，从头循环
                cap.set(cv2.CAP_PROP_POS_FRAMES, 0)
                frame_cnt = 0
                continue
            frame_cnt += 1
            if frame_cnt % SKIP_STEP == 0:
                gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
                pix_data = frame2ssd1306_bin(gray)
                packet = bytearray([0xAA, 0x55]) + pix_data + bytearray([0xBB, 0xCC])
                ser.write(packet)
                print(f"发送帧 {frame_cnt}，等待ACK...")

                # 等待 STM32 返回 b"OK"
                ack = ser.read(2)
                if ack == b"OK":
                    print("收到ACK，准备下一帧")
                else:
                    print(f"ACK异常，收到：{ack}，重试等待")
                    time.sleep(0.05)
    except KeyboardInterrupt:
        print("\n退出程序")
    finally:
        cap.release()
        ser.close()
