#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <limits>
#include <iostream>

using namespace webots;

int main() {
    // 1. 로봇 생성
    Robot robot;
    const int timestep = static_cast<int>(robot.getBasicTimeStep());

    // 2. 좌우 모터 가져오기
    Motor* leftMotor = robot.getMotor("left wheel motor");
    Motor* rightMotor = robot.getMotor("right wheel motor");

    if (leftMotor == nullptr || rightMotor == nullptr) {
        std::cerr << "Motor not found!" << std::endl;
        return 1;
    }

    // 3. 속도 제어 모드 설정
    const double INF = std::numeric_limits<double>::infinity();

    leftMotor->setPosition(INF);
    rightMotor->setPosition(INF);

    // 4. 좌우 모터 속도 (rad/s)
    leftMotor->setVelocity(3.0);
    rightMotor->setVelocity(-3.0);

    // 5. 시뮬레이션 루프
    while (robot.step(timestep) != -1) {
        // 다음 단계에서 센서 제어 코드 추가
    }

    return 0;
}
