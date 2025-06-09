import cv2
import cv2.aruco as aruco
import serial
import time

print("OpenCV version:", cv2.__version__)

ser = serial.Serial('/dev/ttyUSB0', 9600)
time.sleep(2)

cap = cv2.VideoCapture(0)

aruco_dict = aruco.getPredefinedDictionary(aruco.DICT_4X4_50)
parameters = aruco.DetectorParameters()
detector = aruco.ArucoDetector(aruco_dict, parameters)

while True:
    ret, frame = cap.read()
    if not ret:
        print("Image capture failed")
        break

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    corners, ids, _ = detector.detectMarkers(gray)

    if ids is not None and len(ids) > 0:
        aruco.drawDetectedMarkers(frame, corners, ids)
        message = b'Y'
        cv2.putText(frame, "TAG DETECTED", (40, 60), cv2.FONT_HERSHEY_SIMPLEX, 1.2, (0, 255, 0), 3)
    else:
        message = b'N'
        cv2.putText(frame, "ALERT: TAG LOST", (40, 60), cv2.FONT_HERSHEY_SIMPLEX, 1.2, (0, 0, 255), 3)

    ser.write(message)
    print(f"Sent: {message.decode()}")
    time.sleep(0.05)

    if ser.in_waiting:
        response = ser.readline().decode().strip()
        print(f"Echo: {response}")
        if response == message.decode():
            print("Echo match\n")
        else:
            print("Echo mismatch\n")
    else:
        print("No echo received\n")

    cv2.imshow("ArUco Tag Tracking", frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
ser.close()
cv2.destroyAllWindows()