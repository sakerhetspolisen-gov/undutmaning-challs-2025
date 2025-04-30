import socket
import re
import math
import argparse
try:
    import plotly.graph_objects as go
    import plotly.offline as pyo
    plot = True
except ImportError: 
    print("- Plotting unavailable")
    plot = False

def connect_to_server(ip, port):
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect((ip, port))
        print(f"Ansluten till {ip}:{port}")
        return s
    except Exception as e:
        print(f"Fel vid anslutning: {e}")
        return None


class LineReader:
    def __init__(self, socket):
        self.socket = socket
        self.buffer = ""
        
    def get_line(self):
        while "\n" not in self.buffer:  # Fortsätt läsa tills vi hittar en radbrytning
            data = self.socket.recv(4096).decode('utf-8')  # Läs data från JOPPE
            if not data:
                if self.buffer:  # Om det finns kvarvarande data i bufferten
                    line = self.buffer
                    self.buffer = ""
                    return line.strip()
                return None  # Ingen mer data att läsa
            self.buffer += data

        # Dela bufferten vid radbrytningar
        line, self.buffer = self.buffer.split("\n", 1)
        return line.strip()


class SpacecraftController:
    def __init__(self, s):
        self.x_hist = []                        # X-koordinat-historik (för plottning)
        self.y_hist = []                        # Y-koordinat-historik (för plottning)
        self.z_hist = []                        # Z-koordinat-historik (för plottning)
        self.socket = s
        self.line_reader = LineReader(self.socket)
        self.position = [0.0, 0.0, 0.0]         # Aktuell position
        self.last_position_valid = False        # Is last position valid?
        self.last_position = self.position[:]   # För att beräkna hastighet
        self.velocity = [0.0, 0.0, 0.0]
        self.previous_velocity = self.velocity[:]
        self.motor_ran_ok = True
        self.motor = [None] * 6                 # Vilken motor påverkar i vilken riktning [x+,x-,y+,y-,z+,z-]
        self.testing_motor = 0                  # Vilken motor håller vi på att undersöka?
        self.testing_motor_activated = False
        
    def read_data(self):
        while True:
            line = self.line_reader.get_line()
            if line is None:
                print("Ingen mer data att läsa.")
                break

            # Kolla om raden är i formatet [x,y,z] med flyttal
            if re.match(r'^\[\s*-?\d+(\.\d+)?\s*,\s*-?\d+(\.\d+)?\s*,\s*-?\d+(\.\d+)?\s*\]$', line):
                self.last_position = self.position[:]  # Spara den senaste positionen
                self.position = eval(line)  # Omvandla strängen till en lista
        
                if plot:
                    self.x_hist.append(self.position[0])
                    self.y_hist.append(self.position[1])
                    self.z_hist.append(self.position[2])

                self.velocity = [(self.position[i] - self.last_position[i]) for i in range(3)]

                print(f"[{self.position[0]}({self.velocity[0]:.2f}),{self.position[1]}({self.velocity[1]:.2f}),{self.position[2]}({self.velocity[2]:.2f})]")

                if(self.last_position_valid):
                    # Beräkna nuvarande hastighet
                    if self.testing_motor < 6:
                        if not self.determine_motor_effects():
                            break
                    else:
                        self.move_to_origin()   # Flytta mot origo
                else:
                    self.last_position_valid = True

            else:
                print(f"{line}")
                if line == "OK":
                    self.motor_ran_ok = True
                if line == "Kontakten med farkosten har förlorats!":
                    break

    def determine_motor_effects(self):
        if not self.testing_motor_activated:
            self.previous_velocity = self.velocity[:]
            self.testing_motor_activated = True
            self.send_motor_command(self.testing_motor,1)
            return True

        if not self.motor_ran_ok:
            # Vänta tills vi fått ok att motorn körts
            return True

         # Beräkna hastighetsförändringen för att avgöra motorpåverkan
        delta_velocity = [(self.velocity[i] - self.previous_velocity[i]) for i in range(3)]
        # print(f"Motor {self.testing_motor}: Förändring: {delta_velocity}")
        
        # Registrera motorpåverkan baserat på största hastighetsförändring
        if abs(delta_velocity[0]) > abs(delta_velocity[1]) and abs(delta_velocity[0]) > abs(delta_velocity[2]):
            if delta_velocity[0] > 0:
                print(f"Motor {self.testing_motor} identifierad som X+")
                self.motor[0] = self.testing_motor  # x+
            else:
                print(f"Motor {self.testing_motor} identifierad som X-")
                self.motor[1] = self.testing_motor  # x-
        elif abs(delta_velocity[1]) > abs(delta_velocity[0]) and abs(delta_velocity[1]) > abs(delta_velocity[2]):
            if delta_velocity[1] > 0:
                print(f"Motor {self.testing_motor} identifierad som Y+")
                self.motor[2] = self.testing_motor  # y+
            else:
                print(f"Motor {self.testing_motor} identifierad som Y-")
                self.motor[3] = self.testing_motor  # y-
        elif abs(delta_velocity[2]) > abs(delta_velocity[0]) and abs(delta_velocity[2]) > abs(delta_velocity[1]):
            if delta_velocity[2] > 0:
                print(f"Motor {self.testing_motor} identifierad som Z+")
                self.motor[4] = self.testing_motor  # z+
            else:
                print(f"Motor {self.testing_motor} identifierad som Z-")
                self.motor[5] = self.testing_motor  # z-


        self.testing_motor_activated = False
        self.testing_motor += 1      

        if self.testing_motor > 5:
            print(f"Motor index antas vara: {self.motor}")
            if any(m is None for m in self.motor):  
                print("Misslyckades med att identifiera motorernas orientering. Avbryter!")
                return False
        
        return True

    def send_motor_command(self, motor, duration):
        print(f"Skickar kommando: {motor}:{duration}")
        self.socket.sendall(f"{motor}:{duration}\n".encode('utf-8'))
        self.last_position_valid = False
        self.motor_ran_ok = False

    def move_to_origin(self):
        # Beräkna avståndet till origo
        distance = math.sqrt(sum(p ** 2 for p in self.position))
        print(f"Avstånd till origo: {distance:.2f}")

        # Beräkna riktning och hastighet för att röra mot origo
        if distance > 0.1:  # Om vi är längre än 0.1 enheter från origo
            if self.motor_ran_ok:
                motor, duration = self.calculate_motor_command(distance)
                if motor is not None:
                    if duration == 0:
                        duration = 1
                    self.send_motor_command(motor,duration)
            
    def calculate_motor_command(self,distance):
        # Säkerställ att vi inte rör oss iväg från origo

        # Hitta axeln längst från origo (0 = x, 1 = y, 2 = z)
        abs_position = [abs(self.position[i]) for i in range(3)]
        abs_velocity = [abs(self.position[i] - self.last_position[i]) for i in range(3)]
        max_axis_position = abs_position.index(max(abs_position))  
        max_axis_velocity = abs_velocity.index(max(abs_velocity))  

        duration = [min(math.ceil(abs_velocity[i]) + int(abs_position[i]/20),5) for i in range(3)]

        # Kolla hastighet och position för att bestämma motor kommando för x-led
        if self.position[0] < 0:  # x-position är negativ
            if (self.position[0] - self.last_position[0]) < 0:  # Negativ hastighet
                return self.motor[0], duration[0]  # Motor x+
        else:  # x-position är positiv
            if (self.position[0] - self.last_position[0]) > 0:  # Positiv hastighet
                return self.motor[1], duration[0]  # Motor x-

        # Kolla hastighet och position för att bestämma motor kommando för y-led
        if self.position[1] < 0:  # y-position är negativ
            if (self.position[1] - self.last_position[1]) < 0:  # Negativ hastighet
                return self.motor[2], duration[1]  # Motor y+
        else:  # y-position är positiv
            if (self.position[1] - self.last_position[1]) > 0:  # Positiv hastighet
                return self.motor[3], duration[1]  # Motor y-
            
        # Kolla hastighet och position för att bestämma motor kommando för z-led
        if self.position[2] < 0:  # z-position är negativ
            if (self.position[2] - self.last_position[2]) < 0:  # Negativ hastighet
                return self.motor[4], duration[2]  # Motor z+
        else:  # z-position är positiv
            if (self.position[2] - self.last_position[2]) > 0:  # Positiv hastighet
                return self.motor[5], duration[2]  # Motor z-

        # Rörelsen är in mot origo
        
        # Är vi nära origo och hastigheten är för hög måste vi minska den
        # Vi prioriterar den axel längs vilken vi har högst hastighet
        if distance < 15:
            duration = [1,1,1] # Kör motorn så kort vi kan för att göra små justreringar
            if max_axis_velocity == 0:  # x-led prioriteras
                if (abs_velocity[0] > 0.5):
                    print("Minskar hastigheten...")
                    if (self.position[0] - self.last_position[0]) > 0:
                        return self.motor[1], duration[0]
                    else:
                        return self.motor[0], duration[0]
            elif max_axis_velocity == 1:  # y-led prioriteras
                if (abs_velocity[1] > 0.5):
                    print("Minskar hastigheten...")
                    if (self.position[1] - self.last_position[1]) > 0:
                        return self.motor[3], duration[1]
                    else:
                        return self.motor[2], duration[1]
            elif max_axis_velocity == 2:  # z-led prioriteras
                if (abs_velocity[2] > 0.5):
                    print("Minskar hastigheten...")
                    if (self.position[2] - self.last_position[2]) > 0:
                        return self.motor[5], duration[2]
                    else:
                        return self.motor[4], duration[2]

        # Om vi är långt borta och hastigheten för låg för att hinna tillbaka måste vi öka den
        # Vi prioriterar den axel längs vilken vi är längs bort från origo
        elif distance > 20:
            duration = [min(math.ceil(abs_position[i]/10),2) for i in range(3)]
            if max_axis_position == 0:  # x-led prioriteras
                if (abs_position[0] > 15 and abs_velocity[0] < 1) or (abs_position[0] > 50 and abs_velocity[0] < 5):
                    print("Ökar hastigheten...")
                    if (self.position[0] - self.last_position[0]) > 0:
                        return self.motor[0], duration[0]
                    else:
                        return self.motor[1], duration[0]
            elif max_axis_position == 1:  # y-led prioriteras
                if (abs_position[1] > 15 and abs_velocity[1] < 1) or (abs_position[1] > 50 and abs_velocity[1] < 5):
                    print("Ökar hastigheten...")
                    if (self.position[1] - self.last_position[1]) > 0:
                        return self.motor[2], duration[1]
                    else:
                        return self.motor[3], duration[1]
            elif max_axis_position == 2:  # z-led prioriteras
                if (abs_position[2] > 15 and abs_velocity[2] < 1) or (abs_position[2] > 50 and abs_velocity[2] < 5):
                    print("Ökar hastigheten...")
                    if (self.position[2] - self.last_position[2]) > 0:
                        return self.motor[4], duration[2]
                    else:
                        return self.motor[5], duration[2]

        return None, 0

