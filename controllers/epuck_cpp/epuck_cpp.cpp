#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>
#include <iostream>
#include <limits>

using namespace webots;

// 로봇 행동 상태 정의
enum class RobotState {
    FORWARD,
    TURN_LEFT,
    TURN_RIGHT
};

int main() {

    // ===== 1. 로봇 생성 =====
    Robot robot;

    const int timestep =
        static_cast<int>(robot.getBasicTimeStep());

    // ===== 2. 모터 연결 =====
    Motor* leftMotor =
        robot.getMotor("left wheel motor");

    Motor* rightMotor =
        robot.getMotor("right wheel motor");

    if (!leftMotor || !rightMotor) {
        std::cerr << "Motor not found!\n";
        return 1;
    }

    const double INF =
        std::numeric_limits<double>::infinity();

    // 속도 제어 모드
    leftMotor->setPosition(INF);
    rightMotor->setPosition(INF);

    leftMotor->setVelocity(0.0);
    rightMotor->setVelocity(0.0);

    // ===== 3. 센서 8개 연결 =====
    const char* sensorNames[8] = {
        "ps0", "ps1", "ps2", "ps3",
        "ps4", "ps5", "ps6", "ps7"
    };

    DistanceSensor* sensors[8];

    for (int i = 0; i < 8; i++) {

        sensors[i] =
            robot.getDistanceSensor(sensorNames[i]);

        if (!sensors[i]) {
            std::cerr << "Sensor not found!\n";
            return 1;
        }

        sensors[i]->enable(timestep);
    }

    // ===== 4. 제어 설정 =====

    // 히스테리시스: 초기 시험값
    const double DETECT_ON = 110.0;
    const double DETECT_OFF = 90.0;

    bool detected[8] = {false};

    RobotState state = RobotState::FORWARD;

    double lastPrintTime = 0.0;

    // ===== 5. 메인 제어 루프 =====
    while (robot.step(timestep) != -1) {

        double leftSignal = 0.0;
        double rightSignal = 0.0;

        double sensorValue[8] = {0.0};

        // STEP A. 센서값 측정
        for (int i = 0; i < 8; i++) {

            sensorValue[i] = sensors[i]->getValue();

            // STEP B. 히스테리시스
            if (!detected[i] &&
                sensorValue[i] >= DETECT_ON) {

                detected[i] = true;
            }
            else if (detected[i] &&
                     sensorValue[i] <= DETECT_OFF) {

                detected[i] = false;
            }

            // STEP C. 좌우 신호 합산
            if (detected[i]) {

                if (i < 3) {
                    rightSignal += sensorValue[i];
                }
                else if (i > 4) {
                    leftSignal += sensorValue[i];
                }
            }
        }

        // STEP D. 회피 방향 결정
        if (leftSignal == 0.0 &&
            rightSignal == 0.0) {

            state = RobotState::FORWARD;
        }
        else if (rightSignal > leftSignal) {

            state = RobotState::TURN_LEFT;
        }
        else if (leftSignal > rightSignal) {

            state = RobotState::TURN_RIGHT;
        }
        else {
            // 양쪽 신호가 같고 장애물이 있을 때
            // 무한 정지를 피하기 위한 임시 규칙
            state = RobotState::TURN_LEFT;
        }

        // STEP E. 모터 속도 결정
        double leftSpeed = 0.0;
        double rightSpeed = 0.0;

        switch (state) {

            case RobotState::FORWARD:
                leftSpeed = 3.0;
                rightSpeed = 3.0;
                break;

            case RobotState::TURN_LEFT:
                leftSpeed = -2.0;
                rightSpeed = 2.0;
                break;

            case RobotState::TURN_RIGHT:
                leftSpeed = 2.0;
                rightSpeed = -2.0;
                break;
        }

        // STEP F. 모터 구동
        leftMotor->setVelocity(leftSpeed);
        rightMotor->setVelocity(rightSpeed);

        // STEP G. 데이터 출력 (0.5초 간격)
        if (robot.getTime() - lastPrintTime >= 0.5) {

            std::cout
                << "Time=" << robot.getTime()
                << " ps0=" << sensorValue[0]
                << " ps7=" << sensorValue[7]
                << " L=" << leftSignal
                << " R=" << rightSignal
                << " vL=" << leftSpeed
                << " vR=" << rightSpeed
                << std::endl;

            lastPrintTime = robot.getTime();
        }
    }

    return 0;
}
