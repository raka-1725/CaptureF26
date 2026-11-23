from flask import Flask, request, jsonify
import subprocess #To fire another thread to work on anothet task

SESSION_NAME_KEY = "SESSION_NAME"
SESSION_SEARCH_ID_KEY="SESSION_SEARCH_ID"
SESSION_PORT_KEY = "SESSION_PORT"
nextAvaialePort = 7777

app = Flask(__file__)

def CreateServerLocalTest(SessionName, SessionSearchID):
    global nextAvaialePort
    print(f"creating session with name {SessionName} and id: {SessionSearchID}")
    subprocess.Popen
    (
        [
            "C:/UnrealSources/Unreal5.7.4/Engine/Binaries/Win64/UnrealEditor.exe",
            "C:/dev/Capture/Capture.uproject",
            "-server",
            "-log",
            "-epicapp=ServerClient",
            f"-{SESSION_NAME_KEY}={SessionName}",
            f"-{SESSION_SEARCH_ID_KEY}={SessionSearchID}",
            f"-{SESSION_PORT_KEY}={nextAvaialePort}"
        ]
    )

    usedPort = nextAvaialePort
    nextAvaialePort += 1

    return usedPort

# @ - decolator
@app.route('/Session', methods = ['Post'])
def CreateServer():
    print(dict(request.headers))
    sessionName = request.get_json().get(SESSION_NAME_KEY)
    sessionSearchID = request.get_json().get(SESSION_SEARCH_ID_KEY)

    port = CreateServerLocalTest(sessionName, sessionSearchID)

    return jsonify({'status':'success', SESSION_PORT_KEY: port}), 200

if __name__ == "__main__":
    app.run(host = '0.0.0.0', port = 80)