def main():
    parser = argparse.ArgumentParser(description="Undutmaning 2025 - Rädda Joppe.")
    parser.add_argument("--ip",type=str,default="127.0.0.1",help="Adressen att ansluta till (default 127.0.0.1)"    )
    parser.add_argument("--port",type=int,default=3000,help="Porten att ansluta till (default 3000)")
    if plot:
        parser.add_argument("--plot",action="store_true",help="Ange för att Joppes rörelse ska plottas")
        parser.add_argument("--file",type=str,default=None,help="Namnet på en fil där output ska sparas (om inget anges öppnas en websida med plotten)")
        
    args = parser.parse_args()

    s = connect_to_server(args.ip, args.port)

    if s is None:
        return

    controller = SpacecraftController(s)
    controller.read_data()

    if controller.socket:
        controller.socket.close()
        print("Anslutningen stängdes.")

    if plot and (args.plot or args.file):
        fig = go.Figure(data=[go.Scatter3d(x=controller.x_hist,y=controller.y_hist,z=controller.z_hist),
                              go.Scatter3d(x=[0],y=[0],z=[0],mode='markers',marker=dict(color='green',size=10))])
        fig.update_layout(scene = dict(xaxis_title='X',yaxis_title='Y',zaxis_title='Z'))
        if args.file:
            pyo.plot(fig,filename=args.file,auto_open=args.plot)
        else:
            fig.show()

if __name__ == "__main__":
    main()
