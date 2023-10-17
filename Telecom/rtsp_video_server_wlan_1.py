import network, omv, rtsp, sensor, time

# RTP MJPEG streaming works using JPEG images produced by the OV2640/OV5640 camera modules.
# Not all programs (e.g. VLC) implement the full JPEG standard for decoding any JPEG image
# in RTP packets. Images JPEG compressed by the OpenMV Cam internally may not display.

# FFPLAY will correctly handle JPEGs produced by OpenMV software.

sensor.reset()

sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.VGA)

omv.disable_fb(True)

# Setup Network Interface

network_if = network.WLAN(network.STA_IF)
network_if.active(True)
network_if.connect('your-ssid', 'your-password')
while not network_if.isconnected():
    print("Trying to connect. Note this may take a while...")
    time.sleep_ms(1000)

# Setup RTSP Server

server = rtsp.rtsp_server(network_if)

# Track the current FPS.
clock = time.clock()

def setup_callback(pathname, session):
    print("Opening \"%s\" in session %d" % (pathname, session))

def play_callback(pathname, session):
    clock.reset()
    clock.tick()
    print("Playing \"%s\" in session %d" % (pathname, session))

def pause_callback(pathname, session): # VLC only pauses locally. This is never called.
    print("Pausing \"%s\" in session %d" % (pathname, session))

def teardown_callback(pathname, session):
    print("Closing \"%s\" in session %d" % (pathname, session))

server.register_setup_cb(setup_callback)
server.register_play_cb(play_callback)
server.register_pause_cb(pause_callback)
server.register_teardown_cb(teardown_callback)

# Called each time a new frame is needed.
def image_callback(pathname, session):
    img = sensor.snapshot()
    # Markup image and/or do various things.
    print(clock.fps())
    clock.tick()
    return img

# Stream does not return. It will call `image_callback` when it needs to get an image object to send
# to the remote rtsp client connecting to the server.

server.stream(image_callback, quality=70)
