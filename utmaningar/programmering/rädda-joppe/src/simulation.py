import numpy as np
import random
import time
import threading
import sys
from scipy.spatial.transform import Rotation as R  # För rotationsmatris

time_limit = 400        # Tidsbegränsning i sekunder
distance_limit = 800    # Om över detta avstånd från origo förloras kontakten
max_fuel = 1000         # Bränsle per motor från början
safe_speed_limit = 0.4  # Max tillåten hastighet för att undvika krasch

def out(text="", end="\n"):
    print(text, end=end)
    sys.stdout.flush()

class Spacecraft:
    def __init__(self):
        # Är farkosten alive and kicking?
        self.alive = True

        # Startposition 
        self.position = np.array([random.uniform(-20, 20) for _ in range(3)], dtype=float)
        
         # Initial hastighet rätlinjigt bort från origo, normerad
        direction = self.position / np.linalg.norm(self.position)  # Enhetsvektor i riktning från origo
        speed = random.uniform(0.5, 2.0)  # Slumpmässig hastighet
        self.velocity = direction * speed

        # Farkostens inre axelförskjutning (rotation i förhållande till omgivande rymd)

        # Den här koden ger en mindre förskjutning runt rymdaxlarna och får anses vara en klart enklare variant
        #   rotation_angles = np.radians([random.uniform(-20, 20) for _ in range(3)])  # Liten rotation runt varje axel
        #   self.rotation_matrix = R.from_euler('xyz', rotation_angles).as_matrix()  # Skapar rotationsmatris

        # Den här koden ersätter den utkommenterade koden ovan och innebär en klart svårare utmaning då
        # den innebär att farkostens rotation i rymden är fullkomligt slumpmässig 
        self.rotation_matrix = R.random().as_matrix()  # Skapar rotationsmatris

        # Motorer och bränsle för varje riktning (6 motorer totalt: +x, -x, +y, -y, +z, -z)
        self.fuel = max_fuel  # Max bränsle per motor
        self.fuel_per_motor = [self.fuel] * 6
        
        # Simulation begränsningar
        self.max_distance = distance_limit
        self.time_limit = time_limit
        self.start_time = time.time()
        
        # Motor påverkan
        self.motor_force = 0.1  # Kraft som varje motor tillför per sekund

    def is_alive(self):
        return self.alive

    def apply_motor(self, motor_id, duration):
        """Kör vald motor under <duration> sekunder (eller så länge bränslet räcker)."""
        if motor_id < 0 or motor_id > 5:
            out("ERR-INVALID-MOTOR")
            return False

        if self.fuel_per_motor[motor_id] <= 0:
            out(f"ERR-INSUFFICIENT-FUEL")
            return False

        force_vector = np.zeros(3)

        # Definiera kraft beroende på motor
        if motor_id == 0:
            force_vector[0] = self.motor_force  # +x
        elif motor_id == 1:
            force_vector[0] = -self.motor_force  # -x
        elif motor_id == 2:
            force_vector[1] = self.motor_force  # +y
        elif motor_id == 3:
            force_vector[1] = -self.motor_force  # -y
        elif motor_id == 4:
            force_vector[2] = self.motor_force  # +z
        elif motor_id == 5:
            force_vector[2] = -self.motor_force  # -z

        # Lägg till axelförskjutningen
        adjusted_force = self.rotation_matrix.dot(force_vector)

        # Informera om att motorn är aktiv
        out(f"MRT-{motor_id}-AKT")

        while duration > 0 and self.fuel_per_motor[motor_id] > 0:
            # Ändra hastigheten
            self.velocity += adjusted_force 

            # Minska mängden bränsle i motorn
            self.fuel_per_motor[motor_id] -= 1

            # Vi har kört i en sekund, vänta till nästa            
            duration -= 1
            time.sleep(1)

        return True

    def update_position(self):
        """Uppdaterar farkostens position och kollar status."""
        # Ny position baserad på hastighet
        self.position += self.velocity
        distance_from_origin = np.linalg.norm(self.position)
        current_speed = np.linalg.norm(self.velocity)

        # Kolla om farkosten har gått för långt bort
        if distance_from_origin > self.max_distance:
            out("Kontakten med farkosten har förlorats!")
            self.alive = False
            return False
        
        # Kontrollera tidsgränsen
        if time.time() - self.start_time > self.time_limit:
            out("Kontakten med farkosten har förlorats!")
            self.alive = False
            return False

        # Kolla om farkosten är nära origo (målet)
        if distance_from_origin < 1:
            # Om hastigheten är för hög så krashar farkosten
            if current_speed > safe_speed_limit:
                out("Kontakten med farkosten har förlorats!")
                self.alive = False
                return False
            else:
                out("Dockning genomförd. Uppdrag slutfört!")
                f = open("flag.txt","r")
                text = f.read()
                f.close()
                out(text)
                self.alive = False
                return False

        # Skriv ut aktuell position 
        out([round(float(coord), 2) for coord in self.position])
        return True

def control_spacecraft(spacecraft):
    """Kontrollerar användarkommandon för motorer."""
    while spacecraft.is_alive():
        command = input("")
        try:
            motor_id, duration = map(int, command.strip().split(":"))
            if spacecraft.apply_motor(motor_id, duration):
                out("OK")
            time.sleep(1)
        except ValueError:
            out("ERR-COMMAND-INVALID")


def main():
    spacecraft = Spacecraft()

    # Skriv ut lite initial information
    out("Ansluten till JOPPE")
    out("Stabilisering utförd.")
    out("Gyro ur funktion.")
    out("Nöddrift aktiverad.")
    out(f"Återstående batteritid ca {time_limit} sekunder.")
    out("Motor 0 - 5 redo.")
    out("Ange kommando <motor>:<sekunder> för att aktivera motor.")

    # Skapa en tråd för användarkommandon
    control_thread = threading.Thread(target=control_spacecraft, args=(spacecraft,))
    control_thread.daemon = True
    control_thread.start()

    # Uppdatera farkostens position varje sekund
    while True:
        time.sleep(1)
        if not spacecraft.update_position():
            break

if __name__ == "__main__":
    main()
