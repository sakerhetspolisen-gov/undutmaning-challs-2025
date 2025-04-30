import os
import uuid
import subprocess
from crc16 import calculate_crc16
from flask import Flask, request, render_template, redirect, url_for

app = Flask(__name__)

# Kataloger
SANDBOX_BASE = "/home/ctf/jail/"
SANDBOX_PATH = "/home/ops/"

# Lista över godkända checksummor
VALID_CHECKSUMS = [
    "bbbb", # Kort status
    "3b75", # Full status
]

def execute_script(script_content):
    """Spara och kör scriptet i chroot-jailet."""
    # Skapa en unik ID för användaren för att undvika en krock
    tmp_id = str(uuid.uuid4())
    tmp_name_sandbox = os.path.join(SANDBOX_PATH, tmp_id)
    tmp_name = os.path.join(SANDBOX_BASE, tmp_name_sandbox.lstrip("/"))
    script_path = tmp_name + ".sh"
    script_path_sandbox = tmp_name_sandbox + ".sh"
        
    try:
        # Skriv användarens skript till sandboxen
        with open(script_path, "w") as script_file:
            script_file.write(script_content)
        os.chown(script_path, 1000, 1000) # CTF usern som ägare    
        os.chmod(script_path, 0o755)  # Gör skriptet exekverbart

        # Kör skriptet i chroot jailet
        result = subprocess.run(
            [
                "chroot",
                "--userspec=1000:1000",
                SANDBOX_BASE,
                "/bin/sh",
                script_path_sandbox
            ],
            capture_output=True,
            text=True,
            timeout=5
        )

        output = result.stdout + result.stderr
    except subprocess.TimeoutExpired:
        output = "Skriptet tog för lång tid och avbröts."
    except subprocess.CalledProcessError as e:
        output = f"Fel vid körning av skriptet: {e.stderr}"
    except Exception as e:
        output = f"Fel: {str(e)}"
    finally:
        # Rensa bort scriptet efter exekvering
        if os.path.exists(script_path):
            os.remove(script_path)
            
    return output

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        script_content = request.form.get("script").replace('\r\n', '\n')
        if not script_content:
            return redirect(url_for("error"))

        # Kontrollera CRC16 checksum
        script_crc = calculate_crc16(script_content)
        if script_crc in VALID_CHECKSUMS:
            # Kör skriptet
            output = execute_script(script_content)
            return render_template("output.html", output=output)
        else:
            return render_template("error.html", checksum=script_crc)
    return render_template("index.html")

@app.route("/error")
def error():
    return render_template("error.html", checksum=0)

@app.route("/output")
def output():
    return render_template("output.html")

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8222)
