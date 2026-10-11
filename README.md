# Webots Differential Drive Robot

**Webots와 C++을 이용한 차동구동 로봇 제어 및 장애물 회피 프로젝트**

## 프로젝트 개요

Webots R2025a 환경에서 e-puck 로봇의 좌우 바퀴를 제어하고, 차동구동 운동학을 학습하는 프로젝트입니다.

향후 거리 센서 기반 장애물 회피 알고리즘과 성능 검증 기능을 구현할 예정입니다.

## 개발 환경

- Simulator: Webots R2025a
- Language: C++ (Main), Python (Initial Practice)
- Robot: e-puck
- Platform: Windows 10

## 구현 현황

**완료**
- Webots 시뮬레이션 환경 구축
- C++ 로봇 제어기 작성
- 좌우 바퀴 속도 제어
- 직진, 곡선 주행, 제자리 회전 구현
- 차동구동 운동학 이해 및 계산

**진행 예정**
- 거리 센서 데이터 처리
- 장애물 회피 알고리즘
- 목표 각도 제어
- 시뮬레이션 성능 검증

## 핵심 학습 내용

- Differential Drive Kinematics
- Linear & Angular Velocity
- Webots Motor API
- C++ Object-Oriented Programming

## 실행 방법

1. Webots R2025a에서 `worlds/obstacle_avoidance.wbt` 열기
2. 로봇의 Controller를 `epuck_cpp`로 설정
3. C++ Controller 빌드
4. 시뮬레이션 Reset 후 실행

## 개발 상태

🚧 In Progress
