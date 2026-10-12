# Webots Differential Drive Robot

**Webots R2025a와 C++을 이용한 e-puck 차동구동 로봇 제어 및 장애물 회피 프로젝트**

**상태:**  In Progress | **개발 기간:** 2026.10.11 ~

## 1. 프로젝트 목표

Webots 가상환경에서 e-puck 로봇을 C++로 제어하고, 기계공학의 **차동구동 운동학**을 실제 시뮬레이션 결과와 비교합니다. 최종 목표는 거리 센서 기반 **자율 장애물 회피**와 성능 검증입니다.

- 좌우 바퀴 속도 제어와 차동구동 운동학 이해
- 개방루프 회전 제어 및 엔코더 기반 오도메트리 실험
- 거리 센서(`ps0`~`ps7`)를 활용한 장애물 회피 알고리즘 구현 예정
- 제어 결과를 수치로 기록하고 이론 모델과 비교

## 2. 개발 환경

| 항목 | 사용 환경 |
|---|---|
| Simulator | Webots R2025a |
| Robot | e-puck |
| Main language | C++ |
| Initial practice | Python |
| Operating system | Windows 10 |
| Controller | `epuck_cpp` |

## 3. 구현 현황

**완료**
- [x] Webots 프로젝트 생성 및 e-puck 배치
- [x] Python / C++ 제어기 연결과 빌드
- [x] 직진, 곡선 주행, 제자리 회전
- [x] 시간 기반 목표 회전각 제어 및 자동 정지
- [x] 바퀴 엔코더 측정과 오도메트리 추정
- [x] 회전 속도별 오차 비교 실험

**예정**
- [ ] 거리 센서 데이터 읽기와 임계값 설정
- [ ] 장애물 회피 알고리즘 (C++)
- [ ] 알고리즘 성능 평가 및 시연 영상
- [ ] 목표 회전각의 피드백 제어 (후속 심화)

## 4. 개발 일지

새 실습을 마칠 때마다 이 표에 한 줄만 추가하고, 자세한 내용은 [notes.md](notes.md)에 기록합니다.

| Day | 날짜 | 주요 활동 | 결과 |
|---|---|---|---|
| 01 | 2026-10-11 | Webots 세팅, 모터 속도 제어, 차동구동 운동학 | 직진·회전 성공 |
| 02 | 2026-10-12 | 시간 기반 90° 회전, 엔코더·몸체 회전각 비교 | 오차 측정 및 재현성 확인 |
| 03 | 예정 | 거리 센서와 C++ 조건문 | 진행 예정 |

## 5. 대표 실험 — 90° 시계방향 회전 (Day 02)

이상적인 차동구동 운동학을 이용하여 목표 회전 시간을 계산하고, Webots 자세 변화와 비교했습니다.

**모델 계산값:** 바퀴 반지름 `r = 0.020m`(충돌 형상 기준), 바퀴 간 거리 `L = 0.052m`, 제어 주기 `32ms`

| 항목 | 실험 A (고속) | 실험 B (저속) |
|---|---:|---:|
| 바퀴 속도 (좌/우) | +3 / −3 rad/s | +1.5 / −1.5 rad/s |
| 정지 명령 시점 | 0.704s | 1.376s |
| 왼쪽/오른쪽 엔코더 | +2.11080 / −2.11008 rad | +2.05984 / −2.05984 rad |
| 엔코더 기반 회전각 추정 | −93.01° | −90.78° |
| Webots 몸체 자세 변화 | −85.45° | −83.22° |
| 두 회전각의 차이 | 7.56° | 7.57° |
| 90° 목표 대비 몸체 오차 | 4.55° 부족 | 6.78° 부족 |

**분석 결과**

명령 시간은 32ms 제어 주기에 맞춰 처리됐습니다.

두 실험 모두 엔코더 추정 회전각과 몸체 자세 사이에 약 7.6°의 차이가 나타났습니다.

이는 이상적인 미끄러짐 없는 차동구동 모델이 시뮬레이션 운동을 완전히 설명하지 못함을 보여줍니다.

바퀴 미끄러짐, 접촉 및 유효 기구 파라미터 등이 가능한 원인이지만 하나의 원인으로 확정하지 않았습니다.

계산 과정, 원본 데이터 및 자세한 학습 내용은 [notes.md](notes.md)에 정리했습니다.

## 6. 실행 방법

1. Webots R2025a에서 `worlds/obstacle_avoidance.wbt` 열기
2. e-puck의 `controller`를 `epuck_cpp`로 설정
3. `epuck_cpp.cpp`를 열고 Build → Build로 컴파일
4. 초기 자세 확인 후 Reload World → Real-time 실행
5. 새 실험 전 초기 월드를 다시 불러오고, 회전한 상태의 월드는 저장하지 않기

## 7. 폴더 구조

```text
webots-obstacle-avoidance/
├── controllers/
│   ├── epuck_cpp/
│   │   ├── epuck_cpp.cpp
│   │   └── Makefile
│   └── epuck_controller/
│       └── epuck_controller.py
├── worlds/
│   └── obstacle_avoidance.wbt
├── README.md
└── notes.md
```

빌드된 `.exe` 등 실행 파일은 업로드하지 않습니다.

## 8. 참고 자료

- [Webots 공식 사이트](https://cyberbotics.com/)
- [Webots R2025a e-puck 모델 정의](https://github.com/cyberbotics/webots/blob/R2025a/projects/robots/gctronic/e-puck/protos/E-puck.proto)
- [Webots Controller Programming](https://cyberbotics.com/doc/guide/controller-programming)
- [Webots Pose](https://cyberbotics.com/doc/reference/pose)
