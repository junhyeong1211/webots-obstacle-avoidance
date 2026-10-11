from controller import Robot

# 1. 로봇 객체 생성
robot = Robot()
timestep = int(robot.getBasicTimeStep())

# 2. 좌우 바퀴 모터 가져오기
left_motor = robot.getDevice("left wheel motor")
right_motor = robot.getDevice("right wheel motor")

# 3. 모터를 속도 제어 모드로 설정
left_motor.setPosition(float("inf"))
right_motor.setPosition(float("inf"))

# 4. 양쪽 바퀴 회전 속도 설정 (rad/s)
left_motor.setVelocity(3.0)
right_motor.setVelocity(-3.0)

# 5. 시뮬레이션 실행
while robot.step(timestep) != -1:
    pass
