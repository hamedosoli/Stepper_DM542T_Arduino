import tkinter as tk
import serial

class SerialCommunicationApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Serial Communication")
        self.com_port_label = tk.Label(root, text="COM Port:")
        self.com_port_label.pack()
        self.com_port_entry = tk.Entry(root)
        self.com_port_entry.pack()
        self.baud_rate_label = tk.Label(root, text="Baud Rate:")
        self.baud_rate_label.pack()
        self.baud_rate_entry = tk.Entry(root)
        self.baud_rate_entry.pack()
        self.connect_button = tk.Button(root, text="Connect", command=self.connect)
        self.connect_button.pack()

        self.send_label = tk.Label(root, text="Send Data:")
        self.send_label.pack()
        self.send_entry = tk.Entry(root)
        self.send_entry.pack()
        self.send_button = tk.Button(root, text="Send", command=self.send_data)
        self.send_button.pack()

        self.receive_label = tk.Label(root, text="Received Data:")
        self.receive_label.pack()
        self.receive_text = tk.Text(root, height=5, width=30)
        self.receive_text.pack()

        self.serial = None

    def connect(self):
        com_port = self.com_port_entry.get()
        baud_rate = int(self.baud_rate_entry.get())
        try:
            self.serial = serial.Serial(com_port, baud_rate)
        except serial.SerialException as e:
            self.receive_text.insert(tk.END, f"Error: {e}\n")

    def send_data(self):
        if self.serial is not None:
            data_to_send = self.send_entry.get()
            self.serial.write(data_to_send.encode())
            received_data = self.serial.readline().decode()
            self.receive_text.insert(tk.END, f"Sent: {data_to_send}\nReceived: {received_data}\n")

if __name__ == "__main__":
    root = tk.Tk()
    app = SerialCommunicationApp(root)
    root.mainloop()
