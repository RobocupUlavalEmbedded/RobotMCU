from pyhermes.McuCommunicator import McuCommunicator
from pyhermes.packet_definitions import RegisterID
from time import sleep
import time
from numpy import arange 
from math import sqrt

current_milli_time = lambda: int(round(time.time() * 1000))

def rotate_test(robot_id):
    print("Start rotate test")
    com = McuCommunicator()
    com.setRegister(robot_id, REG_CTRL_LOOP_STATE, 2)
    while True:
            print("Rotate command send")
            com.sendSpeed(robot_id, 0 , 0, 1.0) # break
            sleep(0.01)


def open_loop_test(robot_id, commands):
    # commands = []
    #
    # commands.append((6000, 0, 0, 0, 0))

    # RAMP ..
    # for cmd in range(-40, 40, 1):
    #     commands.append((200, 0, -cmd/100, 0, cmd/100))
    #
    # commands.append((1000, 0, -0.4, 0, 0.4))
    do_test(1, 0, commands, robot_id)

# 0.03 max 2 wheels speed
# 0.07 max 4 wheels speed
def close_loop_test(robot_id, commands):
    # commands = [
    # (10000, 0.3535, 0.3535, 0)
    # ]

    a = 1.6 # m/s^2

    max_dist = 3.5 # meters
    sampling_period = 0.05 # secondes
    test_duration = sqrt(2 * max_dist / a)

    sampling_time = arange(0, test_duration, sampling_period)
    speed = a * sampling_time
    commands = [(50, i, i, 0) for i in speed]
    do_test(1, 2, commands, robot_id)


def do_test(ctrl_loop_state_initially, ctrl_loop_state_for_test, commands, robot_id) :
    com = McuCommunicator()

    # wait to contact robot
    #while not com.testHeartBeat():
    #	pass

    com.sendSpeed(robot_id,0,0,0) # break
    com.sendOpenLoopSpeed(robot_id,0,0,0,0) # break
    sleep(1)

    for _ in range(0, 100):
        com.setRegister(robot_id, RegisterID.CONTROL_LOOP_STATE, ctrl_loop_state_for_test)


    if ctrl_loop_state_for_test == 0:
        print("Start open loop")
        for (dt, cmd1, cmd2, cmd3, cmd4) in commands:
            print(time.time(), cmd1, ' ', cmd2, ' ', cmd3, ' ', cmd4)
            start = current_milli_time()
            while current_milli_time() - start < dt:
                com.sendOpenLoopSpeed(robot_id, cmd1, cmd2, cmd3, cmd4)  # -command
                sleep(0.05)
        print("Stop open loop")
        for i in range(1, 10):
            com.sendOpenLoopSpeed(robot_id, 0, 0, 0, 0)
            sleep(0.1)
    else:
        print("Start close loop")
        for (dt, vx, vy, vtheta) in commands:
            print(time.time(), vx, ' ', vy, ' ', vtheta)
            start = current_milli_time()
            while current_milli_time() - start < dt:
                com.sendSpeed(robot_id, vx, vy, vtheta) # -command
                sleep(0.05)

        print("Stop close loop")
        for i in range(1, 10):
            com.sendSpeed(robot_id, 0, 0, 0)
            sleep(0.1)


    com.setRegister(robot_id, RegisterID.CONTROL_LOOP_STATE, ctrl_loop_state_initially) # set close loop
